#include "Vx/Lifecycle.h" // IWYU pragma: associated
#include <stdbool.h>
#include "Internal.h"

#ifdef _WIN32
  #define NOMINMAX
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
#else
  #error "Vx only supports Win32 as of now..."
#endif

LRESULT CALLBACK Vx__WindowProcess(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
  switch (umsg) {
    case WM_NCCREATE:
      SetWindowLongPtr(hwnd, GWLP_USERDATA, 1);
      return TRUE;
    
    case WM_DESTROY:
      SetWindowLongPtr(hwnd, GWLP_USERDATA, 0);
      PostQuitMessage(0);
      return 0;

    default:
      return DefWindowProc(hwnd, umsg, wparam, lparam);
  }
}

bool Vx_Initiate(void) {
  WNDCLASSEX wc = {0};
  wc.lpszClassName = Vx__WindowClass;
  wc.lpfnWndProc = Vx__WindowProcess;
  wc.hInstance = GetModuleHandle(NULL);
  wc.cbSize = sizeof(WNDCLASSEX);

  Vx__FalseCheck(RegisterClassEx(&wc), "Failed to register window class");
  return true;
}

bool Vx_Terminate(void) {
  Vx__FalseCheck(UnregisterClass(Vx__WindowClass, GetModuleHandle(NULL)), "Failed to unregister window class");
  return true;
}
