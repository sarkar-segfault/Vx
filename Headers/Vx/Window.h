/*
  `Window.h` - defines structs and methods for window creation and control.
  Introduced in version `0.1.0`.

  This file defines the `VxWindow` struct and its many, many methods. Before
  you try to use any of these functions, please consult `Lifecycle.h` and its
  functions as they need to be called before and after any windowing logic.

  Most things defined in this file only work under `_WIN32`. Unsupported
  platforms will not be mentioned.
*/

#ifndef Vx__WindowH
#define Vx__WindowH

#include "_Expose.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

/*
  `VxWindow_Class` - the name of the window class (on `_WIN32`).
  Introduced in version `0.1.0`.

  This macro contains the `char[]` that names the window class on `_WIN32`. The
  default window class name is "VxWindow". Do not override this unless you have to.
*/
#if defined(_WIN32) && !defined(VxWindow_Class)
  #define VxWindow_Class "VxWindow"
#endif

/*
  `VxWindow_DefaultWidth` - the default width of all windows.
  Introduced in version `0.1.0`.

  This macro contains the `int32_t` which is the default width of all windows when
  they are created. If this macro is not set, it defaults to 800. You can set
  this to avoid calling `VxWindow_SetSize` after creation, but please don't [1].

  [1]
    This macro must be set at compile time for it to work, so you will have to
    rebuild every time you get a mood swing. That approach can work, but is
    it really worth it?
*/
#ifndef VxWindow_DefaultWidth
  #define VxWindow_DefaultWidth 800
#endif

/*
  `VxWindow_DefaultHeight` - the default height of all windows.
  Introduced in version `0.1.0`.

  This macro contains the `int32_t` which is the default height of all windows when
  they are created. If this macro is not set, it defaults to 600. You can set
  this to avoid calling `VxWindow_SetSize` after creation, but please don't [1].

  [1]
    This macro must be set at compile time for it to take effect, so you will have
    to rebuild every time you get a mood swing. That approach can work, but is that
    really worth it?
*/
#ifndef VxWindow_DefaultHeight
  #define VxWindow_DefaultHeight 600
#endif

/*
  `VxWindow_DefaultTitle` - the default title of all windows.
  Introduced in version `0.1.0`.

  This macro contains the `char *` which is the default title of all windows when they are
  created. If this macro is not set, it defaults to "VxWindow". You can set this to avoid
  calling `VxWindow_SetTitle` after creation, but please don't [1].

  [1]
    This macro must be set at compile time for it to take effect, so you will have
    to rebuild every time you get a mood swing. That approach may work, but is that
    really worth it?
*/
#ifndef VxWindow_DefaultTitle
  #define VxWindow_DefaultTitle "VxWindow"
#endif

/*
  `VxWindow` - represents a platform specific window with an opaque pointer.
  Introduced in version `0.1.0`.

  This struct represents a underlying native window via an opaque pointer. The exact
  inner fields differ based on the environment, but a rough overview is given below.
  You can try to do some pointer acrobatics and access the inner fields, but don't.
  You can get access to the platform specific context using `VxWindow_GetHandle`.

  On `_WIN32`, we store `HWND` for the window handle and `UINT_PTR` for the timer ID.
*/
typedef struct VxWindow VxWindow;

Vx__Expose bool VxWindow_Create(VxWindow **window);

Vx__Expose bool VxWindow_Delete(VxWindow **window);

Vx__Expose bool VxWindow_Update(VxWindow *window);

Vx__Expose bool VxWindow_IsOpen(const VxWindow *window);

Vx__Expose bool VxWindow_GetFps(const VxWindow *window, uint8_t *fps);

Vx__Expose bool VxWindow_SetFps(VxWindow *window, const uint8_t fps);

Vx__Expose bool VxWindow_GetSize(const VxWindow *window, uint32_t *w, uint32_t *h);

Vx__Expose bool VxWindow_SetSize(const VxWindow *window, const uint32_t w, const uint32_t h);

Vx__Expose bool VxWindow_GetPos(const VxWindow *window, int32_t *x, int32_t *y);

Vx__Expose bool VxWindow_SetPos(const VxWindow *window, const int32_t x, const int32_t y);

Vx__Expose bool VxWindow_GetTitle(const VxWindow *window, char *buf, const size_t len);

Vx__Expose bool VxWindow_SetTitle(const VxWindow *window, const char *const title);

Vx__Expose bool VxWindow_GetOpacity(const VxWindow *window, float *o);

Vx__Expose bool VxWindow_SetOpacity(const VxWindow *window, const float o);

Vx__Expose bool VxWindow_Minimize(const VxWindow *window);

Vx__Expose bool VxWindow_Restore(const VxWindow *window);

Vx__Expose bool VxWindow_Maximize(const VxWindow *window);

Vx__Expose bool VxWindow_Show(const VxWindow *window);

Vx__Expose bool VxWindow_Hide(const VxWindow *window);

Vx__Expose bool VxWindow_Focus(const VxWindow *window);

Vx__Expose bool VxWindow_Flash(const VxWindow *window);

Vx__Expose bool VxWindow_GetHandle(const VxWindow *window, void **ptr);

#endif
