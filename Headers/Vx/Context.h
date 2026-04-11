/*
  `Context.h` - functions for managing the lifecycle of the library.

  This header defines functions for managing the lifecycle of the library via
  the `VxContext` wrapper.
*/

#ifndef Vx__LifecycleH
#define Vx__LifecycleH

#include <stdbool.h>

#include "_Expose.h"

typedef struct VxContext *VxContext;

Vx__Expose bool VxContext_Initiate(VxContext *device);

Vx__Expose bool VxContext_Terminate(VxContext device);

#endif
