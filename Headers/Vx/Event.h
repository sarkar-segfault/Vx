#ifndef Vx__EventH
#define Vx__EventH

#include <stdint.h>

typedef enum VxEventType {
  VxEventType_Close,
  VxEventType_Resize,
  VxEventType_Move,
  VxEventType_Focus,
  VxEventType_Blur,
  VxEventType_Minimize,
  VxEventType_Maximize,
  VxEventType_Restore,

  VxEventType_KeyPress,
  VxEventType_KeyRelease,
  VxEventType_CharSent,

  VxEventType_MouseMove,
  VxEventType_MousePress,
  VxEventType_MouseRelease,
  VxEventType_MouseWheel
} VxEventType;

typedef enum VxEventKey {
  VxEventKey_0,
  VxEventKey_1,
  VxEventKey_2,
  VxEventKey_3,
  VxEventKey_4,
  VxEventKey_5,
  VxEventKey_6,
  VxEventKey_7,
  VxEventKey_8,
  VxEventKey_9,

  VxEventKey_A,
  VxEventKey_B,
  VxEventKey_C,
  VxEventKey_D,
  VxEventKey_E,
  VxEventKey_F,
  VxEventKey_G,
  VxEventKey_H,
  VxEventKey_I,
  VxEventKey_J,
  VxEventKey_K,
  VxEventKey_L,
  VxEventKey_M,
  VxEventKey_N,
  VxEventKey_O,
  VxEventKey_P,
  VxEventKey_Q,
  VxEventKey_R,
  VxEventKey_S,
  VxEventKey_T,
  VxEventKey_U,
  VxEventKey_V,
  VxEventKey_W,
  VxEventKey_X,
  VxEventKey_Y,
  VxEventKey_Z,

  // TODO: add all keys
  VxEventKey_Space
} VxEventKey;

typedef enum VxEventButton {
  VxEventButton_MouseRight,
  VxEventButton_MouseLeft,
  VxEventButton_MouseCenter,
} VxEventButton;

typedef struct VxEventInfo {
  struct { uint32_t w, h; } size;
  struct { int32_t x, y; } pos;
  struct { int32_t delta; } wheel;
  VxEventKey key;
  VxEventButton button;
  char sent;
} VxEventInfo;

typedef struct VxEvent {
  VxEventType type;
  VxEventInfo info;
} VxEvent;

#endif
