#include "Vx/Lifecycle.h" // IWYU pragma: associated
#include <stdbool.h>
#include "Internal.h"

LRESULT CALLBACK VxWindow__Process(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
  switch (umsg) {
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;

    case WM_TIMER:
      InvalidateRect(hwnd, NULL, TRUE);
      UpdateWindow(hwnd);
      return 0;

    default:
      return DefWindowProc(hwnd, umsg, wparam, lparam);
  }
}

bool Vx_Initiate(void) {
  WNDCLASSEX wc = {0};
  wc.lpszClassName = VxWindow_Class;
  wc.lpfnWndProc = VxWindow__Process;
  wc.hInstance = GetModuleHandle(NULL);
  wc.cbSize = sizeof(WNDCLASSEX);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW+1;

  return RegisterClassEx(&wc);
}

bool Vx_Terminate(void) {
  return UnregisterClass(Vx__WindowClass, GetModuleHandle(NULL));
}
