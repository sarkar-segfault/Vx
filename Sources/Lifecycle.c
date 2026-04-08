#include "Vx/Lifecycle.h" // IWYU pragma: associated
#include <Windows.h>
#include <stdbool.h>
#include "Internal.h"
#include "Vx/Window.h"

#define Vx__PostSent(hwnd, smsg, pmsg, wparam, lparam) case smsg: \
  PostMessage(hwnd, pmsg, wparam, lparam); \
  return DefWindowProc(hwnd, smsg, wparam, lparam);

LRESULT CALLBACK VxWindow__Process(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
  switch (umsg) {
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;

    case WM_TIMER:
      InvalidateRect(hwnd, NULL, TRUE);
      UpdateWindow(hwnd);
      return 0;

    Vx__PostSent(hwnd, WM_MOVE, WM_MOVEP, wparam, lparam);
    Vx__PostSent(hwnd, WM_SIZE, WM_SIZEP, wparam, lparam);
    Vx__PostSent(hwnd, WM_SETFOCUS, WM_SETFOCUSP, wparam, lparam);
    Vx__PostSent(hwnd, WM_KILLFOCUSP, WM_KILLFOCUSP, wparam, lparam);

    case WM_CLOSE:
      PostMessage(hwnd, WM_CLOSEP, wparam, lparam);
      return 0;

    case WM_CLOSEP:
      return DefWindowProc(hwnd, WM_CLOSE, wparam, lparam);
    
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

  if (!RegisterClassEx(&wc)) {
    Vx__Error("failed to register window class");
    return false;
  }

  return true;
}

bool Vx_Terminate(void) {
  if (!UnregisterClass(VxWindow_Class, GetModuleHandle(NULL))) {
    Vx__Error("failed to unregister window class");
    return false;
  }

  return true;
}
