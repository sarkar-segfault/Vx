#include "Vx/Lifecycle.h"
#include "Vx/Window.h"
#include <stddef.h>
// #include <stdio.h>
#include <Windows.h>

int main(void) {
  Vx_Initiate();
  VxWindow *window = NULL;

  VxWindow_Create(&window, 60);

  while (VxWindow_IsOpen(window)) {
    VxWindow_Update(window);
  }

  Vx_Terminate();
  return 0;
}
