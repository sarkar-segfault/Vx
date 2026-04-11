#include "Internal.h"

#include <stdbool.h>
#include <stdlib.h>

#include "Vx/Event.h"

#define VxEventRing__Wrap(var) var = (var + 1) % VxEventRing_Length

#define Vx__INear(latest, event, a, b) abs(latest->info.a - event.info.a) <= 16 && abs(latest->info.b - event.info.b) <= 16

#define Vx__UNear(latest, event, a, b) latest->info.a - event.info.a <= 16 && latest->info.b - event.info.b <= 16

bool VxEventRing_Put(VxEventRing ring, VxEvent event) {
  if (!ring) return false;

  VxEvent *latest = &ring->events[ring->head - 1];

  if (latest->type == event.type) {
    if ((latest->type == VxEventType_Move || latest->type == VxEventType_MouseMove) && Vx__INear(latest, event, pos.x, pos.y)) {
      latest->info.pos.x = event.info.pos.x;
      latest->info.pos.y = event.info.pos.y;
      return true;
    } else if (latest->type == VxEventType_Resize && latest->type == event.type && Vx__UNear(latest, event, size.w, size.h)) {
      latest->info.size.w = event.info.size.w;
      latest->info.size.h = event.info.size.h;
      return true;
    }
  }

  ring->events[ring->head] = event;
  VxEventRing__Wrap(ring->head);

  if (ring->full) {
    VxEventRing__Wrap(ring->tail);
  }

  ring->full = ring->head == ring->tail;
  return true;
}

bool VxEventRing_Pop(VxEventRing ring, VxEvent *event) {
  if (!ring || !event || (!ring->full && ring->head == ring->tail)) return false;

  *event = ring->events[ring->tail];
  VxEventRing__Wrap(ring->tail);

  ring->full = false;
  return true;
}
