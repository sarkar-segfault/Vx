/**
  Define flags for setting and querying window state.

  This file defines the `VxFlag` enum and its members. The enum
  is used for checking window state.
**/

#ifndef Vx__FlagH
#define Vx__FlagH

#include <stdint.h>

/**
  ## Enum `VxFlag`
  Represents all flags that we can handle.

  When creating a window, you can specify these flags so that window
  creation differs or does things differently. Some flags can also be
  modified later, but only internally. To you, they are immutable.
**/
typedef enum VxFlag {
  /**
    ### Member `VxFlag_Invisible`
    Whether the window is invisible.
  **/
  VxFlag_Invisible = 1u << 0,

  /**
    ### Member `VxFlag_Maximized`
    Whether the window is maximized.
  **/
  VxFlag_Maximized = 1u << 1,

  /**
    ### Member `VxFlag_Minimized`
    Whether the window is minimized.
  **/
  VxFlag_Minimized = 1u << 2,

  /**
    ### Member `VxFlag_Unlayered`
    Whether the window has opacity.
  **/
  VxFlag_Unlayered = 1u << 3
} VxFlag;

/**
  ## Typedef `VxFlags`
  Type alias for `uint8_t` to store flags. This is used so that if we
  have to change integer types later, we can do it at one spot.
**/
typedef uint8_t VxFlags;

#endif
