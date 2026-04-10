/*
  `Window.h` - defines structs and methods for window creation and control.

  This file defines the `VxWindow` struct and its many, many methods. Before
  you try to use any of these functions, please consult `Lifecycle.h` and its
  functions as they need to be called before and after any windowing logic.

  Most things defined in this file only work under `_WIN32`. Unsupported
  platforms will not be mentioned. Also, all functions here are thread safe.
*/

#ifndef Vx__WindowH
#define Vx__WindowH

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "Event.h"
#include "_Expose.h"

/*
  `VxWindow_Class` - the name of the window class (on `_WIN32`).

  This macro contains the `char[]` that names the window class on `_WIN32`. The
  default window class name is "VxWindow". Do not override this unless you have to.
*/
#if defined(_WIN32) && !defined(VxWindow_Class)
#define VxWindow_Class "VxWindow"
#endif

/*
  `VxWindow_DefaultWidth` - the default width of all windows.

  This macro contains the `int32_t` which is the default width of all windows when
  they are created. If this macro is not set, it defaults to 800. You can set
  this to avoid calling `VxWindow_SetSize` after creation, but since this only
  takes effect if defined at compile time, you may have to rebuild over and over.
*/
#ifndef VxWindow_DefaultWidth
#define VxWindow_DefaultWidth 800
#endif

/*
  `VxWindow_DefaultHeight` - the default height of all windows.

  This macro contains the `int32_t` which is the default height of all windows when
  they are created. If this macro is not set, it defaults to 600. You can set
  this to avoid calling `VxWindow_SetSize` after creation, but since this only
  takes effect if defined at compile time, you may have to rebuild over and over.
*/
#ifndef VxWindow_DefaultHeight
#define VxWindow_DefaultHeight 600
#endif

/*
  `VxWindow_DefaultTitle` - the default title of all windows.

  This macro contains the `char *` which is the default title of all windows when
  they are created. If this macro is not set, it defaults to "VxWindow". You can set
  this to avoid calling `VxWindow_SetTitle` after creation, but since this only takes
  effect if defined at compile time, you may have to rebuild over and over again.
*/
#ifndef VxWindow_DefaultTitle
#define VxWindow_DefaultTitle "VxWindow"
#endif

/*
  `VxWindow` - represents a platform specific window with an opaque pointer.

  This struct represents a underlying native window via an opaque pointer. The exact
  inner fields differ based on the environment, but a rough overview is given below.
  You can use `VxWindow_GetHandle` to get access to the inner platform context.
*/
typedef struct VxWindow VxWindow;

/*
  `VxWindow_Create` - create a `VxWindow` object.

  This function allocates the passed `VxWindow **`. Make sure that it is not already
  allocated, because this function will overwrite it and then inevitably leak memory.
  Internally, we call platform specific functions to create the window, write to the
  output parameter, and perform some extra work like setting opacity.
*/
Vx__Expose bool VxWindow_Create(VxWindow **window);

/*
  `VxWindow_Close` - close a `VxWindow` object.

  This function sets a flag which causes `VxWindow_IsOpen` to return false. Call this
  if you get `VxEventType_Close` and `VxWindow_Delete` later.
*/
Vx__Expose bool VxWindow_Close(VxWindow *window);

/*
  `VxWindow_Close` - open a `VxWindow` object.

  This function sets a flag which influences `VxWindow_IsOpen` to return true. Call this
  if you want to revive a window affected by `VxWindow_Close`.
*/
Vx__Expose bool VxWindow_Close(VxWindow *window);

/*
  `VxWindow_Delete` - delete a `VxWindow` object.

  This function deallocates the passed `VxWindow **` and sets it to `NULL`. If the inner
  platform context is valid, then a platform specific destructor is also called to destroy
  the window; though this is usually not needed unless called while the window is alive.
*/
Vx__Expose bool VxWindow_Delete(VxWindow **window);

/*
  `VxWindow_PollEvents` - poll input events from the window.

  This function processes all platform-specific messages/input and pushes them onto the
  window's internal event ring, which is a circular queue. This function does not block at
  all, and may be insufficient for certain applications.
*/
Vx__Expose bool VxWindow_PollEvents(VxWindow *window);

/*
  `VxWindow_PopEvent` - pop an event from the window's event ring.

  This function pops the oldest relevant event from the window's event ring into the provided
  output parameter. In a loop, you can use this to sequentially process all window events.
*/
Vx__Expose bool VxWindow_PopEvent(VxWindow *window, VxEvent *event);

/*
  `VxWindow_PutEvent` - put an event onto the window's event ring.

  This function puts the provided event onto the window event ring's last available spot,
  removing the oldest event if it has to. You can use this to simulate events or interactions.
*/
Vx__Expose bool VxWindow_PutEvent(VxWindow *window, VxEvent event);

/*
  `VxWindow_IsOpen` - check whether the window is still open.

  This function checks whether the window is still open. In a loop, you can use this to check
  the validity of the window.
*/
Vx__Expose bool VxWindow_IsOpen(const VxWindow *window);

/*
  `VxWindow_GetFps` - get the current FPS of the window.

  This function writes the current FPS of the window into an output parameter.
  If the FPS is unset or reset, it returns 0. Returns `false` on failure.
*/
Vx__Expose bool VxWindow_GetFps(const VxWindow *window, uint8_t *fps);

/*
  `VxWindow_SetFps` - set the current FPS of the window.

  This function sets the FPS of the window to the specified value. If 0, it removes the timer.
  Returns `false` on failure.
*/
Vx__Expose bool VxWindow_SetFps(VxWindow *window, const uint8_t fps);

/*
  `VxWindow_GetSize` - get the current size of the window.

  Writes the width and height of the window in pixels to the output parameters `w`
  and `h`. Returns `false` on failure.
*/
Vx__Expose bool VxWindow_GetSize(const VxWindow *window, uint32_t *w, uint32_t *h);

/*
  `VxWindow_SetSize` - set the window's size.

  Changes the width and height of the window in pixels. Returns `false` on failure.
*/
Vx__Expose bool VxWindow_SetSize(const VxWindow *window, const uint32_t w, const uint32_t h);

/*
  `VxWindow_GetPos` - get the current position of the window.

  Writes the X and Y coordinates of the window's top-left corner relative to the
  screen into `x` and `y`. Returns `false` on failure.
*/
Vx__Expose bool VxWindow_GetPos(const VxWindow *window, int32_t *x, int32_t *y);

/*
  `VxWindow_SetPos` - set the window's position on the screen.

  Moves the window to the specified screen coordinates. Returns `false` on failure.
*/
Vx__Expose bool VxWindow_SetPos(const VxWindow *window, const int32_t x, const int32_t y);

/*
  `VxWindow_GetTitle` - retrieve the window's title.

  Copies the current window title into `buf`, up to `len` characters. Returns `false` on failure [1].

  [1] - On `_WIN32`, we use `GetWindowText` to get the title. `GetWindowText`, however, returns 0 both
        when it fails and also if the window's title length is literally 0. Since, to my knowledge, we
        cannot distinguish among these two outcomes, this returns `true` regardless of `GetWindowText`.
*/
Vx__Expose bool VxWindow_GetTitle(const VxWindow *window, char *buf, const size_t len);

/*
  `VxWindow_SetTitle` - set the window's title.

  Changes the text displayed in the title bar of the window. Returns `false` on failure.
*/
Vx__Expose bool VxWindow_SetTitle(const VxWindow *window, const char *const title);

/*
  `VxWindow_GetOpacity` - retrieve the window's opacity.

  Writes the current opacity between 0.0 and 1.0 to `o`. Returns `false` on failure.
*/
Vx__Expose bool VxWindow_GetOpacity(const VxWindow *window, float *o);

/*
  `VxWindow_SetOpacity` - set the window's opacity.

  Sets the window's transparency. `o` should range between 0.0 and 1.0; returns `false`
  on failure.
*/
Vx__Expose bool VxWindow_SetOpacity(const VxWindow *window, const float o);

/*
  `VxWindow_Minimize` - minimize the window.

  Sends the window to the taskbar or dock, iconifying it. Returns `false` on failure.
*/
Vx__Expose bool VxWindow_Minimize(const VxWindow *window);

/*
  `VxWindow_Restore` - restore a minimized or maximized window.

  Brings the window back to its normal size and position. Returns `true` on success.
*/
Vx__Expose bool VxWindow_Restore(const VxWindow *window);

/*
  `VxWindow_Maximize` - maximize the window.

  Enlarges the window to fill the screen or desktop area, maintaining borders if
  supported. Returns `true` on success.
*/
Vx__Expose bool VxWindow_Maximize(const VxWindow *window);

/*
  `VxWindow_Show` - show the window.

  Makes the window visible if it is hidden. Returns `true` on success.
*/
Vx__Expose bool VxWindow_Show(const VxWindow *window);

/*
  `VxWindow_Hide` - hide the window.

  Makes the window invisible without destroying it. Returns `true` on success.
*/
Vx__Expose bool VxWindow_Hide(const VxWindow *window);

/*
  `VxWindow_Focus` - give keyboard focus to the window.

  Makes this window the active window and directs keyboard input to it. Returns
  `true` if the operation succeeds.
*/
Vx__Expose bool VxWindow_Focus(const VxWindow *window);

/*
  `VxWindow_Flash` - flash the window to draw user attention.

  Causes the window to visually flash, typically in the taskbar, to notify the
  user. Returns `true` if successful.
*/
Vx__Expose bool VxWindow_Flash(const VxWindow *window);

/*
  `VxWindow_GetHandle` - retrieve the underlying platform handle.

  Writes the platform-specific window object (e.g., `HWND` on `_WIN32`) into `ptr`.
  Returns `true` if successful. This can be used for low-level platform operations
  not exposed through the `VxWindow` API.
*/
Vx__Expose bool VxWindow_GetHandle(const VxWindow *window, void **ptr);

#endif
