#include "Vx/Window.h" // IWYU pragma: associated
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "Internal.h"

struct VxWindow {
  HWND hwnd;
};

bool VxWindow_Create(VxWindow **window, const uint8_t fps) {
  *window = calloc(1, sizeof(VxWindow));
  if (!window) return false;

  (*window)->hwnd = CreateWindowEx(
    WS_EX_LAYERED, Vx__WindowClass, Vx__WindowClass,
    WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
    800, 600, NULL, NULL, GetModuleHandle(NULL), 0
  );
  
  if (
    !(*window)->hwnd ||
    !VxWindow_Show(*window)
  ) return false;

  if (
    fps > 0 &&
    !SetTimer((*window)->hwnd, 1, 1000 / fps, NULL)
  ) return false;

  return true;
}

bool VxWindow_Update(VxWindow *window) {
  if (!window) return false;

  MSG msg = {0};
  while (GetMessage(&msg, NULL, 0, 0) > 0) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  
  return true;
}

bool VxWindow_IsOpen(const VxWindow *window) {
  return window && IsWindow(window->hwnd);
}

bool VxWindow_Delete(VxWindow *window) {
  if (
    !window ||
    (IsWindow(window->hwnd) && !DestroyWindow(window->hwnd))
  ) return false;
  
  free(window);
  window = NULL;
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
  
  VxWindow_GetPos(window, &x, &y);
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
  
  VxWindow_GetSize(window, &w, &h);
  return MoveWindow(window->hwnd, x, y, w, h, TRUE);
}

bool VxWindow_GetTitle(const VxWindow *window, char *buf, const size_t len) {
  if (!window || !buf || len < 0) return false;
  GetWindowText(window->hwnd, buf, len);
  return GetLastError() == 0;
}

bool VxWindow_SetTitle(const VxWindow *window, const char *const title) {
  return window && title && SetWindowText(window->hwnd, title);
}

bool VxWindow_GetOpacity(const VxWindow *window, float *o) {
  if (!window) return false;

  BYTE alpha = 0;
  DWORD flags = 0;
  
  GetLayeredWindowAttributes(window->hwnd, NULL, &alpha, &flags);
  if (flags & LWA_ALPHA) {
    *o = alpha / 255.0f;
    return false;
  }

  return false;
}

bool VxWindow_SetOpacity(const VxWindow *window, const float o) {
  return window && SetLayeredWindowAttributes(window->hwnd, NULL, o * 255.0f, LWA_ALPHA);
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
