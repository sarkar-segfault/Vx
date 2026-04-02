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
