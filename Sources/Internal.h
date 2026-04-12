#ifndef Vx__InternalH
#define Vx__InternalH

// IWYU pragma: begin_exports
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
// IWYU pragma: end_exports

#include "Vx/Event.h"
#include "Vx/_Expose.h"

#ifdef VxContext_UseAngle
  // IWYU pragma: begin_exports
  #include <EGL/egl.h>
  #include <EGL/eglext.h>
  #include <EGL/eglext_angle.h>
  // IWYU pragma: end_exports
#endif

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

#define Vx__Error(msg) fprintf(stderr, "[%s] - %s\n", __func__, msg)

// (VxWindow_MountGraphics)
#ifndef VxEventRing_Length
  #define VxEventRing_Length 128
#endif

#ifdef VxContext_UseAngle
struct VxContext {
  EGLDisplay display;
  EGLConfig config;
};
#else
struct VxContext {
  char _;
};
#endif

typedef struct VxEventRing {
  VxEvent events[VxEventRing_Length];
  size_t head, tail;
  bool full;
} VxEventRing;

Vx__Extern bool VxEventRing_Put(VxEventRing *ring, VxEvent event);
Vx__Extern bool VxEventRing_Pop(VxEventRing *ring, VxEvent *event);

typedef struct VxWindowData {
  VxEventRing ring;
  bool is_changing;
  uint32_t w, h;
  int32_t x, y;
} *VxWindowData;

#endif
