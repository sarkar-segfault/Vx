#include "Vx/Window.h" // IWYU pragma: associated
#include <stdbool.h>
#include <stdlib.h>
#include "Internal.h"

#define Vx__WindowRect(name, hwnd) RECT name; Vx__FalseCheck(GetWindowRect(hwnd, &name), "Failed to obtain window rect")

struct VxWindow {
  HWND hwnd;
};

bool VxWindow_Create(VxWindow **window) {
  *window = calloc(1, sizeof(VxWindow));
  Vx__FalseCheck(window, "Failed to calloc window");

  (*window)->hwnd = CreateWindowEx(
    0, TEXT(Vx__WindowClass), TEXT(Vx__WindowClass),
    WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
    800, 600, NULL, NULL, GetModuleHandle(NULL), 0
  );
  Vx__FalseCheck((*window)->hwnd, "Failed to create window");

  ShowWindow((*window)->hwnd, SW_SHOW);
  UpdateWindow((*window)->hwnd);

  return true;
}

bool VxWindow_Update(VxWindow *window) {
  Vx__FalseCheck(window, "Passed NULL to VxWindow_Update");

  MSG msg = {0};
  while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  
  return true;
}

bool VxWindow_IsOpen(const VxWindow *window) {
  Vx__FalseCheck(window, "Passed NULL to VxWindow_IsOpen");
  Vx__FalseCheckNoLog(IsWindow(window->hwnd));
  return true;
}

bool VxWindow_Delete(VxWindow *window) {
  Vx__FalseCheck(window, "Passed NULL to VxWindow_Delete");
  if (IsWindow(window->hwnd)) {
    Vx__FalseCheck(DestroyWindow(window->hwnd), "Failed to destroy window");
  }
  
  free(window);
  window = NULL;
  return true;
}

bool VxWindow_GetSize(const VxWindow *window, int *w, int *h) {
  Vx__FalseCheck(window, "Passed NULL to VxWindow_GetSize");
  Vx__WindowRect(rect, window->hwnd);

  *w = rect.right - rect.left;
  *h = rect.bottom - rect.top;

  return true;
}

bool VxWindow_GetPos(const VxWindow *window, int *x, int *y) {
  Vx__FalseCheck(window, "Passed NULL to VxWindow_GetPos");
  Vx__WindowRect(rect, window->hwnd);

  *x = rect.left;
  *y = rect.top;

  return true;
}
