#ifndef Vx__EventRingH
#define Vx__EventRingH

#include <stdbool.h>
#include <stddef.h>

#include "Vx/Event.h"
#include "Vx/_Expose.h"

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
