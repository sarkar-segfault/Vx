#ifndef Vx__FlagH
#define Vx__FlagH

#include <stdint.h>

typedef enum VxFlag {
  VxFlag_Invisible = 1u << 0,
  VxFlag_Maximized = 1u << 1,
  VxFlag_Minimized = 1u << 2,
  VxFlag_Unlayered = 1u << 3
} VxFlag;

typedef uint8_t VxFlags;

#endif
