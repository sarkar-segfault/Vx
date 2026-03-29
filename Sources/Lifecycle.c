#include "Vx/Lifecycle.h"
#include <stdbool.h>

#ifdef _WIN32
  #define NOMINMAX
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
#else
  #error "Vx only supports Win32 as of now..."
#endif

WNDCLASS Vx__WindowClass;

bool Vx_Initiate(void) {
  Vx__WindowClass.lpszClassName = "VxWindow";
  Vx__WindowClass.lpfnWndProc = DefWindowProc;
  Vx__WindowClass.hInstance = GetModuleHandle(NULL);

  if (!RegisterClass(&Vx__WindowClass)) return false;
  return true;
}

void Vx_Terminate(void) {
  return;
}

void *Vx_GetWindowClass(void) {
  return &Vx__WindowClass;
}
