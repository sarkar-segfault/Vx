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
  @brief Updates the specified window.
*/
Vx__Expose void VxWindow_Update(const VxWindow *window);

/**
  @since 0.1.0
  @brief Checks whether the window is still open.
  @returns Whether the specified window is still valid.
*/
Vx__Expose bool VxWindow_IsOpen(const VxWindow *window);

#endif
