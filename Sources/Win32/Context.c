#include "Vx/Context.h"

#include <stdbool.h>

#include "Internal.h"

Vx__Extern LRESULT CALLBACK VxWindow__Process(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

VxStatus VxContext_Create(VxContext **context) {
  WNDCLASSEX wc = {0};
  wc.lpszClassName = VxWindow_Class;
  wc.lpfnWndProc = VxWindow__Process;
  wc.hInstance = GetModuleHandle(NULL);
  wc.cbSize = sizeof(WNDCLASSEX);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);

  if (!RegisterClassEx(&wc)) return VxStatus_WindowingFail;

  if (!context) return VxStatus_Pass;

  *context = calloc(1, sizeof(struct VxContext));
  if (!*context) return VxStatus_AllocFail;

#ifdef VxContext_UseAngle
  EGLint display_spec[] = {EGL_PLATFORM_ANGLE_TYPE_ANGLE, EGL_PLATFORM_ANGLE_TYPE_D3D11_ANGLE,
                           EGL_NONE};

  PFNEGLGETPLATFORMDISPLAYEXTPROC eglGetPlatformDisplayEXT =
      (PFNEGLGETPLATFORMDISPLAYEXTPROC)eglGetProcAddress("eglGetPlatformDisplayEXT");

  (*context)->display =
      eglGetPlatformDisplayEXT(EGL_PLATFORM_ANGLE_ANGLE, EGL_DEFAULT_DISPLAY, display_spec);

  if ((*context)->display == EGL_NO_DISPLAY || !eglInitialize((*context)->display, NULL, NULL)) {
    VxContext_Delete(context);
    return VxStatus_GraphicsFail;
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

  if (!eglChooseConfig((*context)->display, config_spec, &(*context)->config, 1, &num) ||
      num == 0) {
    VxContext_Delete(context);
    return VxStatus_GraphicsFail;
  }
#endif

  return VxStatus_Pass;
}

VxStatus VxContext_ClearGraphics(VxContext *context) {
#ifdef VxContext_UseAngle
  if (!context) return VxStatus_BadInput;

  if (!eglMakeCurrent(context->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT))
    return VxStatus_GraphicsFail;

  return VxStatus_Pass;
#else
  return VxStatus_NotConfigured;
#endif
}

VxStatus VxContext_GetDisplay(VxContext *context, void **display) {
#ifdef VxContext_UseAngle
  if (context && display) {
    *display = context->display;
    return VxStatus_Pass;
  } else
    return VxStatus_BadInput;
#else
  return VxStatus_NotConfigured;
#endif
}

VxStatus VxContext_Delete(VxContext **context) {
  VxStatus s = VxStatus_Pass;

  if (context && *context) {
#ifdef VxContext_UseAngle
    if (*context && !eglTerminate((*context)->display)) s = VxStatus_GraphicsFail;
#endif

    free(*context);
    *context = NULL;
  }

  if (!UnregisterClass(VxWindow_Class, GetModuleHandle(NULL))) s = VxStatus_WindowingFail;

  return s;
}
