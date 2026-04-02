#include "Vx/Window.h" // IWYU pragma: associated
#include <stdbool.h>
#include <stdlib.h>
#include "Internal.h"

struct VxWindow {
  HWND hwnd;
};

bool VxWindow_Create(VxWindow **window, const int fps) {
  *window = calloc(1, sizeof(VxWindow));
  if (!window) return false;

  (*window)->hwnd = CreateWindowEx(
    0, Vx__WindowClass, Vx__WindowClass,
    WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
    800, 600, NULL, NULL, GetModuleHandle(NULL), 0
  );
  
  if (
    !(*window)->hwnd ||
    !ShowWindow((*window)->hwnd, SW_SHOW) ||
    !UpdateWindow((*window)->hwnd)
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
  while (GetMessage(&msg, NULL, 0, 0)) {
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

bool VxWindow_GetSize(const VxWindow *window, int *w, int *h) {
  if (!window || !w || !h) return false;

  RECT rect;
  if (!GetWindowRect(window->hwnd, &rect)) return false;

  *w = rect.right - rect.left;
  *h = rect.bottom - rect.top;

  return true;
}

bool VxWindow_SetSize(const VxWindow *window, int w, int h) {
  if (!window) return false;
  int x, y;
  
  VxWindow_GetPos(window, &x, &y);
  return MoveWindow(window->hwnd, x, y, w, h, TRUE);
}

bool VxWindow_GetPos(const VxWindow *window, int *x, int *y) {
  if (!window || !x || !y) return false;

  RECT rect;
  if (!GetWindowRect(window->hwnd, &rect)) return false;

  *x = rect.left;
  *y = rect.top;

  return true;
}

bool VxWindow_SetPos(const VxWindow *window, int x, int y) {
  if (!window) return false;
  int w, h;
  
  VxWindow_GetSize(window, &w, &h);
  return MoveWindow(window->hwnd, x, y, w, h, TRUE);
}

bool VxWindow_GetTitle(const VxWindow *window, char *buf, int len) {
  if (!window || !buf || len <= 0) return false;
  return GetWindowText(window->hwnd, buf, len) != 0;
}

bool VxWindow_SetTitle(const VxWindow *window, char *buf) {
  if (!window || !buf) return false;
  return SetWindowText(window->hwnd, buf);
}
