#include "Vx/Lifecycle.h"
#include "Vx/Window.h"
#include <stddef.h>

int main(void) {
  Vx_Initiate();
  
  VxWindow *window = NULL;
  if (!VxWindow_Create(&window)) return 1;

  while (VxWindow_IsOpen(window)) {
    VxWindow_Update(window);
  }

  if (!VxWindow_Delete(window)) return 1;

  Vx_Terminate();
  return 0;
}
