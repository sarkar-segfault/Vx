/**
  # Header `Vx.h`
  Umbrella header for all other public headers in the project.

  Instead of having to include all of the other headers individually, you can
  just include this one. IWYU pragmas also make an appearance here, so that
  the compiler doesn't yell that "yOu dIdN't UsE aLL oF THe sYMboLs".

  You may accidentally include more stuff than you need which can make compilation
  slower, but that doesn't really matter anymore since modern compilers are jacked.
**/

#ifndef Vx__H
#define Vx__H

// IWYU pragma: begin_exports

#include "Context.h"
#include "Event.h"
#include "Window.h"

// IWYU pragma: end_exports

#endif
