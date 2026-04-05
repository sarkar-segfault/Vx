/*
  `EventRing.h` - defines types and methods for interacting with the event ring.

  This file defines `VxEventRing` and its methods.
*/

#ifndef Vx__EventRingH
#define Vx__EventRingH

#include <stdbool.h>
#include <stddef.h>

/*
  `VxEventRing_Length` - the length that the event ring is allocated to have.

  This macro is the `size_t` that controls the size of the event ring of a window. Try to
  not set this too high, because it causes higher allocation, slower performance, and frankly
  you do not need more than 64 events at a time unless you are either a magician or a bot.
*/
#ifndef VxEventRing_Length
  #define VxEventRing_Length 64
#endif

/*
  `VxEventRing` - the circular queue for storing window events.

  Every frame when a window receives events from the user, it stores it inside its event ring
  for you to handle. The event ring is a circular queue which keeps track of a head and tail.
  It is comprised of `VxEvent` objects and should preferably only be queried, and not modified,
  by the user.
*/
typedef struct VxEventRing VxEventRing;

#endif
