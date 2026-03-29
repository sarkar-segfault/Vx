#include "Vx/Lifecycle.h"
#include "Vx/Window.h"
#include <stddef.h>

int main(void) {
  VxWindow *window = NULL;
  if (!VxWindow_Create(&window)) return 1;

  while (VxWindow_IsOpen(window)) {
    ;;
  }

  if (!VxWindow_Delete(window)) return 1;
  return 0;
}
