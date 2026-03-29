/**
  @file Window.c
  @since 0.1.0
  @license MIT
  @author Adhrit Sarkar <adhritsarkar@proton.me>
  @brief Defines functionality for VxWindow.h; as of now, only supports windows.
*/

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

typedef struct VxWindow {
  HWND hwnd;
} VxWindow;

bool VxWindow_Create(VxWindow **window) {
  *window = calloc(1, sizeof(VxWindow));
  if (!window) return false;

  WNDCLASS *wc = Vx_GetWindowClass();  
  (*window)->hwnd = CreateWindowEx(
    0, wc->lpszClassName, wc->lpszClassName,
    WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
    CW_USEDEFAULT, 800, 600, NULL, NULL,
    wc->hInstance, NULL
  );

  ShowWindow((*window)->hwnd, SW_SHOW);
  UpdateWindow((*window)->hwnd);

  if (!(*window)->hwnd) return false;
  return true;
}

void VxWindow_Update(VxWindow *window) {
  MSG msg = {};
  while (GetMessage(&msg, window->hwnd, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}

bool VxWindow_IsOpen(VxWindow *window) {
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
