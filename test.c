#include <stddef.h>
#include <stdio.h>

#include "Vx/Context.h"
#include "Vx/Window.h"
#include <GLES2/gl2.h>
#include <EGL/egl.h>

int main(void) {
  VxContext *context;
  if (!VxContext_Initiate(&context)) return 1;

  VxWindow window;

  if (!VxWindow_Create(&window, context)) return 1;

  if (!VxWindow_MountGraphics(window)) return 1;
  VxEvent event;

  while (VxWindow_IsOpen(window)) {
    if (!VxWindow_PollEvents(window)) return 1;
    glClearColor(100.0f/255.0f, 149.0f/255.0f, 237.0f/255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    while (VxWindow_PopEvent(window, &event)) {
      switch (event.type) {
        case VxEventType_Close:
          printf("Close\n");
          if (!VxWindow_Close(window)) return 1;
          goto terminate;

        case VxEventType_Resize:
          printf("Resize: %u x %u\n", event.info.size.w, event.info.size.h);
          break;

        case VxEventType_Move:
          printf("Move: %d, %d\n", event.info.pos.x, event.info.pos.y);
          break;

        case VxEventType_Focus:
          printf("Focus gained\n");
          break;

        case VxEventType_Blur:
          printf("Focus lost\n");
          break;

        case VxEventType_Show:
          printf("Window shown\n");
          break;

        case VxEventType_Hide:
          printf("Window hidden\n");
          break;

        case VxEventType_Minimize:
          printf("Minimized\n");
          break;

        case VxEventType_Maximize:
          printf("Maximized\n");
          break;

        case VxEventType_KeyPress:
          printf("Key press: %d (mod: %u)\n", event.info.press.key, event.info.press.mod);
          break;

        case VxEventType_KeyRelease:
          printf("Key release: %d\n", event.info.release);
          break;

        case VxEventType_CharSent:
          printf("Char: %c\n", event.info.sent);
          break;

        case VxEventType_MouseMove:
          printf("Mouse move: %d, %d\n", event.info.pos.x, event.info.pos.y);
          break;

        case VxEventType_MousePress:
          printf("Mouse press: %d\n", event.info.button);
          break;

        case VxEventType_MouseRelease:
          printf("Mouse release: %d\n", event.info.button);
          break;

        case VxEventType_MouseWheel:
          printf("Mouse wheel: %d\n", event.info.wheel.delta);
          break;

        case VxEventType_Empty:
          printf("Empty");
          break;

        default:
          printf("Unknown event\n");
          break;
      }
    }

    eglSwapBuffers(context->display, VxWindow_GetSurface(window));
  }

terminate:
  if (!VxWindow_Delete(&window)) return 1;
  if (!VxContext_Terminate(context)) return 1;
  return 0;
}
