#ifndef Vx__EventRingH
#define Vx__EventRingH

#include "Event.h"
#include "_Expose.h"
#include <stdbool.h>
#include <stddef.h>

#ifndef VxEventRing_Length
  #define VxEventRing_Length 64
#endif

/**
  @since 0.1.0
  @brief A ring buffer of `VxEventRing_Length` `VxEvent`s, that wraps around when filled.
*/
typedef struct VxEventRing VxEventRing;

/**
  @since 0.1.0
  @brief Push an event onto the event ring.
  @returns Whether pushing was successful.
*/
Vx__Expose bool VxEventRing_Push(VxEventRing *er, const VxEvent event);

/**
  @since 0.1.0
  @brief Pop the last event from the event ring.
  @returns Whether popping was successful.
*/
Vx__Expose bool VxEventRing_Pop(VxEventRing *er, const VxEvent *event);

/**
  @since 0.1.0
  @returns The latest event from the event ring.
*/
Vx__Expose bool VxEventRing_Head(VxEventRing *er, const size_t **head);

/**
  @since 0.1.0
  @returns The last event from the event ring.
*/
Vx__Expose bool VxEventRing_Tail(VxEventRing *er, const size_t **tail);

#endif
