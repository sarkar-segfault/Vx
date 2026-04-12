#include "Vx/Context.h"

#include <stdbool.h>

#include "Internal.h"
#include "Vx/Window.h"

Vx__Extern LRESULT CALLBACK VxWindow__Process(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

bool VxContext_Initiate(VxContext **context) {
  WNDCLASSEX wc = {0};
  wc.lpszClassName = VxWindow_Class;
  wc.lpfnWndProc = VxWindow__Process;
  wc.hInstance = GetModuleHandle(NULL);
  wc.cbSize = sizeof(WNDCLASSEX);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);

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

bool VxContext_ClearGraphics(VxContext *context) {
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

bool VxContext_Terminate(VxContext *context) {
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
