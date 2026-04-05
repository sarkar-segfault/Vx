#include "Vx/Window.h" // IWYU pragma: associated
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "Internal.h"

struct VxWindow {
  HWND hwnd;
  UINT_PTR timer;
  uint8_t fps;
};

bool VxWindow_Create(VxWindow **window) {
  *window = calloc(1, sizeof(VxWindow));
  if (!*window) return false;

  (*window)->hwnd = CreateWindowEx(
    WS_EX_LAYERED, VxWindow_Class, VxWindow_DefaultTitle, WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT, VxWindow_DefaultWidth, VxWindow_DefaultHeight,
    NULL, NULL, GetModuleHandle(NULL), 0
  );
  
  if (
    !(*window)->hwnd ||
    !VxWindow_SetOpacity(*window, 1.0f) ||
    !VxWindow_Show(*window)
  ) {
    if ((*window)->hwnd) DestroyWindow((*window)->hwnd);
    free(*window);
    *window = NULL;
    return false;
  }

  return true;
}

bool VxWindow_Update(VxWindow *window) {
  if (!window) return false;

  MSG msg = {0};
  while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  
  return true;
}

bool VxWindow_IsOpen(const VxWindow *window) {
  return window && IsWindow(window->hwnd);
}

bool VxWindow_Delete(VxWindow **window) {
  if (!window || !*window) return false;
  if (IsWindow((*window)->hwnd) && !DestroyWindow((*window)->hwnd)) return false;
  
  free(*window);
  *window = NULL;
  return true;
}

bool VxWindow_GetFps(const VxWindow *window, uint8_t *fps) {
  if (!window || !fps) return false;
  *fps = window->fps;
  return true;
}

bool VxWindow_SetFps(VxWindow *window, const uint8_t fps) {
  if (!window) return false;
  window->fps = fps;

  if (window->timer != 0) {
    UINT_PTR timer = window->timer;
    window->timer = 0;
    if (!KillTimer(window->hwnd, timer)) return false;
  }

  if (fps != 0) {
    window->timer = SetTimer(window->hwnd, 0, 1000 / fps, NULL);
    if (!window->timer) return false;
  }

  return true;
}

bool VxWindow_GetSize(const VxWindow *window, uint32_t *w, uint32_t *h) {
  if (!window || !w || !h) return false;

  RECT rect;
  if (!GetWindowRect(window->hwnd, &rect)) return false;

  *w = rect.right - rect.left;
  *h = rect.bottom - rect.top;

  return true;
}

bool VxWindow_SetSize(const VxWindow *window, const uint32_t w, const uint32_t h) {
  if (!window) return false;
  int x, y;
  
  if (!VxWindow_GetPos(window, &x, &y)) return false;
  return MoveWindow(window->hwnd, x, y, w, h, TRUE);
}

bool VxWindow_GetPos(const VxWindow *window, int32_t *x, int32_t *y) {
  if (!window || !x || !y) return false;

  RECT rect;
  if (!GetWindowRect(window->hwnd, &rect)) return false;

  *x = rect.left;
  *y = rect.top;

  return true;
}

bool VxWindow_SetPos(const VxWindow *window, const int32_t x, const int32_t y) {
  if (!window) return false;
  uint32_t w, h;
  
  if (!VxWindow_GetSize(window, &w, &h)) return false;
  return MoveWindow(window->hwnd, x, y, w, h, TRUE);
}

bool VxWindow_GetTitle(const VxWindow *window, char *buf, const size_t len) {
  if (!window || !buf || len == 0) return false;
  GetWindowText(window->hwnd, buf, len);
  return true;
}

bool VxWindow_SetTitle(const VxWindow *window, const char *const title) {
  return window && title && SetWindowText(window->hwnd, title);
}

bool VxWindow_GetOpacity(const VxWindow *window, float *o) {
  if (!window || !o) return false;

  BYTE alpha = 0;
  DWORD flags = 0;
  
  GetLayeredWindowAttributes(window->hwnd, NULL, &alpha, &flags);
  if (flags & LWA_ALPHA) {
    *o = alpha / 255.0f;
    return true;
  }

  return false;
}

bool VxWindow_SetOpacity(const VxWindow *window, const float o) {
  return window && SetLayeredWindowAttributes(window->hwnd, 0, o * 255.0f, LWA_ALPHA);
}

bool VxWindow_Minimize(const VxWindow *window) {
  return window && ShowWindow(window->hwnd, SW_MINIMIZE);
}

bool VxWindow_Maximize(const VxWindow *window) {
  return window && ShowWindow(window->hwnd, SW_MAXIMIZE);
}

bool VxWindow_Restore(const VxWindow *window) {
  return window && ShowWindow(window->hwnd, SW_RESTORE);
}

bool VxWindow_Hide(const VxWindow *window) {
  return window && ShowWindow(window->hwnd, SW_HIDE);
}

bool VxWindow_Show(const VxWindow *window) {
  return window && ShowWindow(window->hwnd, SW_SHOW);
}

bool VxWindow_Focus(const VxWindow *window) {
  return window && SetForegroundWindow(window->hwnd);
}

bool VxWindow_Flash(const VxWindow *window) {
  if (!window) return false;

  FLASHWINFO fwi = {0};
  fwi.cbSize = sizeof(FLASHWINFO);
  fwi.hwnd = window->hwnd;
  fwi.dwFlags = FLASHW_TRAY | FLASHW_TIMERNOFG;
  return FlashWindowEx(&fwi);
}
