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

#define WM_MOVEP      (WM_APP+1)
#define WM_SIZEP      (WM_APP+2)
#define WM_CLOSEP     (WM_APP+3)
#define WM_SETFOCUSP  (WM_APP+4)
#define WM_KILLFOCUSP (WM_APP+5)

bool Vx__TranslateEvent(const MSG *msg, VxEvent *event);

#endif
