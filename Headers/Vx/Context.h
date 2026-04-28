/**
  This header declares `VxContext` and its methods.

  This file defines `VxContext` and its methods, which manage allocation
  and deallocation of platform-specific global windowing resources.
**/

#ifndef Vx__ContextH
#define Vx__ContextH

#include "Status.h"
#include "_Expose.h"

typedef void *VxContext;

/**
  ## Function `VxContext_Create`

  This function initiates the native windowing context. This must be called
  before all other library functions.
**/
Vx__Expose VxStatus VxContext_Create(VxContext *context);

/**
  ## Function `VxContext_Delete`

  This function terminates the native windowing context. This must be called
  after all other library functions.
**/
Vx__Expose VxStatus VxContext_Delete(VxContext *context);

#endif
