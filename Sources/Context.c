#include "Vx/Context.h"

#include <stdbool.h>

#include "Internal.h"
#include "Vx/Event.h"
#include "Vx/Window.h"

VxEventKey Vx__TranslateKey(VxEventKey key) {
  switch (key) {
    case 'A':
      return VxEventKey_A;
    case 'B':
      return VxEventKey_B;
    case 'C':
      return VxEventKey_C;
    case 'D':
      return VxEventKey_D;
    case 'E':
      return VxEventKey_E;
    case 'F':
      return VxEventKey_F;
    case 'G':
      return VxEventKey_G;
    case 'H':
      return VxEventKey_H;
    case 'I':
      return VxEventKey_I;
    case 'J':
      return VxEventKey_J;
    case 'K':
      return VxEventKey_K;
    case 'L':
      return VxEventKey_L;
    case 'M':
      return VxEventKey_M;
    case 'N':
      return VxEventKey_N;
    case 'O':
      return VxEventKey_O;
    case 'P':
      return VxEventKey_P;
    case 'Q':
      return VxEventKey_Q;
    case 'R':
      return VxEventKey_R;
    case 'S':
      return VxEventKey_S;
    case 'T':
      return VxEventKey_T;
    case 'U':
      return VxEventKey_U;
    case 'V':
      return VxEventKey_V;
    case 'W':
      return VxEventKey_W;
    case 'X':
      return VxEventKey_X;
    case 'Y':
      return VxEventKey_Y;
    case 'Z':
      return VxEventKey_Z;

    case '0':
      return VxEventKey_0;
    case '1':
      return VxEventKey_1;
    case '2':
      return VxEventKey_2;
    case '3':
      return VxEventKey_3;
    case '4':
      return VxEventKey_4;
    case '5':
      return VxEventKey_5;
    case '6':
      return VxEventKey_6;
    case '7':
      return VxEventKey_7;
    case '8':
      return VxEventKey_8;
    case '9':
      return VxEventKey_9;

    case VK_ESCAPE:
      return VxEventKey_Escape;
    case VK_TAB:
      return VxEventKey_Tab;
    case VK_CAPITAL:
      return VxEventKey_CapsLock;
    case VK_SPACE:
      return VxEventKey_Space;
    case VK_RETURN:
      return VxEventKey_Enter;
    case VK_BACK:
      return VxEventKey_Backspace;

    case VK_INSERT:
      return VxEventKey_Insert;
    case VK_DELETE:
      return VxEventKey_Delete;
    case VK_HOME:
      return VxEventKey_Home;
    case VK_END:
      return VxEventKey_End;
    case VK_PRIOR:
      return VxEventKey_PageUp;
    case VK_NEXT:
      return VxEventKey_PageDown;
    case VK_LEFT:
      return VxEventKey_Left;
    case VK_RIGHT:
      return VxEventKey_Right;
    case VK_UP:
      return VxEventKey_Up;
    case VK_DOWN:
      return VxEventKey_Down;

    case VK_F1:
      return VxEventKey_F1;
    case VK_F2:
      return VxEventKey_F2;
    case VK_F3:
      return VxEventKey_F3;
    case VK_F4:
      return VxEventKey_F4;
    case VK_F5:
      return VxEventKey_F5;
    case VK_F6:
      return VxEventKey_F6;
    case VK_F7:
      return VxEventKey_F7;
    case VK_F8:
      return VxEventKey_F8;
    case VK_F9:
      return VxEventKey_F9;
    case VK_F10:
      return VxEventKey_F10;
    case VK_F11:
      return VxEventKey_F11;
    case VK_F12:
      return VxEventKey_F12;

    case VK_NUMLOCK:
      return VxEventKey_NumLock;
    case VK_NUMPAD0:
      return VxEventKey_Numpad0;
    case VK_NUMPAD1:
      return VxEventKey_Numpad1;
    case VK_NUMPAD2:
      return VxEventKey_Numpad2;
    case VK_NUMPAD3:
      return VxEventKey_Numpad3;
    case VK_NUMPAD4:
      return VxEventKey_Numpad4;
    case VK_NUMPAD5:
      return VxEventKey_Numpad5;
    case VK_NUMPAD6:
      return VxEventKey_Numpad6;
    case VK_NUMPAD7:
      return VxEventKey_Numpad7;
    case VK_NUMPAD8:
      return VxEventKey_Numpad8;
    case VK_NUMPAD9:
      return VxEventKey_Numpad9;
    case VK_MULTIPLY:
      return VxEventKey_NumpadMultiply;
    case VK_ADD:
      return VxEventKey_NumpadAdd;
    case VK_SUBTRACT:
      return VxEventKey_NumpadSubtract;
    case VK_DECIMAL:
      return VxEventKey_NumpadDecimal;
    case VK_DIVIDE:
      return VxEventKey_NumpadDivide;

    case VK_OEM_1:
      return VxEventKey_Semicolon;
    case VK_OEM_PLUS:
      return VxEventKey_Equals;
    case VK_OEM_COMMA:
      return VxEventKey_Comma;
    case VK_OEM_MINUS:
      return VxEventKey_Minus;
    case VK_OEM_PERIOD:
      return VxEventKey_Period;
    case VK_OEM_2:
      return VxEventKey_Slash;
    case VK_OEM_3:
      return VxEventKey_Backtick;
    case VK_OEM_4:
      return VxEventKey_LeftBracket;
    case VK_OEM_5:
      return VxEventKey_Backslash;
    case VK_OEM_6:
      return VxEventKey_RightBracket;
    case VK_OEM_7:
      return VxEventKey_Quote;

    default:
      return VxEventKey_Unknown;
  }
}

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

    case WM_KEYDOWN: {
      VxEvent ev = (VxEvent) { .type = VxEventType_KeyPress, .info.press.key = Vx__TranslateKey(wparam) };

      if (GetKeyState(VK_CONTROL) & 0x8000) ev.info.press.mod |= VxEventMod_Control;
      else if (GetKeyState(VK_SHIFT) & 0x8000) ev.info.press.mod |= VxEventMod_Shift;
      else if (GetKeyState(VK_MENU) & 0x8000) ev.info.press.mod |= VxEventMod_Alt;

      if (ev.info.press.key != VxEventKey_Unknown) VxEventRing_Put(ring, ev);
      return DefWindowProc(hwnd, umsg, wparam, lparam);
    }

    case WM_KEYUP: {
      VxEventKey key = Vx__TranslateKey(wparam);
      if (key != VxEventKey_Unknown) VxEventRing_Put(ring, (VxEvent){.type = VxEventType_KeyRelease, .info.press.key = key});
      return DefWindowProc(hwnd, umsg, wparam, lparam);
    }

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
