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
  
  VxEventKey_Escape,
  VxEventKey_Tab,
  VxEventKey_CapsLock,
  VxEventKey_Space,
  VxEventKey_Enter,
  VxEventKey_Backspace,

  VxEventKey_Shift,
  VxEventKey_Control,
  VxEventKey_Alt,
  VxEventKey_Insert,
  VxEventKey_Delete,
  VxEventKey_Home,
  VxEventKey_End,
  VxEventKey_PageUp,
  VxEventKey_PageDown,
  VxEventKey_Left,
  VxEventKey_Right,
  VxEventKey_Up,
  VxEventKey_Down,
 
  VxEventKey_F1,
  VxEventKey_F2,
  VxEventKey_F3,
  VxEventKey_F4,
  VxEventKey_F5,
  VxEventKey_F6,
  VxEventKey_F7,
  VxEventKey_F8,
  VxEventKey_F9,
  VxEventKey_F10,
  VxEventKey_F11,
  VxEventKey_F12,
  
  VxEventKey_NumLock,
  VxEventKey_Numpad0,
  VxEventKey_Numpad1,
  VxEventKey_Numpad2,
  VxEventKey_Numpad3,
  VxEventKey_Numpad4,
  VxEventKey_Numpad5,
  VxEventKey_Numpad6,
  VxEventKey_Numpad7,
  VxEventKey_Numpad8,
  VxEventKey_Numpad9,
  VxEventKey_NumpadMultiply,
  VxEventKey_NumpadAdd,
  VxEventKey_NumpadSubtract,
  VxEventKey_NumpadDecimal,
  VxEventKey_NumpadDivide,
  
  VxEventKey_Semicolon, 
  VxEventKey_Equals, 
  VxEventKey_Comma, 
  VxEventKey_Minus, 
  VxEventKey_Period, 
  VxEventKey_Slash, 
  VxEventKey_Backtick, 
  VxEventKey_LeftBracket, 
  VxEventKey_Backslash, 
  VxEventKey_RightBracket, 
  VxEventKey_Quote,
} VxEventKey;

typedef enum VxEventMod {
  VxEventMod_None    = 0,
  VxEventMod_Shift   = 1 << 0,
  VxEventMod_Control = 1 << 1,
  VxEventMod_Alt     = 1 << 2,
} VxEventMod;

typedef enum VxEventButton {
  VxEventButton_MouseRight,
  VxEventButton_MouseLeft,
  VxEventButton_MouseCenter,
} VxEventButton;

typedef union VxEventInfo {
  struct { uint32_t w, h; } size;
  struct { int32_t x, y; } pos;
  struct { int32_t delta; } wheel;
  struct { VxEventKey key; uint16_t mod; } press;
  VxEventKey release;
  VxEventButton button;
  char sent;
} VxEventInfo;

typedef struct VxEvent {
  VxEventType type;
  VxEventInfo info;
} VxEvent;

#endif
