#include "Vx/Lifecycle.h" // IWYU pragma: associated
#include <stdbool.h>
#include "Internal.h"

LRESULT CALLBACK Vx__WindowProcess(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
  switch (umsg) {
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;

    default:
      return DefWindowProc(hwnd, umsg, wparam, lparam);
  }
}

bool Vx_Initiate(void) {
  WNDCLASSEX wc = {0};
  wc.lpszClassName = TEXT(Vx__WindowClass);
  wc.lpfnWndProc = Vx__WindowProcess;
  wc.hInstance = GetModuleHandle(NULL);
  wc.cbSize = sizeof(WNDCLASSEX);

  Vx__FalseCheck(RegisterClassEx(&wc), "Failed to register window class");
  return true;
}

bool Vx_Terminate(void) {
  Vx__FalseCheck(UnregisterClass(TEXT(Vx__WindowClass), GetModuleHandle(NULL)), "Failed to unregister window class");
  return true;
}
