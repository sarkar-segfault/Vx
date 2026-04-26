#include "Vx/Window.h"  // IWYU pragma: associated

#include <Vx/Event.h>
#include <stdlib.h>

#include "Internal.h"
#include "Vx/Status.h"

struct VxWindow {
  HWND hwnd;
  MSG msg;
  bool open;
};

VxStatus VxWindow_Create(VxWindow **window, const VxFlags flags) {
  if (!window) return VxStatus_BadInput;

  *window = calloc(1, sizeof(struct VxWindow));
  if (!*window) return VxStatus_AllocFail;

  (*window)->open = true;

  (*window)->hwnd =
      CreateWindowEx(flags & VxFlag_Layered ? WS_EX_LAYERED : 0, VxWindow_Class, VxWindow_Class,
                     WS_OVERLAPPEDWINDOW | (flags & VxFlag_Visible ? WS_VISIBLE : 0), 0, 0, 800,
                     600, NULL, NULL, GetModuleHandle(NULL), (LPVOID)(intptr_t)flags);

  if (!(*window)->hwnd) {
    VxWindow_Delete(window);
    return VxStatus_WindowingFail;
  }

  if (flags & VxFlag_Maximized && !VxWindow_Maximize(*window)) {
    VxWindow_Delete(window);
    return VxStatus_WindowingFail;
  } else if (flags & VxFlag_Minimized && !VxWindow_Minimize(*window)) {
    VxWindow_Delete(window);
    return VxStatus_WindowingFail;
  }

  if (flags & VxFlag_Layered && !VxWindow_SetOpacity(*window, 1.0f)) {
    VxWindow_Delete(window);
    return VxStatus_WindowingFail;
  }

  return VxStatus_Pass;
}

bool VxWindow_GetFlag(const VxWindow *window, VxFlag flag) {
  if (window) {
    VxFlags flags = ((VxWindowData *)GetWindowLongPtr(window->hwnd, GWLP_USERDATA))->flags;
    return flags & flag;
  } else
    return false;
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

  while (PeekMessage(&window->msg, window->hwnd, 0, 0, PM_REMOVE)) {
    TranslateMessage(&window->msg);
    DispatchMessage(&window->msg);
  }

  return VxStatus_Pass;
}

VxStatus VxWindow_PopEvent(const VxWindow *window, VxEvent *event) {
  if (!window || !event) return VxStatus_BadInput;

  VxWindowData *data = (VxWindowData *)GetWindowLongPtr(window->hwnd, GWLP_USERDATA);
  return VxEventRing_Pop(&data->ring, event);
}

VxStatus VxWindow_PutEvent(const VxWindow *window, VxEvent event) {
  if (!window) return VxStatus_BadInput;

  VxWindowData *data = (VxWindowData *)GetWindowLongPtr(window->hwnd, GWLP_USERDATA);
  return VxEventRing_Put(&data->ring, event);
}

VxStatus VxWindow_Delete(VxWindow **window) {
  if (!window || !*window) return VxStatus_BadInput;

  VxStatus s = VxStatus_Pass;
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
  if (!VxWindow_GetFlag(window, VxFlag_Layered)) return VxStatus_NotConfigured;
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

#define Vx__Clamp(val, min, max) (val < min) ? min : (val > max) ? max : o

VxStatus VxWindow_SetOpacity(const VxWindow *window, const float o) {
  if (!VxWindow_GetFlag(window, VxFlag_Layered)) return VxStatus_NotConfigured;

  if (!window ||
      !SetLayeredWindowAttributes(window->hwnd, 0, Vx__Clamp(o, 0.0f, 1.0f) * 255.0f, LWA_ALPHA)) {
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
