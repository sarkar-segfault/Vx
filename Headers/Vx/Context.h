/**
  Functions for managing the lifecycle of the library.

  This header defines functions for managing the lifecycle of the library via
  the `VxContext` wrapper.
**/

#ifndef Vx__ContextH
#define Vx__ContextH

#include <stdbool.h>

#include "Vx/Status.h"
#include "_Expose.h"

/**
  ## Struct `VxContext`
  Wrapper for storing information required for windowing to work.

  This struct is a wrapper for storing extra information we need to make windowing
  and graphics work. Internally, this stores a `EGLDisplay` and a `EGLConfig`.
**/
typedef struct VxContext VxContext;

/**
  ## Method `VxContext_Create`
  Initiate windowing and graphics.

  This function uses platform APIs to allocate the required resources for windowing
  and graphics. It creates a EGL display and a config, writing it into the context.
**/
Vx__Expose VxStatus VxContext_Create(VxContext **context);

/**
  ## Method `VxContext_ClearGraphics`
  Clear the graphics context.

  This function clears the current graphics context. Use this to remove the window
  whose graphics context is current right now. This is usually called before cleanup.
**/
Vx__Expose VxStatus VxContext_ClearGraphics(VxContext *context);

/**
  ## Method `VxContext_GetDisplay`
  Return the display of the context.

  This function returns the `EGLDisplay` of the provided context.
**/
Vx__Expose VxStatus VxContext_GetDisplay(VxContext *context, void **display);

/**
  ## Method `VxContext_Delete`
  Terminate windowing and graphics.

  This function uses platform APIs to deallocate the resources `VxContext_Create`
  allocated for windowing and graphics. It frees all EGL and windowing contexts.
**/
Vx__Expose VxStatus VxContext_Delete(VxContext **context);

#endif
