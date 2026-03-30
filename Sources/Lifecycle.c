#include "Vx/Lifecycle.h" // IWYU pragma: associated
#include <stdbool.h>

#ifdef _WIN32
  #define NOMINMAX
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
#else
  #error "Vx only supports Win32 as of now..."
#endif

bool Vx_Initiate(void) {
  WNDCLASSEX wc = {0};
  wc.lpszClassName = Vx__WindowClass;
  wc.lpfnWndProc = DefWindowProc;
  wc.hInstance = GetModuleHandle(NULL);
  wc.cbSize = sizeof(WNDCLASSEX);

  if (!RegisterClassEx(&wc)) return false;
  return true;
}

void Vx_Terminate(void) {
  UnregisterClass(Vx__WindowClass, GetModuleHandle(NULL));
}
