#include "Vx/Lifecycle.h"
#include "Vx/Window.h"
#include <stddef.h>
#include <stdio.h>
#include <Windows.h>

int main(void) {
  Vx_Initiate();
  VxWindow *window = NULL;

  VxWindow_Create(&window);
  VxWindow_SetTargetFps(window, 60);

  while (VxWindow_IsOpen(window)) {
    VxWindow_Update(window);
  }

  // int w, h;
  // VxWindow_GetSize(window, &w, &h);
  // printf("w: %d, h: %d\n", w, h);

  // int x, y;
  // VxWindow_GetPos(window, &x, &y);
  // printf("x: %d, y: %d\n", x, y);

  // VxWindow_Delete(window);

  // DWORD err = GetLastError();
  // char *msg = NULL;

  // FormatMessage(
  //   FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
  //   NULL,
  //   err,
  //   0,
  //   (LPSTR)&msg,
  //   0,
  //   NULL
  // );

  // if (msg) {
  //   printf("Win32 API Error #%lu: %s", err, msg);
  //   LocalFree(msg);
  // } else {
  //   printf("Win32 API Error #%lu", err);
  // }

  Vx_Terminate();
  return 0;
}
