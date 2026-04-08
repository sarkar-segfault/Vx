/*
  `Event.h` - defines types for handling input events triggered by the user.

  This file defines the tagged union `VxEvent` and other types to complement it.
  Enum variants are not documented, and I don't plan to document them at all,
  since there are simply too many of them.
*/

#ifndef Vx__EventH
#define Vx__EventH

#include <stdint.h>

/*
  `VxEventType` - enum for representing the types of events we can handle.
  Only cross-platform events are to be added here.
*/
typedef enum VxEventType {
  VxEventType_Resize,
  VxEventType_Move,
  VxEventType_Focus,
  VxEventType_Blur,
  VxEventType_Minimize,
  VxEventType_Maximize,

  VxEventType_KeyPress,
  VxEventType_KeyRelease,
  VxEventType_CharSent,

  VxEventType_MouseMove,
  VxEventType_MousePress,
  VxEventType_MouseRelease,
  VxEventType_MouseWheel
} VxEventType;

/*
  `VxEventKey` - represents all keys we can detect.
  Only cross-platform keys are to be added here.
*/
typedef enum VxEventKey {
  VxEventKey_Unknown,

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

/*
  `VxEventMod` - represents all the bitflag modifiers we can have on our keys.
  At most, we can have 8 variants, because we use `uint8_t` to store the flags.
  Only cross-platform mods are to be added here.
*/
typedef enum VxEventMod {
  VxEventMod_Shift   = 1 << 0,
  VxEventMod_Control = 1 << 1,
  VxEventMod_Alt     = 1 << 2,
} VxEventMod;

/*
  `VxEventButton` - represents all the mouse buttons that we can handle.
  Only cross-platform buttons are to be added here.
*/
typedef enum VxEventButton {
  VxEventButton_MouseRight,
  VxEventButton_MouseLeft,
  VxEventButton_MouseCenter,
} VxEventButton;

/*
  `VxEventInfo` - union for representing extra data for some events.

  This union contains extra data/structs for different events. All events do not
  have/need an entry here. We try to reuse members as much as we can. For example,
  `pos` is be reused for mouse movements too, besides window movements.
*/
typedef union VxEventInfo {
  struct { uint32_t w, h; } size;
  struct { int32_t x, y; } pos;
  struct { int32_t delta; } wheel;
  struct { VxEventKey key; uint8_t mod; } press;
  VxEventKey release;
  VxEventButton button;
  char sent;
  int32_t delta;
} VxEventInfo;

/*
  `VxEvent` - a tagged union containing all the data we need about an event.

  This struct is comprised of a `VxEventType` tag, and a `VxEventInfo` union. Do
  not try to access fields on the `VxEventInfo` unless assured by the `VxEventType`.
*/
typedef struct VxEvent {
  VxEventType type;
  VxEventInfo info;
} VxEvent;

#endif
