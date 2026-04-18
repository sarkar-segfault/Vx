#ifndef Vx__TestsIncludeH
#define Vx__TestsIncludeH

// IWYU pragma: begin_exports
#include <stdio.h>

#include "Vx/Vx.h"
// IWYU pragma: end_exports

#define CHECK(s, v)            \
  s = v;                       \
  if (s != VxStatus_Pass) {    \
    puts(VxStatus_Strings[s]); \
  }

#endif
