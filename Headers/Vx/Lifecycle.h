/*
  `Lifecycle.h` - functions for managing the lifecycle of the library.
  Introduced in version `0.1.0`.

  Defines `Vx_Initiate` and `Vx_Terminate` specifically.
*/

#ifndef Vx__LifecycleH
#define Vx__LifecycleH

#include "_Expose.h"
#include <stdbool.h>

/*
  `Vx_Initiate` - initiate the library for usage.

  This function performs any activity necessary before windows can be created.
  The exact behavior depends on the platform; they are listed below:

  On `_WIN32`, a `WNDCLASSEX` is registered by the name of `VxWindow_Class`;
  on other platforms, we panic.
*/
Vx__Expose bool Vx_Initiate(void);

/*
  `Vx_Terminate` - terminate the library for usage.

  This function performs cleanup and any operations to undo `Vx_Initiate`.
  The exact behaviour is dependent of the platform; they are listed below:

  On `_WIN32`, the `WNDCLASSEX` by the name of `VxWindow_Class` is unregistered.
  On other platforms, we panic.
*/
Vx__Expose bool Vx_Terminate(void);

#endif
