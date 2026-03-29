/**
  @file Window.h
  @since 0.1.0
  @license MIT
  @author Adhrit Sarkar <adhritsarkar@proton.me>
  @brief Defines the `VxWindow` struct and its operations.
*/

#ifndef Vx__WindowH
#define Vx__WindowH

#include "_Expose.h"
#include <stdbool.h>

typedef struct VxWindow VxWindow;

Vx__Expose void VxWindow_Create(VxWindow *window);
Vx__Expose void VxWindow_Delete(VxWindow *window);

#endif
