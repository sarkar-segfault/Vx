#include "Vx/Window.h" // IWYU pragma: associated
#include <stdbool.h>
#include <stdlib.h>
#include "Vx/Lifecycle.h"

#ifdef _WIN32
  #define NOMINMAX
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
#else
  #error "Vx only supports Win32 as of now..."
#endif

struct VxWindow {
  HWND hwnd;
};

bool VxWindow_Create(VxWindow **window) {
  *window = calloc(1, sizeof(VxWindow));
  if (!window) return false;

  (*window)->hwnd = CreateWindowEx(
    0, Vx__WindowClass, Vx__WindowClass,
    WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
    CW_USEDEFAULT, 800, 600, NULL, NULL,
    GetModuleHandle(NULL), NULL
  );

  ShowWindow((*window)->hwnd, SW_SHOW);
  UpdateWindow((*window)->hwnd);

  if (!(*window)->hwnd) return false;
  return true;
}

void VxWindow_Update(const VxWindow *window) {
  MSG msg = {0};
  while (GetMessage(&msg, window->hwnd, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}

bool VxWindow_IsOpen(const VxWindow *window) {
  if (!window) return false;
  if (!window->hwnd) return false;
  if (!IsWindow(window->hwnd)) return false;
  return true;
}

bool VxWindow_Delete(VxWindow *window) {
  if (!window) return false;
  if (!DestroyWindow(window->hwnd)) return false;

  window->hwnd = NULL;
  return true;
}
