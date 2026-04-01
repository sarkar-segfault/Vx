#include "Vx/Window.h" // IWYU pragma: associated
#include <stdbool.h>
#include <stdlib.h>
#include "Internal.h"

struct VxWindow {
  HWND hwnd;
};

bool VxWindow_Create(VxWindow **window) {
  *window = calloc(1, sizeof(VxWindow));
  if (!window) return false;

  (*window)->hwnd = CreateWindowEx(
    0, Vx__WindowClass, Vx__WindowClass,
    WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
    800, 600, NULL, NULL, GetModuleHandle(NULL), 0
  );
  if (!(*window)->hwnd) return false;

  ShowWindow((*window)->hwnd, SW_SHOW);
  UpdateWindow((*window)->hwnd);

  return true;
}

bool VxWindow_Update(VxWindow *window) {
  if (!window) return false;

  MSG msg = {0};
  while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  
  return true;
}

bool VxWindow_IsOpen(const VxWindow *window) {
  return window && IsWindow(window->hwnd);
}

bool VxWindow_Delete(VxWindow *window) {
  if (!window) return false;
  if (IsWindow(window->hwnd) && !DestroyWindow(window->hwnd)) return false;
  
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

bool VxWindow_SetTargetFps(const VxWindow *window, const int fps) {
  if (!window || fps == 0) return false;

  SetTimer(window->hwnd, 1, 1000 / fps, NULL);

  return true;
}
