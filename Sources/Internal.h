#ifndef Vx__InternalH
#define Vx__InternalH

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglext_angle.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>  // IWYU pragma: export

#include "Vx/Event.h"

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

#define Vx__Error(msg) fprintf(stderr, "%s: %s\n", __func__, msg)

#ifndef VxEventRing_Length
  #define VxEventRing_Length 64
#endif

struct VxContext {
  EGLDisplay display;
  EGLConfig config;
};

typedef struct VxEventRing {
  VxEvent events[VxEventRing_Length];
  size_t head, tail;
  bool full;
} *VxEventRing;

bool VxEventRing_Put(VxEventRing ring, VxEvent event);

bool VxEventRing_Pop(VxEventRing ring, VxEvent *event);

#endif
