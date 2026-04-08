#ifndef Vx__InternalH
#define Vx__InternalH

#include "Vx/Event.h"
#include <stdbool.h>
#include <stdio.h> // IWYU pragma: export

#ifdef _WIN32
  #define NOMINMAX
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h> // IWYU pragma: export
#else
  #error "Vx only supports Win32 as of now..."
#endif

#define Vx__Error(msg) fprintf(stderr, "%s: %s\n", __func__, msg)

bool Vx__TranslateEvent(const MSG *msg, VxEvent *event);

#endif
