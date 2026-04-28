/**
  This header declares `VxHandle` and its methods.

  This file defines `VxHandle` and its methods, which manage allocation
  and deallocation of platform-specific global windowing resources.
**/

#ifndef Vx__HandleH
#define Vx__HandleH

#include "Status.h"
#include "_Expose.h"

/**
  ## Typedef `VxHandle`
  Void pointer to platform-specific windowing context.

  This pointer holds a reference to the native windowing context.
  Do not try to dereference it; we do not guarantee validity.
**/
typedef void *VxHandle;

/**
  ## Function `VxHandle_Create`

  This function initiates the native windowing context. This must be called
  before all other library functions.
**/
Vx__Expose VxStatus VxHandle_Create(VxHandle *handle);

/**
  ## Function `VxHandle_Delete`

  This function terminates the native windowing context. This must be called
  after all other library functions.
**/
Vx__Expose VxStatus VxHandle_Delete(VxHandle *handle);

#endif
