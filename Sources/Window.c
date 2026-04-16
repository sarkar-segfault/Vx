#include "Vx/Window.h"  // IWYU pragma: associated

#include <Vx/Event.h>
#include <stdlib.h>

#include "Internal.h"
#include "Vx/Context.h"
#include "Vx/Status.h"

struct VxWindow {
  HWND hwnd;
  MSG msg;
  bool open;
#ifdef VxContext_UseAngle
  EGLSurface surface;
  EGLContext econtext;
  VxContext *context;
#endif
};

VxStatus VxWindow_Create(VxWindow **window, VxContext *context) {
  if (!window) return VxStatus_BadInput;

  *window = calloc(1, sizeof(struct VxWindow));
  if (!*window) return VxStatus_AllocFail;

  (*window)->open = true;
  (*window)->hwnd = CreateWindowEx(WS_EX_LAYERED, VxWindow_Class, VxWindow_Class,
                                   WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, 800, 600, NULL, NULL,
                                   GetModuleHandle(NULL), 0);

  if (!(*window)->hwnd) {
    VxWindow_Delete(window);
    return VxStatus_WindowingFail;
  }

  if (!VxWindow_SetOpacity(*window, 1.0f)) {
    VxWindow_Delete(window);
    return VxStatus_WindowingFail;
  }

#ifdef VxContext_UseAngle
  (*window)->surface = EGL_NO_SURFACE;
  (*window)->econtext = EGL_NO_CONTEXT;

  if (context) {
    (*window)->context = context;
    void *display, *config;

    if (VxContext_GetDisplay(context, &display) != VxStatus_Pass ||
        VxContext_GetConfig(context, &config) != VxStatus_Pass) {
      VxWindow_Delete(window);
      return VxStatus_GraphicsFail;
    }

    (*window)->surface = eglCreateWindowSurface(display, config, (*window)->hwnd, NULL);

    if ((*window)->surface == EGL_NO_SURFACE) {
      VxWindow_Delete(window);
      return VxStatus_GraphicsFail;
    }

    (*window)->econtext = eglCreateContext(display, config, EGL_NO_CONTEXT, NULL);

    if ((*window)->econtext == EGL_NO_CONTEXT) {
      VxWindow_Delete(window);
      return VxStatus_GraphicsFail;
    }
  }
#endif

  return VxStatus_Pass;
}

Vx__Expose VxStatus VxWindow_GetSurface(VxWindow *window, void **surface) {
  if (!window || !surface) return VxStatus_BadInput;

  *surface = window->surface;
  return VxStatus_Pass;
}

VxStatus VxWindow_MountGraphics(VxWindow *window) {
#ifdef VxContext_UseAngle
  if (!window || !window->context) return VxStatus_BadInput;
  void *display;

  if (VxContext_GetDisplay(window->context, &display) != VxStatus_Pass)
    return VxStatus_GraphicsFail;

  if (!eglMakeCurrent(display, window->surface, window->surface, window->econtext))
    return VxStatus_GraphicsFail;
#endif

  return VxStatus_Pass;
}

VxStatus VxWindow_Close(VxWindow *window) {
  if (!window) return VxStatus_BadInput;

  window->open = false;
  return VxStatus_Pass;
}

VxStatus VxWindow_Open(VxWindow *window) {
  if (!window) return VxStatus_BadInput;

  window->open = true;
  return VxStatus_Pass;
}

bool VxWindow_IsOpen(const VxWindow *window) {
  return window && IsWindow(window->hwnd) && window->open;
}

VxStatus VxWindow_PollEvents(VxWindow *window) {
  if (!window) return VxStatus_BadInput;

  while (PeekMessage(&window->msg, window->hwnd, 0, 0, PM_REMOVE) > 0) {
    TranslateMessage(&window->msg);
    DispatchMessage(&window->msg);
  }

  return VxStatus_Pass;
}

VxStatus VxWindow_PopEvent(VxWindow *window, VxEvent *event) {
  if (!window || !event) return VxStatus_BadInput;

  VxWindowData data = (VxWindowData)GetWindowLongPtr(window->hwnd, GWLP_USERDATA);
  return VxEventRing_Pop(&data->ring, event);
}

VxStatus VxWindow_PutEvent(VxWindow *window, VxEvent event) {
  if (!window) return VxStatus_BadInput;

  VxWindowData data = (VxWindowData)GetWindowLongPtr(window->hwnd, GWLP_USERDATA);
  return VxEventRing_Put(&data->ring, event);
}

VxStatus VxWindow_Delete(VxWindow **window) {
  if (!window || !*window) return VxStatus_BadInput;

  VxStatus s = VxStatus_Pass;

#ifdef VxContext_UseAngle
  if ((*window)->context) {
    if (!VxContext_ClearGraphics((*window)->context)) s = VxStatus_GraphicsFail;
    void *display;

    if (VxContext_GetDisplay((*window)->context, &display) != VxStatus_Pass)
      s = VxStatus_GraphicsFail;

    if ((*window)->surface != EGL_NO_SURFACE && !eglDestroySurface(display, (*window)->surface))
      s = VxStatus_GraphicsFail;

    if ((*window)->econtext != EGL_NO_CONTEXT &&
        !eglDestroyContext(display, (*window)->econtext))
      s = VxStatus_GraphicsFail;
  }
#endif

  if (IsWindow((*window)->hwnd) && !DestroyWindow((*window)->hwnd)) s = VxStatus_WindowingFail;

  free(*window);
  *window = NULL;
  return s;
}

VxStatus VxWindow_GetSize(const VxWindow *window, uint32_t *w, uint32_t *h) {
  if (!window || !w || !h) return VxStatus_BadInput;

  RECT rect;
  if (!GetWindowRect(window->hwnd, &rect)) return VxStatus_WindowingFail;

  *w = rect.right - rect.left;
  *h = rect.bottom - rect.top;
  return VxStatus_Pass;
}

VxStatus VxWindow_SetSize(const VxWindow *window, const uint32_t w, const uint32_t h) {
  if (!window) return VxStatus_BadInput;

  int32_t x, y;
  if (!VxWindow_GetPos(window, &x, &y) || !MoveWindow(window->hwnd, x, y, w, h, TRUE))
    return VxStatus_WindowingFail;

  return VxStatus_Pass;
}

VxStatus VxWindow_GetPos(const VxWindow *window, int32_t *x, int32_t *y) {
  if (!window || !x || !y) return VxStatus_BadInput;

  RECT rect;
  if (!GetWindowRect(window->hwnd, &rect)) return VxStatus_WindowingFail;

  *x = rect.left;
  *y = rect.top;
  return VxStatus_Pass;
}

VxStatus VxWindow_SetPos(const VxWindow *window, const int32_t x, const int32_t y) {
  if (!window) return VxStatus_BadInput;

  uint32_t w, h;
  if (!VxWindow_GetSize(window, &w, &h) || !MoveWindow(window->hwnd, x, y, w, h, TRUE))
    return VxStatus_WindowingFail;

  return VxStatus_Pass;
}

VxStatus VxWindow_GetTitle(const VxWindow *window, char *buf, const size_t len) {
  if (!window || !buf || len == 0) return VxStatus_BadInput;

  GetWindowText(window->hwnd, buf, len);
  return VxStatus_Pass;
}

VxStatus VxWindow_SetTitle(const VxWindow *window, const char *const title) {
  if (!window || !title) return VxStatus_BadInput;

  if (!SetWindowText(window->hwnd, title)) return VxStatus_WindowingFail;

  return VxStatus_Pass;
}

VxStatus VxWindow_GetOpacity(const VxWindow *window, float *o) {
  if (!window || !o) return VxStatus_BadInput;

  BYTE alpha = 0;
  DWORD flags = 0;

  GetLayeredWindowAttributes(window->hwnd, NULL, &alpha, &flags);
  if (flags & LWA_ALPHA) {
    *o = alpha / 255.0f;
    return VxStatus_Pass;
  }

  return VxStatus_WindowingFail;
}

VxStatus VxWindow_SetOpacity(const VxWindow *window, const float o) {
  if (!window || !SetLayeredWindowAttributes(window->hwnd, 0,
                                             ((o < 0.0f)   ? 0.0f
                                              : (o > 1.0f) ? 1.0f
                                                           : o) *
                                                 255.0f,
                                             LWA_ALPHA)) {
    return VxStatus_WindowingFail;
  }

  return VxStatus_Pass;
}

VxStatus VxWindow_Minimize(const VxWindow *window) {
  if (!window || !ShowWindow(window->hwnd, SW_MINIMIZE)) return VxStatus_WindowingFail;

  return VxStatus_Pass;
}

VxStatus VxWindow_Maximize(const VxWindow *window) {
  if (!window || !ShowWindow(window->hwnd, SW_MAXIMIZE)) return VxStatus_WindowingFail;

  return VxStatus_Pass;
}

VxStatus VxWindow_Restore(const VxWindow *window) {
  if (!window || !ShowWindow(window->hwnd, SW_RESTORE)) return VxStatus_WindowingFail;

  return VxStatus_Pass;
}

VxStatus VxWindow_Hide(const VxWindow *window) {
  if (!window || !ShowWindow(window->hwnd, SW_HIDE)) return VxStatus_WindowingFail;

  return VxStatus_Pass;
}

VxStatus VxWindow_Show(const VxWindow *window) {
  if (!window || !ShowWindow(window->hwnd, SW_SHOW)) return VxStatus_WindowingFail;

  return VxStatus_Pass;
}

VxStatus VxWindow_Focus(const VxWindow *window) {
  if (!window || !SetForegroundWindow(window->hwnd)) return VxStatus_WindowingFail;

  return VxStatus_Pass;
}

VxStatus VxWindow_Flash(const VxWindow *window) {
  if (!window) return VxStatus_WindowingFail;

  FLASHWINFO fwi = {0};
  fwi.cbSize = sizeof(FLASHWINFO);
  fwi.hwnd = window->hwnd;
  fwi.dwFlags = FLASHW_TRAY | FLASHW_TIMERNOFG;

  if (!FlashWindowEx(&fwi)) return VxStatus_WindowingFail;

  return VxStatus_Pass;
}

VxStatus VxWindow_GetHandle(const VxWindow *window, void **handle) {
  if (!window || !handle) return VxStatus_BadInput;

  *handle = window->hwnd;
  return VxStatus_Pass;
}
