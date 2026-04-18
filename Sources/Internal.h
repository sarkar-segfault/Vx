#ifndef Vx__InternalH
#define Vx__InternalH

// IWYU pragma: begin_exports
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
// IWYU pragma: end_exports

#include "Vx/Event.h"
#include "Vx/Flag.h"
#include "Vx/_Expose.h"

#ifdef VxContext_UseAngle
  // IWYU pragma: begin_exports
  #include <EGL/egl.h>
  #include <EGL/eglext.h>
  #include <EGL/eglext_angle.h>
  // IWYU pragma: end_exports
#endif

#ifndef VxEventRing_Length
  #define VxEventRing_Length 128
#endif

typedef struct VxEventRing {
  VxEvent events[VxEventRing_Length];
  size_t head, tail;
  bool full;
} VxEventRing;

Vx__Extern bool VxEventRing_Put(VxEventRing *ring, VxEvent event);
Vx__Extern bool VxEventRing_Pop(VxEventRing *ring, VxEvent *event);

#endif
