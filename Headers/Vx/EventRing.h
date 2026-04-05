#ifndef Vx__EventRingH
#define Vx__EventRingH

#include "Event.h"
#include "_Expose.h"
#include <stdbool.h>
#include <stddef.h>

#ifndef VxEventRing_Length
  #define VxEventRing_Length 64
#endif

typedef struct VxEventRing VxEventRing;

Vx__Expose bool VxEventRing_Push(VxEventRing *er, const VxEvent event);

Vx__Expose bool VxEventRing_Pop(VxEventRing *er, const VxEvent *event);

Vx__Expose bool VxEventRing_Head(VxEventRing *er, const size_t **head);

Vx__Expose bool VxEventRing_Tail(VxEventRing *er, const size_t **tail);

#endif
