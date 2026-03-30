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

#define Vx_FalseCheck(VAL) if (!VAL) return false
#define Vx_WindowRect(NAME, HWND) RECT NAME; Vx_FalseCheck(GetWindowRect(HWND, &NAME))

struct VxWindow {
  HWND hwnd;
};

bool VxWindow_Create(VxWindow **window) {
  *window = calloc(1, sizeof(VxWindow));
  Vx_FalseCheck(window);

  (*window)->hwnd = CreateWindowEx(
    0, Vx__WindowClass, Vx__WindowClass,
    WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
    CW_USEDEFAULT, 800, 600, NULL, NULL,
    GetModuleHandle(NULL), NULL
  );

  ShowWindow((*window)->hwnd, SW_SHOW);
  UpdateWindow((*window)->hwnd);

  Vx_FalseCheck((*window)->hwnd);
  return true;
}

bool VxWindow_Update(const VxWindow *window) {
  Vx_FalseCheck(window);
  
  MSG msg = {0};
  while (GetMessage(&msg, window->hwnd, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return true;
}

bool VxWindow_IsOpen(const VxWindow *window) {
  Vx_FalseCheck(window);
  Vx_FalseCheck(IsWindow(window->hwnd));
  return true;
}

bool VxWindow_Delete(VxWindow *window) {
  Vx_FalseCheck(window);
  Vx_FalseCheck(DestroyWindow(window->hwnd));

  window = NULL;
  return true;
}

bool VxWindow_GetSize(const VxWindow *window, int *w, int *h) {
  Vx_FalseCheck(window);
  Vx_WindowRect(rect, window->hwnd);

  *w = rect.right - rect.left;
  *h = rect.bottom - rect.top;

  return true;
}

bool VxWindow_GetPos(const VxWindow *window, int *x, int *y) {
  Vx_FalseCheck(window);
  Vx_WindowRect(rect, window->hwnd);  

  *x = rect.left;
  *y = rect.top;

  return true;
}
