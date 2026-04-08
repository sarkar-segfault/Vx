#include "Internal.h"

#include <Windows.h>
#include <stdbool.h>

#include "Vx/Event.h"

#define VxEventRing__Wrap(var) var = (var + 1) % VxEventRing_Length

bool VxEventRing_Put(VxEventRing* ring, VxEvent event) {
  if (!ring) return false;

  ring->events[ring->head] = event;
  VxEventRing__Wrap(ring->head);

  if (ring->full) {
    VxEventRing__Wrap(ring->tail);
  }

  ring->full = ring->head == ring->tail;
  return true;
}

bool VxEventRing_Pop(VxEventRing* ring, VxEvent* event) {
  if (!ring || !event || (!ring->full && ring->head == ring->tail)) return false;

  *event = ring->events[ring->tail];
  VxEventRing__Wrap(ring->tail);

  ring->full = false;
  return true;
}
