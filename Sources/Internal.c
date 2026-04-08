#include "Internal.h"
#include "Vx/Event.h"
#include <stdbool.h>
#include <Windows.h>

bool Vx__TranslateEvent(const MSG *msg, VxEvent *event) {
  if (!msg || !event) return false;
  *event = (VxEvent){0};

  if (msg->message == WM_CLOSE)
    event->type = VxEventType_Close;
  
  else if (msg->message == WM_SIZE) {  
    if (msg->wParam == SIZE_MAXIMIZED)
      event->type = VxEventType_Maximize;

    else if (msg->wParam == SIZE_MINIMIZED)
      event->type = VxEventType_Minimize;

    else {
      event->type = VxEventType_Resize;
      event->info.size.w = LOWORD(msg->lParam);
      event->info.size.h = HIWORD(msg->lParam);
    }
  }

  else if (msg->message == WM_MOVE) {
    event->type = VxEventType_Move;
    event->info.pos.x = LOWORD(msg->lParam);
    event->info.pos.y = HIWORD(msg->lParam);
  }

  else if (msg->message == WM_SETFOCUS)
    event->type = VxEventType_Focus;

  else if (msg->message == WM_KILLFOCUS)
    event->type = VxEventType_Blur;

  else if (msg->message == WM_CHAR) {
    event->type = VxEventType_CharSent;
    event->info.sent = msg->wParam;
  }

  else if (msg->message == WM_MOUSEMOVE) {
    event->type = VxEventType_MouseMove;
    event->info.pos.x = LOWORD(msg->lParam);
    event->info.pos.y = HIWORD(msg->lParam);
  }

  else if (msg->message == WM_MBUTTONDOWN) {
    event->type = VxEventType_MousePress;
    event->info.button = VxEventButton_MouseCenter;
  }

  else if (msg->message == WM_MBUTTONUP) {
    event->type = VxEventType_MouseRelease;
    event->info.button = VxEventButton_MouseCenter;
  }

  else if (msg->message == WM_LBUTTONDOWN) {
    event->type = VxEventType_MousePress;
    event->info.button = VxEventButton_MouseLeft;
  }

  else if (msg->message == WM_LBUTTONUP) {
    event->type = VxEventType_MouseRelease;
    event->info.button = VxEventButton_MouseLeft;
  }

  else if (msg->message == WM_RBUTTONDOWN) {
    event->type = VxEventType_MousePress;
    event->info.button = VxEventButton_MouseRight;
  }

  else if (msg->message == WM_RBUTTONUP) {
    event->type = VxEventType_MousePress;
    event->info.button = VxEventButton_MouseRight;
  }

  else if (msg->message == WM_KEYDOWN) {
    event->type = VxEventType_KeyPress;
    event->info.press.key = VxEventKey_Unknown;

    if (GetKeyState(VK_CONTROL) & 0x8000)
      event->info.press.mod |= VxEventMod_Control;
    else if (GetKeyState(VK_SHIFT) & 0x8000)
      event->info.press.mod |= VxEventMod_Shift;
    else if (GetKeyState(VK_MENU) & 0x8000)
      event->info.press.mod |= VxEventMod_Alt;
  }

  else if (msg->message == WM_KEYUP) {
    event->type = VxEventType_KeyRelease;
    event->info.release = VxEventKey_Unknown;
  }

  else if (msg->message == WM_MOUSEWHEEL) {
    event->type = VxEventType_MouseWheel;
    event->info.delta = HIWORD(msg->wParam);
  }

  else return false;

  return true;
}
