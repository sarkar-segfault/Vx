/**
  Defines structs and methods for window creation and control.

  This file defines the `VxWindow` struct and its many, many methods. Before
  you try to use any of these functions, please consult `Context.h` and its
  functions as they need to be called before and after any windowing logic.

  Most things defined in this file only work under `_WIN32`. Unsupported
  platforms will not be mentioned. Also, all functions here are thread safe.
**/

#ifndef Vx__WindowH
#define Vx__WindowH

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "Context.h"
#include "Event.h"
#include "Flag.h"
#include "Status.h"
#include "_Expose.h"

/**
  ## Struct `VxWindow`
  Represents a platform specific window with an opaque pointer.

  This struct represents a underlying native window via an opaque pointer. The exact
  inner fields differ based on the environment, but a rough overview is given below.
  You can use `VxWindow_GetHandle` to get access to the inner platform context.
**/
typedef struct VxWindow VxWindow;

/**
  ## Method `VxWindow_Create`
  Create a `VxWindow` object.

  This function allocates the passed `VxWindow **`. Make sure that it is not already
  allocated, because this function will overwrite it and then inevitably leak memory.
  Internally, we call platform specific functions to create the window, write to the
  output parameter, and create the window's graphics context and surface.
**/
Vx__Expose VxStatus VxWindow_Create(VxWindow **window, VxContext *context, VxFlags flags);

/**
  ## Method `VxWindow_GetFlag`
  Return whether the specified flag is currently set.

  This function returns whether the specified `VxFlag` is currently set on the window.
**/
Vx__Expose bool VxWindow_GetFlag(VxWindow *window, VxFlag flag);

/**
  ## Method `VxWindow_MountGraphics`
  Initialise the window's graphics context and make it current.

  This function enables graphics work on the selected window. No graphics work can run
  before this. Call this with `NULL` in order to reset or clear the context.
**/
Vx__Expose VxStatus VxWindow_MountGraphics(VxWindow *window);

/**
  ## Method `VxWindow_GetSurface`
  Return the `EGLSurface` of the window.

  This function writes the `EGLSurface` handle of the window to the provided `surface`.
**/
Vx__Expose VxStatus VxWindow_GetSurface(VxWindow *window, void **surface);

/**
  ## Method `VxWindow_Close`
  Close a `VxWindow` object.

  This function sets a flag which causes `VxWindow_IsOpen` to return false.
  Call this when handling `VxEventType_Close`, and destroy later with `VxWindow_Delete`.
**/
Vx__Expose VxStatus VxWindow_Close(VxWindow *window);

/**
  ## Method `VxWindow_Open`
  Re-open a `VxWindow` object.

  This function resets the internal open-state flag, causing `VxWindow_IsOpen`
  to return true again.
**/
Vx__Expose VxStatus VxWindow_Open(VxWindow *window);

/**
  ## Method `VxWindow_Delete`
  Delete a `VxWindow` object.

  This function deallocates the passed `VxWindow *` and sets it to `NULL`.
  If the inner platform context is valid, it is destroyed as well, including
  any associated graphics surfaces or contexts.
**/
Vx__Expose VxStatus VxWindow_Delete(VxWindow **window);

/**
  ## Method `VxWindow_PollEvents`
  Poll input events from the window.

  Processes all platform-specific messages and pushes them into the window's
  internal event ring buffer. This function does not block.
**/
Vx__Expose VxStatus VxWindow_PollEvents(VxWindow *window);

/**
  ## Method `VxWindow_PopEvent`
  Pop an event from the window's event ring.

  Removes the oldest event from the internal event queue and writes it to `event`.
**/
Vx__Expose VxStatus VxWindow_PopEvent(VxWindow *window, VxEvent *event);

/**
  ## Method `VxWindow_PutEvent`
  Put an event into the window's event ring.

  Inserts an event into the queue, overwriting the oldest if the buffer is full.
**/
Vx__Expose VxStatus VxWindow_PutEvent(VxWindow *window, VxEvent event);

/**
  ## Method `VxWindow_IsOpen`
  Check whether the window is still open.

  Returns true if the window is currently marked as open.
**/
Vx__Expose bool VxWindow_IsOpen(const VxWindow *window);

/**
  ## Method `VxWindow_GetSize`
  Get the current size of the window.

  Writes width and height in pixels to `w` and `h`.
**/
Vx__Expose VxStatus VxWindow_GetSize(const VxWindow *window, uint32_t *w, uint32_t *h);

/**
  ## Method `VxWindow_SetSize`
  Set the window's size.

  Changes the width and height of the window in pixels.
**/
Vx__Expose VxStatus VxWindow_SetSize(const VxWindow *window, const uint32_t w, const uint32_t h);

/**
  ## Method `VxWindow_GetPos`
  Get the current position of the window.

  Writes the X and Y coordinates of the top-left corner to `x` and `y`.
**/
Vx__Expose VxStatus VxWindow_GetPos(const VxWindow *window, int32_t *x, int32_t *y);

/**
  ## Method `VxWindow_SetPos`
  Set the window's position on the screen.

  Moves the window to the specified screen coordinates.
**/
Vx__Expose VxStatus VxWindow_SetPos(const VxWindow *window, const int32_t x, const int32_t y);

/**
  ## Method `VxWindow_GetTitle`
  Retrieve the window's title.

  Copies the title into `buf`, up to `len` characters.

  Note: On `_WIN32`, `GetWindowText` is used, which cannot distinguish between
  failure and an empty title, so this function always returns true in that case.
**/
Vx__Expose VxStatus VxWindow_GetTitle(const VxWindow *window, char *buf, const size_t len);

/**
  ## Method `VxWindow_SetTitle`
  Set the window's title.

  Changes the text displayed in the window's title bar.
**/
Vx__Expose VxStatus VxWindow_SetTitle(const VxWindow *window, const char *const title);

/**
  ## Method `VxWindow_GetOpacity`
  Retrieve the window's opacity.

  Writes the opacity value (0.0 to 1.0) to `o`.
**/
Vx__Expose VxStatus VxWindow_GetOpacity(const VxWindow *window, float *o);

/**
  ## Method `VxWindow_SetOpacity`
  Set the window's opacity.

  Sets transparency level between 0.0 and 1.0.
**/
Vx__Expose VxStatus VxWindow_SetOpacity(const VxWindow *window, const float o);

/**
  ## Method `VxWindow_Minimize`
  Minimize the window.

  Sends the window to the taskbar or dock.
**/
Vx__Expose VxStatus VxWindow_Minimize(const VxWindow *window);

/**
  ## Method `VxWindow_Restore`
  Restore a minimized or maximized window.

  Returns the window to normal state.
**/
Vx__Expose VxStatus VxWindow_Restore(const VxWindow *window);

/**
  ## Method `VxWindow_Maximize`
  Maximize the window.

  Expands the window to fill the screen or desktop area.
**/
Vx__Expose VxStatus VxWindow_Maximize(const VxWindow *window);

/**
  ## Method `VxWindow_Show`
  Show the window.

  Makes the window visible if it is hidden.
**/
Vx__Expose VxStatus VxWindow_Show(const VxWindow *window);

/**
  ## Method `VxWindow_Hide`
  Hide the window.

  Makes the window invisible without destroying it.
**/
Vx__Expose VxStatus VxWindow_Hide(const VxWindow *window);

/**
  ## Method `VxWindow_Focus`
  Give keyboard focus to the window.

  Makes this window the active input target.
**/
Vx__Expose VxStatus VxWindow_Focus(const VxWindow *window);

/**
  ## Method `VxWindow_Flash`
  Flash the window.

  Causes the window to visually flash to attract user attention.
**/
Vx__Expose VxStatus VxWindow_Flash(const VxWindow *window);

/**
  ## Method `VxWindow_GetHandle`
  Retrieve the underlying platform handle.

  Returns the native window handle (e.g., `HWND` on `_WIN32`).
**/
Vx__Expose VxStatus VxWindow_GetHandle(const VxWindow *window, void **handle);

#endif
