/*
  `Context.h` - functions for managing the lifecycle of the library.

  This header defines functions for managing the lifecycle of the library via
  the `VxContext` wrapper.
*/

#ifndef Vx__ContextH
#define Vx__ContextH

#include <stdbool.h>

#include "_Expose.h"

/*
  `VxContext` - wrapper for storing information required for windowing to work.

  This struct is a wrapper for storing extra information we need to make windowing
  and graphics work. Internally, this stores a `EGLDisplay` and a `EGLConfig`.
*/
typedef struct VxContext *VxContext;

/*
  `VxContext_Initiate` - initiate windowing and graphics.

  This function uses platform APIs to allocate the required resources for windowing
  and graphics. It creates a EGL display and a config, writing it into the context.
*/
Vx__Expose bool VxContext_Initiate(VxContext *context);

/*
  `VxContext_ClearGraphics` - clear the graphics context.

  This function clears the current graphics context. If you are manually dealing with
  OpenGL, you should to call this before commencing teardown.
*/
Vx__Expose bool VxContext_ClearGraphics(VxContext context);

/*
  `VxContext_Terminate` - terminate windowing and graphics.

  This function uses platform APIs to deallocate the resources we `VxContext_Initiate`
  allocated for windowing and graphics. It frees all EGL and windowing contexts.
*/
Vx__Expose bool VxContext_Terminate(VxContext context);

#endif
