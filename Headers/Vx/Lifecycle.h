/**
  This header declares functions for managing the lifecycle of the library.

  This file defines `Vx_Initiate` and `Vx_Terminate`, both of which deallocate
  platform-specific global resources.
**/

#ifndef Vx__LifecycleH
#define Vx__LifecycleH

#include "Status.h"
#include "_Expose.h"

/**
  ## Function `Vx_Initiate`

  This function initiates the native windowing context. This must be called
  before all other library functions.
**/
Vx__Expose VxStatus Vx_Initiate(void);

/**
  ## Function `Vx_Terminate`

  This function terminates the native windowing context. This must be called
  after all other library functions.
**/
Vx__Expose VxStatus Vx_Terminate(void);

#endif
