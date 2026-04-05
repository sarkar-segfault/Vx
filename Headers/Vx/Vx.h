/*
  `Vx.h` is an umbrella header for all other public headers in the project.
  Introduced in version `0.1.0`.
  
  Instead of having to include all of the other headers individually, you can
  just include this one.

  NOTE:
  You may accidentally include more stuff than you need which can make compilation
  slower, but that doesn't really matter anymore since modern compilers are jacked.
*/

/*
  Vx - The windowing library for simpletons and wizards alike.

  Vx is a simple windowing library that I made because GLFW sucks and RGFW inspired me.
  As of now, it only works on Microslop Windows, and I think it'll remain that way until
  mum finally lets me install ArchLinux on my laptop.

  The name does not mean anything, it's just meant to be cool. I think I'll make more libraries
  like Rx for rendering, and a framework called Gx that ties all this together. Anyway, enjoy.
*/

#ifndef Vx__H
#define Vx__H

// IWYU pragma: begin_exports

#include "Lifecycle.h"
#include "Window.h"

// IWYU pragma: end_exports

#endif
