#include "Internal.h"

#include <stdbool.h>

#include "Vx/Event.h"
#include "Vx/Status.h"

const char *const VxStatus_Strings[VxStatus_Pass] = {
    "encountered window-related failure",
    "encountered graphics-related failure",
    "failed to allocate object",
    "called with invalid parameters",
};

#define VxEventRing__Wrap(var) var = (var + 1) % VxEventRing_Length

bool VxEventRing_Put(VxEventRing *ring, VxEvent event) {
  if (!ring) return false;

  VxEvent *latest = &ring->events[ring->head - 1];

  if (latest->type == event.type && latest->type == VxEventType_MouseMove &&
      Vx_Near(latest->info.pos.x, event.info.pos.x) &&
      Vx_Near(latest->info.pos.y, event.info.pos.y)) {
    latest->info.pos.x = event.info.pos.x;
    latest->info.pos.y = event.info.pos.y;
    return true;
  }

  ring->events[ring->head] = event;
  VxEventRing__Wrap(ring->head);

  if (ring->full) {
    VxEventRing__Wrap(ring->tail);
  }

  ring->full = ring->head == ring->tail;
  return true;
}

bool VxEventRing_Pop(VxEventRing *ring, VxEvent *event) {
  if (!ring || !event || (!ring->full && ring->head == ring->tail)) return false;

  *event = ring->events[ring->tail];
  VxEventRing__Wrap(ring->tail);

  ring->full = false;
  return true;
}
