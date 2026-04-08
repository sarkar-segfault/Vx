#include "Vx/Event.h"
#include "Vx/Lifecycle.h"
#include "Vx/Window.h"
#include <Windows.h>
#include <stddef.h>
#include <stdio.h>

int main(void) {
  Vx_Initiate();
  VxWindow *window = NULL;

  VxWindow_Create(&window);
  VxWindow_SetFps(window, 60);

  VxEvent event;

  while (VxWindow_IsOpen(window)) {
    while (VxWindow_WaitEvent(window, &event)) {

      switch (event.type) {
      case VxEventType_Resize:
        printf("Resize - Width: %u, Height: %u\n", event.info.size.w,
               event.info.size.h);
        break;

      case VxEventType_Move:
        printf("Move - X: %d, Y: %d\n", event.info.pos.x,
               event.info.pos.y);
        break;

      case VxEventType_Focus:
        printf("Focus\n");
        break;

      case VxEventType_Blur:
        printf("Blur\n");
        break;

      case VxEventType_Minimize:
        printf("Minimize\n");
        break;

      case VxEventType_Maximize:
        printf("Maximize\n");
        break;

      case VxEventType_KeyPress:
        printf("KeyPress - Key: %d, Modifiers: 0x%02X\n",
               event.info.press.key, event.info.press.mod);
        break;

      case VxEventType_KeyRelease:
        printf("KeyRelease - Key: %d\n", event.info.release);
        break;

      case VxEventType_CharSent:
        printf("CharSent - '%c'\n", event.info.sent);
        break;

      case VxEventType_MouseMove:
        printf("MouseMove - X: %d, Y: %d\n", event.info.pos.x,
               event.info.pos.y);
        break;

      case VxEventType_MousePress:
        printf("MousePress - Button: %d\n", event.info.button);
        break;

      case VxEventType_MouseRelease:
        printf("MouseRelease - Button: %d\n", event.info.button);
        break;

      case VxEventType_MouseWheel:
        printf("MouseWheel - Delta: %d\n", event.info.wheel.delta);
        break;

      default:
        printf("Unknown type %d\n", event.type);
        break;
      }
    }
  }

  VxWindow_Delete(&window);
  Vx_Terminate();
  return 0;
}
