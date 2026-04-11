#include "Vx/Context.h"  // IWYU pragma: associated

#include <stdbool.h>

#include "Internal.h"
#include "Vx/Event.h"
#include "Vx/Window.h"

LRESULT CALLBACK VxWindow__Process(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
  VxEventRing ring = (VxEventRing)GetWindowLongPtr(hwnd, GWLP_USERDATA);

  switch (umsg) {
    case WM_DESTROY:
      free(ring);
      SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)NULL);
      PostQuitMessage(0);
      return 0;

    case WM_TIMER:
      InvalidateRect(hwnd, NULL, TRUE);
      UpdateWindow(hwnd);
      return 0;

    case WM_CLOSE:
      return !VxEventRing_Put(ring, (VxEvent){.type = VxEventType_Close});

    case WM_SETFOCUS:
      VxEventRing_Put(ring, (VxEvent){.type = VxEventType_Focus});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_KILLFOCUS:
      VxEventRing_Put(ring, (VxEvent){.type = VxEventType_Blur});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_SHOWWINDOW:
      if (wparam)
        VxEventRing_Put(ring, (VxEvent){.type = VxEventType_Show});
      else
        VxEventRing_Put(ring, (VxEvent){.type = VxEventType_Hide});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_SIZE:
      if (wparam == SIZE_RESTORED)
        VxEventRing_Put(ring, (VxEvent){.type = VxEventType_Resize, .info.size = {LOWORD(lparam), HIWORD(lparam)}});
      else if (wparam == SIZE_MAXIMIZED)
        VxEventRing_Put(ring, (VxEvent){.type = VxEventType_Maximize});
      else if (wparam == SIZE_MINIMIZED)
        VxEventRing_Put(ring, (VxEvent){.type = VxEventType_Minimize});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_MOVE:
      VxEventRing_Put(ring, (VxEvent){.type = VxEventType_Move, .info.pos = {LOWORD(lparam), HIWORD(lparam)}});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_KEYDOWN:
      VxEventRing_Put(ring, (VxEvent){.type = VxEventType_KeyPress, .info.press.key = VxEventKey_Unknown});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_KEYUP:
      VxEventRing_Put(ring, (VxEvent){.type = VxEventType_KeyRelease, .info.press.key = VxEventKey_Unknown});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_CHAR:
      VxEventRing_Put(ring, (VxEvent){.type = VxEventType_CharSent, .info.sent = wparam});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_LBUTTONDOWN:
      VxEventRing_Put(ring, (VxEvent){.type = VxEventType_MousePress, .info.button = VxEventButton_MouseLeft});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_LBUTTONUP:
      VxEventRing_Put(ring, (VxEvent){.type = VxEventType_MouseRelease, .info.button = VxEventButton_MouseLeft});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_RBUTTONDOWN:
      VxEventRing_Put(ring, (VxEvent){.type = VxEventType_MousePress, .info.button = VxEventButton_MouseRight});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_RBUTTONUP:
      VxEventRing_Put(ring, (VxEvent){.type = VxEventType_MouseRelease, .info.button = VxEventButton_MouseRight});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_MBUTTONDOWN:
      VxEventRing_Put(ring, (VxEvent){.type = VxEventType_MousePress, .info.button = VxEventButton_MouseCenter});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_MBUTTONUP:
      VxEventRing_Put(ring, (VxEvent){.type = VxEventType_MouseRelease, .info.button = VxEventButton_MouseCenter});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_MOUSEMOVE:
      VxEventRing_Put(ring, (VxEvent){.type = VxEventType_MouseMove, .info.pos = {LOWORD(lparam), HIWORD(lparam)}});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_MOUSEWHEEL:
      VxEventRing_Put(ring, (VxEvent){.type = VxEventType_MouseWheel, .info.delta = HIWORD(wparam)});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    default:
      return DefWindowProc(hwnd, umsg, wparam, lparam);
  }
}

bool VxContext_Initiate(VxContext *context) {
  WNDCLASSEX wc = {0};
  wc.lpszClassName = VxWindow_Class;
  wc.lpfnWndProc = VxWindow__Process;
  wc.hInstance = GetModuleHandle(NULL);
  wc.cbSize = sizeof(WNDCLASSEX);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW + 1;

  if (!RegisterClassEx(&wc)) {
    Vx__Error("failed to register window class");
    return false;
  }

  if (!context) return true;

  *context = calloc(1, sizeof(struct VxContext));
  if (!*context) {
    Vx__Error("failed to allocate context");
    return false;
  }

#ifdef VxContext_UseAngle
  EGLint display_spec[] = {EGL_PLATFORM_ANGLE_TYPE_ANGLE, EGL_PLATFORM_ANGLE_TYPE_D3D11_ANGLE, EGL_NONE};

  PFNEGLGETPLATFORMDISPLAYEXTPROC eglGetPlatformDisplayEXT =
      (PFNEGLGETPLATFORMDISPLAYEXTPROC)eglGetProcAddress("eglGetPlatformDisplayEXT");

  (*context)->display = eglGetPlatformDisplayEXT(EGL_PLATFORM_ANGLE_ANGLE, EGL_DEFAULT_DISPLAY, display_spec);
  if ((*context)->display == EGL_NO_DISPLAY) {
    Vx__Error("failed to setup OpenGL ES display");
  }

  if (!eglInitialize((*context)->display, NULL, NULL)) {
    Vx__Error("failed to setup OpenGL ES");
    return false;
  }

  EGLint config_spec[] = {EGL_RENDERABLE_TYPE,
                          EGL_OPENGL_ES2_BIT,
                          EGL_SURFACE_TYPE,
                          EGL_WINDOW_BIT,
                          EGL_RED_SIZE,
                          8,
                          EGL_GREEN_SIZE,
                          8,
                          EGL_BLUE_SIZE,
                          8,
                          EGL_ALPHA_SIZE,
                          8,
                          EGL_NONE};

  EGLint num;

  if (!eglChooseConfig((*context)->display, config_spec, &(*context)->config, 1, &num)) {
    if (num == 0)
      Vx__Error("could not find matching config");
    else
      Vx__Error("failed to setup OpenGL ES config");

    return false;
  }
#endif

  return true;
}

bool VxContext_ClearGraphics(VxContext context) {
  if (!context) {
    Vx__Error("called with invalid args");
    return false;
  }

#ifdef VxContext_UseAngle
  if (!eglMakeCurrent(context->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT)) {
    Vx__Error("failed to clear context");
    return false;
  }
#endif

  return true;
}

bool VxContext_Terminate(VxContext context) {
  if (!UnregisterClass(VxWindow_Class, GetModuleHandle(NULL))) {
    Vx__Error("failed to unregister window class");
    return false;
  }

  if (!context) return true;

#ifdef VxContext_UseAngle
  if (!eglTerminate(context->display)) {
    Vx__Error("failed to delete OpenGL ES display");
    return false;
  }
#endif

  free(context);
  return true;
}
