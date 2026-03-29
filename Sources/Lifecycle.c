/**
  @file Lifecycle.c
  @since 0.1.0
  @license MIT
  @author Adhrit Sarkar <adhritsarkar@proton.me>
  @brief Defines functionality for Lifecycle.h; as of now, only works on windows.
*/

#include "Vx/Lifecycle.h" // IWYU pragma: associated
#include <stdbool.h>

#ifdef _WIN32
  #define NOMINMAX
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
#else
  #error "Vx only supports Win32 as of now..."
#endif

WNDCLASSEX Vx__WindowClass;

bool Vx_Initiate(void) {
  Vx__WindowClass.lpszClassName = "VxWindow";
  Vx__WindowClass.lpfnWndProc = DefWindowProc;
  Vx__WindowClass.hInstance = GetModuleHandle(NULL);
  Vx__WindowClass.cbSize = sizeof(WNDCLASSEX);

  if (!RegisterClassEx(&Vx__WindowClass)) return false;
  return true;
}

void Vx_Terminate(void) {
  return;
}

void *Vx_GetWindowClass(void) {
  return &Vx__WindowClass;
}
