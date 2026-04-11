#include "Vx/Window.h"  // IWYU pragma: associated

#include <Vx/Event.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "Internal.h"
#include "Vx/Context.h"

struct VxWindow {
  HWND hwnd;
  UINT_PTR timer;
  uint8_t fps;
  MSG msg;
  bool open;
#ifdef VxContext_UseAngle
  EGLSurface surface;
  EGLContext econtext;
  VxContext context;
#endif
};

bool VxWindow_Create(VxWindow *window, VxContext context) {
  if (!window) {
    Vx__Error("called with invalid args");
    return false;
  }

  *window = calloc(1, sizeof(struct VxWindow));
  if (!*window) {
    Vx__Error("failed to allocate window");
    return false;
  }

  (*window)->open = true;

  VxEventRing ring = calloc(1, sizeof(struct VxEventRing));
  if (!ring) {
    Vx__Error("failed to allocate event ring");
    goto terminate;
  }

  (*window)->hwnd =
      CreateWindowEx(WS_EX_LAYERED, VxWindow_Class, VxWindow_DefaultTitle, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT,
                     CW_USEDEFAULT, VxWindow_DefaultWidth, VxWindow_DefaultHeight, NULL, NULL, GetModuleHandle(NULL), 0);

  if (!(*window)->hwnd) {
    Vx__Error("failed to create window");
    goto terminate;
  }

  if (!VxWindow_SetOpacity(*window, 1.0f)) {
    Vx__Error("failed to set opacity");
    goto terminate;
  }

#ifdef VxContext_UseAngle
  if (context) {
    (*window)->context = context;

    (*window)->surface = eglCreateWindowSurface(context->display, context->config, (*window)->hwnd, NULL);
    if (!(*window)->surface) {
      Vx__Error("failed to create window surface");
      goto terminate;
    }

    (*window)->econtext = eglCreateContext(context->display, context->config, EGL_NO_CONTEXT, NULL);
    if (!(*window)->econtext) {
      Vx__Error("failed to create window context");
      goto terminate;
    }
  }
#endif

  SetWindowLongPtr((*window)->hwnd, GWLP_USERDATA, (LONG_PTR)ring);
  return true;

terminate:
  free(ring);
  VxWindow_Delete(window);
  return false;
}

bool VxWindow_MountGraphics(VxWindow window) {
#ifdef VxContext_UseAngle
  if (!window || !window->context) {
    Vx__Error("called with invalid args");
    return false;
  }

  if (!eglMakeCurrent(window->context->display, window->surface, window->surface, window->econtext)) {
    Vx__Error("failed to mount window context");
    return false;
  }
#endif

  return true;
}

bool VxWindow_Close(VxWindow window) {
  if (!window) {
    Vx__Error("called with invalid args");
    return false;
  }

  window->open = false;
  return true;
}

bool VxWindow_Open(VxWindow window) {
  if (!window) {
    Vx__Error("called with invalid args");
    return false;
  }

  window->open = true;
  return true;
}

bool VxWindow_IsOpen(const VxWindow window) { return window && IsWindow(window->hwnd) && window->open; }

bool VxWindow_PollEvents(VxWindow window) {
  if (!window) {
    Vx__Error("called with invalid args");
    return false;
  }

  while (PeekMessage(&window->msg, window->hwnd, 0, 0, PM_REMOVE) > 0) {
    TranslateMessage(&window->msg);
    DispatchMessage(&window->msg);
  }

  return true;
}

bool VxWindow_PopEvent(VxWindow window, VxEvent *event) {
  if (!window || !event) {
    Vx__Error("called with invalid args");
    return false;
  }

  VxEventRing ring = (VxEventRing)GetWindowLongPtr(window->hwnd, GWLP_USERDATA);
  return VxEventRing_Pop(ring, event);
}

bool VxWindow_PutEvent(VxWindow window, VxEvent event) {
  if (!window) {
    Vx__Error("called with invalid args");
    return false;
  }

  VxEventRing ring = (VxEventRing)GetWindowLongPtr(window->hwnd, GWLP_USERDATA);
  return VxEventRing_Put(ring, event);
}

bool VxWindow_Delete(VxWindow *window) {
  if (!window || !*window) {
    Vx__Error("called with invalid args");
    return false;
  }

#ifdef VxContext_UseAngle
  if ((*window)->context) {
    if (!VxContext_ClearGraphics((*window)->context)) return false;

    if (!eglDestroySurface((*window)->context->display, (*window)->surface)) {
      Vx__Error("failed to deallocate window surface");
      return false;
    }

    if (!eglDestroyContext((*window)->context->display, (*window)->econtext)) {
      Vx__Error("failed to deallocate window context");
      return false;
    }
  }
#endif

  if (IsWindow((*window)->hwnd) && !DestroyWindow((*window)->hwnd)) {
    Vx__Error("failed to destroy window");
    return false;
  }

  free(*window);
  *window = NULL;
  return true;
}

bool VxWindow_GetFps(const VxWindow window, uint8_t *fps) {
  if (!window || !fps) {
    Vx__Error("called with invalid args");
    return false;
  }
  *fps = window->fps;
  return true;
}

bool VxWindow_SetFps(VxWindow window, const uint8_t fps) {
  if (!window) {
    Vx__Error("called with invalid args");
    return false;
  }

  window->fps = fps;

  if (window->timer != 0) {
    UINT_PTR timer = window->timer;
    window->timer = 0;
    if (!KillTimer(window->hwnd, timer)) {
      Vx__Error("failed to kill timer");
      return false;
    }
  }

  if (fps != 0) {
    window->timer = SetTimer(window->hwnd, 0, 1000 / fps, NULL);
    if (!window->timer) {
      Vx__Error("failed to set timer");
      return false;
    }
  }

  return true;
}

bool VxWindow_GetSize(const VxWindow window, uint32_t *w, uint32_t *h) {
  if (!window || !w || !h) {
    Vx__Error("called with invalid args");
    return false;
  }

  RECT rect;
  if (!GetWindowRect(window->hwnd, &rect)) {
    Vx__Error("failed to get window rect");
    return false;
  }

  *w = rect.right - rect.left;
  *h = rect.bottom - rect.top;
  return true;
}

bool VxWindow_SetSize(const VxWindow window, const uint32_t w, const uint32_t h) {
  if (!window) {
    Vx__Error("called with invalid args");
    return false;
  }

  int x, y;
  if (!VxWindow_GetPos(window, &x, &y)) {
    Vx__Error("failed to get window pos");
    return false;
  }

  if (!MoveWindow(window->hwnd, x, y, w, h, TRUE)) {
    Vx__Error("failed to resize window");
    return false;
  }
  return true;
}

bool VxWindow_GetPos(const VxWindow window, int32_t *x, int32_t *y) {
  if (!window || !x || !y) {
    Vx__Error("called with invalid args");
    return false;
  }

  RECT rect;
  if (!GetWindowRect(window->hwnd, &rect)) {
    Vx__Error("failed to get window rect");
    return false;
  }

  *x = rect.left;
  *y = rect.top;
  return true;
}

bool VxWindow_SetPos(const VxWindow window, const int32_t x, const int32_t y) {
  if (!window) {
    Vx__Error("called with invalid args");
    return false;
  }

  uint32_t w, h;
  if (!VxWindow_GetSize(window, &w, &h)) {
    Vx__Error("failed to get window size");
    return false;
  }

  if (!MoveWindow(window->hwnd, x, y, w, h, TRUE)) {
    Vx__Error("failed to move window");
    return false;
  }

  return true;
}

bool VxWindow_GetTitle(const VxWindow window, char *buf, const size_t len) {
  if (!window || !buf || len == 0) {
    Vx__Error("called with invalid args");
    return false;
  }

  GetWindowText(window->hwnd, buf, len);
  return true;
}

bool VxWindow_SetTitle(const VxWindow window, const char *const title) {
  if (!window || !title) {
    Vx__Error("called with invalid args");
    return false;
  }

  if (!SetWindowText(window->hwnd, title)) {
    Vx__Error("failed to set window title");
    return false;
  }

  return true;
}

bool VxWindow_GetOpacity(const VxWindow window, float *o) {
  if (!window || !o) {
    Vx__Error("called with invalid args");
    return false;
  }

  BYTE alpha = 0;
  DWORD flags = 0;

  GetLayeredWindowAttributes(window->hwnd, NULL, &alpha, &flags);
  if (flags & LWA_ALPHA) {
    *o = alpha / 255.0f;
    return true;
  }

  Vx__Error("failed to extract alpha");
  return false;
}

bool VxWindow_SetOpacity(const VxWindow window, const float o) {
  if (!window || !SetLayeredWindowAttributes(window->hwnd, 0,
                                             ((o < 0.0f)   ? 0.0f
                                              : (o > 1.0f) ? 1.0f
                                                           : o) *
                                                 255.0f,
                                             LWA_ALPHA)) {
    Vx__Error("failed to set window opacity");
    return false;
  }

  return true;
}

bool VxWindow_Minimize(const VxWindow window) {
  if (!window || !ShowWindow(window->hwnd, SW_MINIMIZE)) {
    Vx__Error("failed to minimize window");
    return false;
  }

  return true;
}

bool VxWindow_Maximize(const VxWindow window) {
  if (!window || !ShowWindow(window->hwnd, SW_MAXIMIZE)) {
    Vx__Error("failed to maximize window");
    return false;
  }

  return true;
}

bool VxWindow_Restore(const VxWindow window) {
  if (!window || !ShowWindow(window->hwnd, SW_RESTORE)) {
    Vx__Error("failed to restore window");
    return false;
  }

  return true;
}

bool VxWindow_Hide(const VxWindow window) {
  if (!window || !ShowWindow(window->hwnd, SW_HIDE)) {
    Vx__Error("failed to hide window");
    return false;
  }

  return true;
}

bool VxWindow_Show(const VxWindow window) {
  if (!window || !ShowWindow(window->hwnd, SW_SHOW)) {
    Vx__Error("failed to show window");
    return false;
  }

  return true;
}

bool VxWindow_Focus(const VxWindow window) {
  if (!window || !SetForegroundWindow(window->hwnd)) {
    Vx__Error("failed to focus window");
    return false;
  }

  return true;
}

bool VxWindow_Flash(const VxWindow window) {
  if (!window) {
    Vx__Error("called with invalid args");
    return false;
  }

  FLASHWINFO fwi = {0};
  fwi.cbSize = sizeof(FLASHWINFO);
  fwi.hwnd = window->hwnd;
  fwi.dwFlags = FLASHW_TRAY | FLASHW_TIMERNOFG;

  if (!FlashWindowEx(&fwi)) {
    Vx__Error("failed to flash window");
    return false;
  }

  return true;
}

bool VxWindow_GetHandle(const VxWindow window, void **ptr) {
  if (!window || !ptr) {
    Vx__Error("called with invalid args");
    return false;
  }
  *ptr = window->hwnd;
  return true;
}
