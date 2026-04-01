#ifndef Vx__InternalH
#define Vx__InternalH

#ifdef _WIN32
  #define NOMINMAX
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
#else
  #error "Vx only supports Win32 as of now..."
#endif

#ifdef _DEBUG
  #include <stdio.h> // IWYU pragma: export
  #define Vx__Fatal(msg) puts(msg)
#else
  #define Vx__Fatal(msg)
#endif

#define Vx__AssertLog(exp, msg) if (!(exp)) { Vx__Fatal(msg); return false; }

#endif
