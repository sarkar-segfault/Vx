/*
  `Lifecycle.h` - functions for managing the lifecycle of the library.
  
  Defines `Vx_Initiate` and `Vx_Terminate` specifically.
*/

#ifndef Vx__LifecycleH
#define Vx__LifecycleH

#include "_Expose.h"
#include <stdbool.h>

/*
  `Vx_Initiate` - initiate the library for usage.
  
  This function must be called before any `VxWindow_Create` calls. It sets up
  platform specific contexts so that we can create windows without duplicating
  data like window class on windows.
*/
Vx__Expose bool Vx_Initiate(void);

/*
  `Vx_Terminate` - terminate the library for usage.
  
  Once this function is called, no more windows can be created, unless you initiate
  the library once again. This function releases platform specific contexts like
  window class on windows as they are no longer needed.
*/
Vx__Expose bool Vx_Terminate(void);

#endif
