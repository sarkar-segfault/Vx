#include <stdint.h>
#include <windows.h>

#include "Internal.h"
#include "Vx/Event.h"

VxEventKey Vx__TranslateKey(WPARAM key);

LRESULT CALLBACK VxWindow__Process(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
  VxWindowData *data = (VxWindowData *)GetWindowLongPtr(hwnd, GWLP_USERDATA);

  switch (umsg) {
    case WM_NCCREATE: {
      data = calloc(1, sizeof(struct VxWindowData));
      if (!data) return FALSE;

      CREATESTRUCT *cs = (CREATESTRUCT *)lparam;
      data->flags = (VxFlags)(intptr_t)cs->lpCreateParams;

      SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)data);
      return TRUE;
    }

    case WM_NCDESTROY:
      free(data);
      SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)NULL);
      return 0;

    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;

    case WM_CLOSE:
      return VxEventRing_Put(&data->ring, (VxEvent){.type = VxEventType_Close});

    case WM_SETFOCUS:
      VxEventRing_Put(&data->ring, (VxEvent){.type = VxEventType_Focus});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_KILLFOCUS:
      VxEventRing_Put(&data->ring, (VxEvent){.type = VxEventType_Blur});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_SHOWWINDOW:
      if (wparam) {
        data->flags &= ~VxFlag_Invisible;
        VxEventRing_Put(&data->ring, (VxEvent){.type = VxEventType_Show});
      } else {
        data->flags |= VxFlag_Invisible;
        VxEventRing_Put(&data->ring, (VxEvent){.type = VxEventType_Hide});
      }

      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_ENTERSIZEMOVE: {
      data->is_changing = true;
      RECT rect;
      GetWindowRect(hwnd, &rect);
      data->x = rect.left;
      data->y = rect.top;
      data->w = rect.right - rect.left;
      data->h = rect.bottom - rect.top;
      return 0;
    }

    case WM_EXITSIZEMOVE: {
      data->is_changing = false;
      RECT rect;
      GetWindowRect(hwnd, &rect);

      int32_t x = rect.left, y = rect.top;
      uint32_t w = rect.right - rect.left, h = rect.bottom - rect.top;

      if (data->x != x || data->y != y) {
        VxEventRing_Put(&data->ring, (VxEvent){.type = VxEventType_Move, .info.pos = {x, y}});
      }
      if (data->w != w || data->h != h) {
        VxEventRing_Put(&data->ring,
                        (VxEvent){.type = VxEventType_Resize, .info.size = {w, h}});
      }

      return 0;
    }

    case WM_SIZE:
      if (!data->is_changing) {
        data->flags &= ~(VxFlag_Minimized | VxFlag_Maximized);
        if (wparam == SIZE_RESTORED) {
          VxEventRing_Put(&data->ring,
                          (VxEvent){.type = VxEventType_Resize,
                                    .info.size = {LOWORD(lparam), HIWORD(lparam)}});
        } else if (wparam == SIZE_MAXIMIZED) {
          data->flags |= VxFlag_Maximized;
          VxEventRing_Put(&data->ring, (VxEvent){.type = VxEventType_Maximize});
        } else if (wparam == SIZE_MINIMIZED) {
          data->flags |= VxFlag_Minimized;
          VxEventRing_Put(&data->ring, (VxEvent){.type = VxEventType_Minimize});
        }
      }

      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_MOVE:
      if (!data->is_changing)
        VxEventRing_Put(&data->ring, (VxEvent){.type = VxEventType_Move,
                                               .info.pos = {LOWORD(lparam), HIWORD(lparam)}});

      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_KEYDOWN: {
      VxEvent ev =
          (VxEvent){.type = VxEventType_KeyPress, .info.press.key = Vx__TranslateKey(wparam)};

      if (GetKeyState(VK_CONTROL) & 0x8000) ev.info.press.mod |= VxEventMod_Control;
      if (GetKeyState(VK_SHIFT) & 0x8000) ev.info.press.mod |= VxEventMod_Shift;
      if (GetKeyState(VK_MENU) & 0x8000) ev.info.press.mod |= VxEventMod_Alt;

#ifndef VxEvent_SendUnknown
      if (ev.info.press.key != VxEventKey_Unknown)
#endif
        VxEventRing_Put(&data->ring, ev);

      return DefWindowProc(hwnd, umsg, wparam, lparam);
    }

    case WM_KEYUP: {
      VxEventKey key = Vx__TranslateKey(wparam);

#ifndef VxEvent_SendUnknown
      if (ev.info.press.key != VxEventKey_Unknown)
#endif
        VxEventRing_Put(&data->ring,
                        (VxEvent){.type = VxEventType_KeyRelease, .info.release = key});

      return DefWindowProc(hwnd, umsg, wparam, lparam);
    }

    case WM_CHAR:
      VxEventRing_Put(&data->ring,
                      (VxEvent){.type = VxEventType_CharSent, .info.sent = wparam});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_LBUTTONDOWN:
      VxEventRing_Put(&data->ring, (VxEvent){.type = VxEventType_MousePress,
                                             .info.button = VxEventButton_MouseLeft});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_LBUTTONUP:
      VxEventRing_Put(&data->ring, (VxEvent){.type = VxEventType_MouseRelease,
                                             .info.button = VxEventButton_MouseLeft});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_RBUTTONDOWN:
      VxEventRing_Put(&data->ring, (VxEvent){.type = VxEventType_MousePress,
                                             .info.button = VxEventButton_MouseRight});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_RBUTTONUP:
      VxEventRing_Put(&data->ring, (VxEvent){.type = VxEventType_MouseRelease,
                                             .info.button = VxEventButton_MouseRight});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_MBUTTONDOWN:
      VxEventRing_Put(&data->ring, (VxEvent){.type = VxEventType_MousePress,
                                             .info.button = VxEventButton_MouseCenter});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_MBUTTONUP:
      VxEventRing_Put(&data->ring, (VxEvent){.type = VxEventType_MouseRelease,
                                             .info.button = VxEventButton_MouseCenter});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_MOUSEMOVE:
      VxEventRing_Put(&data->ring, (VxEvent){.type = VxEventType_MouseMove,
                                             .info.pos = {LOWORD(lparam), HIWORD(lparam)}});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    case WM_MOUSEWHEEL:
      VxEventRing_Put(&data->ring,
                      (VxEvent){.type = VxEventType_MouseWheel, .info.delta = HIWORD(wparam)});
      return DefWindowProc(hwnd, umsg, wparam, lparam);

    default:
      return DefWindowProc(hwnd, umsg, wparam, lparam);
  }
}

VxEventKey Vx__TranslateKey(WPARAM key) {
  switch (key) {
    case 'A':
      return VxEventKey_A;
    case 'B':
      return VxEventKey_B;
    case 'C':
      return VxEventKey_C;
    case 'D':
      return VxEventKey_D;
    case 'E':
      return VxEventKey_E;
    case 'F':
      return VxEventKey_F;
    case 'G':
      return VxEventKey_G;
    case 'H':
      return VxEventKey_H;
    case 'I':
      return VxEventKey_I;
    case 'J':
      return VxEventKey_J;
    case 'K':
      return VxEventKey_K;
    case 'L':
      return VxEventKey_L;
    case 'M':
      return VxEventKey_M;
    case 'N':
      return VxEventKey_N;
    case 'O':
      return VxEventKey_O;
    case 'P':
      return VxEventKey_P;
    case 'Q':
      return VxEventKey_Q;
    case 'R':
      return VxEventKey_R;
    case 'S':
      return VxEventKey_S;
    case 'T':
      return VxEventKey_T;
    case 'U':
      return VxEventKey_U;
    case 'V':
      return VxEventKey_V;
    case 'W':
      return VxEventKey_W;
    case 'X':
      return VxEventKey_X;
    case 'Y':
      return VxEventKey_Y;
    case 'Z':
      return VxEventKey_Z;

    case '0':
      return VxEventKey_0;
    case '1':
      return VxEventKey_1;
    case '2':
      return VxEventKey_2;
    case '3':
      return VxEventKey_3;
    case '4':
      return VxEventKey_4;
    case '5':
      return VxEventKey_5;
    case '6':
      return VxEventKey_6;
    case '7':
      return VxEventKey_7;
    case '8':
      return VxEventKey_8;
    case '9':
      return VxEventKey_9;

    case VK_ESCAPE:
      return VxEventKey_Escape;
    case VK_TAB:
      return VxEventKey_Tab;
    case VK_CAPITAL:
      return VxEventKey_CapsLock;
    case VK_SPACE:
      return VxEventKey_Space;
    case VK_RETURN:
      return VxEventKey_Enter;
    case VK_BACK:
      return VxEventKey_Backspace;

    case VK_INSERT:
      return VxEventKey_Insert;
    case VK_DELETE:
      return VxEventKey_Delete;
    case VK_HOME:
      return VxEventKey_Home;
    case VK_END:
      return VxEventKey_End;
    case VK_PRIOR:
      return VxEventKey_PageUp;
    case VK_NEXT:
      return VxEventKey_PageDown;
    case VK_LEFT:
      return VxEventKey_Left;
    case VK_RIGHT:
      return VxEventKey_Right;
    case VK_UP:
      return VxEventKey_Up;
    case VK_DOWN:
      return VxEventKey_Down;

    case VK_F1:
      return VxEventKey_F1;
    case VK_F2:
      return VxEventKey_F2;
    case VK_F3:
      return VxEventKey_F3;
    case VK_F4:
      return VxEventKey_F4;
    case VK_F5:
      return VxEventKey_F5;
    case VK_F6:
      return VxEventKey_F6;
    case VK_F7:
      return VxEventKey_F7;
    case VK_F8:
      return VxEventKey_F8;
    case VK_F9:
      return VxEventKey_F9;
    case VK_F10:
      return VxEventKey_F10;
    case VK_F11:
      return VxEventKey_F11;
    case VK_F12:
      return VxEventKey_F12;

    case VK_NUMLOCK:
      return VxEventKey_NumLock;
    case VK_NUMPAD0:
      return VxEventKey_Numpad0;
    case VK_NUMPAD1:
      return VxEventKey_Numpad1;
    case VK_NUMPAD2:
      return VxEventKey_Numpad2;
    case VK_NUMPAD3:
      return VxEventKey_Numpad3;
    case VK_NUMPAD4:
      return VxEventKey_Numpad4;
    case VK_NUMPAD5:
      return VxEventKey_Numpad5;
    case VK_NUMPAD6:
      return VxEventKey_Numpad6;
    case VK_NUMPAD7:
      return VxEventKey_Numpad7;
    case VK_NUMPAD8:
      return VxEventKey_Numpad8;
    case VK_NUMPAD9:
      return VxEventKey_Numpad9;
    case VK_MULTIPLY:
      return VxEventKey_NumpadMultiply;
    case VK_ADD:
      return VxEventKey_NumpadAdd;
    case VK_SUBTRACT:
      return VxEventKey_NumpadSubtract;
    case VK_DECIMAL:
      return VxEventKey_NumpadDecimal;
    case VK_DIVIDE:
      return VxEventKey_NumpadDivide;

    case VK_OEM_1:
      return VxEventKey_Semicolon;
    case VK_OEM_PLUS:
      return VxEventKey_Equals;
    case VK_OEM_COMMA:
      return VxEventKey_Comma;
    case VK_OEM_MINUS:
      return VxEventKey_Minus;
    case VK_OEM_PERIOD:
      return VxEventKey_Period;
    case VK_OEM_2:
      return VxEventKey_Slash;
    case VK_OEM_3:
      return VxEventKey_Backtick;
    case VK_OEM_4:
      return VxEventKey_LeftBracket;
    case VK_OEM_5:
      return VxEventKey_Backslash;
    case VK_OEM_6:
      return VxEventKey_RightBracket;
    case VK_OEM_7:
      return VxEventKey_Quote;

    default:
      return VxEventKey_Unknown;
  }
}
