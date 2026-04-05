#ifndef Vx__LifecycleH
#define Vx__LifecycleH

#include "_Expose.h"
#include <stdbool.h>

#ifndef VxWindow_Class
  #define VxWindow_Class "VxWindow"
#endif

Vx__Expose bool Vx_Initiate(void);

Vx__Expose bool Vx_Terminate(void);

#endif
