#ifndef Vx__RingH
#define Vx__RingH

#include "Event.h"
#include "_Expose.h"
#include <stdbool.h>
#include <stddef.h>

#ifndef Vx__RingLength
  #define Vx__RingLength 64
#endif

/**
  @since 0.1.0
  @brief A ring buffer of `Vx__RingLength` `VxEvent`s, that wraps around when filled.
*/
typedef struct VxRing VxRing;

/**
  @since 0.1.0
  @brief Push an event onto the event ring.
  @returns Whether pushing was successful.
*/
Vx__Expose bool VxRing_Push(VxRing *eq, const VxEvent event);

/**
  @since 0.1.0
  @brief Pop the last event from the event ring.
  @returns Whether popping was successful.
*/
Vx__Expose bool VxRing_Pop(VxRing *eq, const VxEvent *event);

/**
  @since 0.1.0
  @returns The latest event from the event ring.
*/
Vx__Expose bool VxRing_Head(VxRing *eq, const size_t **head);

/**
  @since 0.1.0
  @returns The last event from the event ring.
*/
Vx__Expose bool VxRing_Tail(VxRing *eq, const size_t **tail);

#endif
