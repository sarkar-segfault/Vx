#ifndef Vx__Win32InternalH
#define Vx__Win32InternalH

#include "../Internal.h"

#ifdef _WIN32
  #ifndef NOMINMAX
    #define NOMINMAX
  #endif

  #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
  #endif

  #include <Windows.h>  // IWYU pragma: export
#else
  #error "Vx only supports Win32 as of now..."
#endif

#ifndef VxWindow_Class
  #define VxWindow_Class "VxWindow"
#endif

typedef struct VxWindowData {
  VxEventRing ring;
  bool is_changing;
  VxFlags flags;
  uint32_t w, h;
  int32_t x, y;
} VxWindowData;

#endif
