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

/**
  @since 0.1.0
  @brief Represents a platform-specific window.
*/
typedef struct VxWindow VxWindow;

/**
  @since 0.1.0
  @brief Creates a native platform window.
  @returns Whether creation was successful.
*/
Vx__Expose bool VxWindow_Create(VxWindow **window);

/**
  @since 0.1.0
  @brief Deletes the specified window.
  @returns Whether deletion was successful.
*/
Vx__Expose bool VxWindow_Delete(VxWindow *window);

/**
  @since 0.1.0
  @brief Whether the specified window is still valid.
*/
Vx__Expose bool VxWindow_IsOpen(VxWindow *window);

#endif
