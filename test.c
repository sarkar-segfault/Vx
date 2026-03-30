#include "Vx/Lifecycle.h"
#include "Vx/Window.h"
#include <stddef.h>
// #include <stdio.h>

int main(void) {
  Vx_Initiate();
  
  VxWindow *window = NULL;
  VxWindow_Create(&window);

  while (VxWindow_IsOpen(window)) {
    VxWindow_Update(window);
  }

  // int w, h;
  // VxWindow_GetSize(window, &w, &h);
  // printf("w: %d, h: %d\n", w, h);

  // int x, y;
  // VxWindow_GetPos(window, &x, &y);
  // printf("x: %d, y: %d\n", x, y);

  VxWindow_Delete(window);

  Vx_Terminate();
  return 0;
}
