#include "Vx/Lifecycle.h"  // IWYU pragma: associated

#include <stdbool.h>

#include "Internal.h"
#include "Vx/Event.h"
#include "Vx/Window.h"

LRESULT CALLBACK VxWindow__Process(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
  VxEventRing *ring = (VxEventRing *)GetWindowLongPtr(hwnd, GWLP_USERDATA);

  switch (umsg) {
    case WM_DESTROY:
      free(ring);
      SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)NULL);
      PostQuitMessage(0);
      return 0;

    case WM_TIMER:
      InvalidateRect(hwnd, NULL, TRUE);
      UpdateWindow(hwnd);
      return 0;

    case WM_CLOSE:
      return !VxEventRing_Put(ring, (VxEvent){.type = VxEventType_Close});

    case WM_SETFOCUS:
      VxEventRing_Put(ring, (VxEvent){.type = VxEventType_Focus});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_KILLFOCUS:
      VxEventRing_Put(ring, (VxEvent){.type = VxEventType_Blur});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_SHOWWINDOW:
      if (wparam)
        VxEventRing_Put(ring, (VxEvent){.type = VxEventType_Show});
      else
        VxEventRing_Put(ring, (VxEvent){.type = VxEventType_Hide});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_SIZE:
      if (wparam == SIZE_RESTORED)
        VxEventRing_Put(ring, (VxEvent){.type = VxEventType_Resize, .info.size = {LOWORD(lparam), HIWORD(lparam)}});
      else if (wparam == SIZE_MAXIMIZED)
        VxEventRing_Put(ring, (VxEvent){.type = VxEventType_Maximize});
      else if (wparam == SIZE_MINIMIZED)
        VxEventRing_Put(ring, (VxEvent){.type = VxEventType_Minimize});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_MOVE:
      VxEventRing_Put(ring, (VxEvent){.type = VxEventType_Move, .info.pos = {LOWORD(lparam), HIWORD(lparam)}});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_KEYDOWN:
      VxEventRing_Put(ring, (VxEvent){.type = VxEventType_KeyPress, .info.press.key = VxEventKey_Unknown});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_KEYUP:
      VxEventRing_Put(ring, (VxEvent){.type = VxEventType_KeyRelease, .info.press.key = VxEventKey_Unknown});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_CHAR:
      VxEventRing_Put(ring, (VxEvent){.type = VxEventType_CharSent, .info.sent = wparam});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_LBUTTONDOWN:
      VxEventRing_Put(ring, (VxEvent){.type = VxEventType_MousePress, .info.button = VxEventButton_MouseLeft});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_LBUTTONUP:
      VxEventRing_Put(ring, (VxEvent){.type = VxEventType_MouseRelease, .info.button = VxEventButton_MouseLeft});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_RBUTTONDOWN:
      VxEventRing_Put(ring, (VxEvent){.type = VxEventType_MousePress, .info.button = VxEventButton_MouseRight});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_RBUTTONUP:
      VxEventRing_Put(ring, (VxEvent){.type = VxEventType_MouseRelease, .info.button = VxEventButton_MouseRight});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_MBUTTONDOWN:
      VxEventRing_Put(ring, (VxEvent){.type = VxEventType_MousePress, .info.button = VxEventButton_MouseCenter});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_MBUTTONUP:
      VxEventRing_Put(ring, (VxEvent){.type = VxEventType_MouseRelease, .info.button = VxEventButton_MouseCenter});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_MOUSEMOVE:
      VxEventRing_Put(ring, (VxEvent){.type = VxEventType_MouseMove, .info.pos = {LOWORD(lparam), HIWORD(lparam)}});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_MOUSEWHEEL:
      VxEventRing_Put(ring, (VxEvent){.type = VxEventType_MouseWheel, .info.delta = HIWORD(wparam)});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

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
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW + 1;

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
