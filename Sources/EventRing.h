#ifndef Vx__EventRingH
#define Vx__EventRingH

#include "Vx/Event.h"
#include <stdbool.h>
#include <stddef.h>

#ifndef VxEventRing_Length
  #define VxEventRing_Length 64
#endif

typedef struct VxEventRing {
  VxEvent events[VxEventRing_Length];
  size_t head, tail;
  bool full;
} VxEventRing;

bool VxEventRing_Put(VxEventRing *ring, VxEvent event);

bool VxEventRing_Pop(VxEventRing *ring, VxEvent *event);

#endif
