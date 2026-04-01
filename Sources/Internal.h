#ifndef Vx__InternalH
#define Vx__InternalH

#ifdef _WIN32
  #define NOMINMAX
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h> // IWYU pragma: export
#else
  #error "Vx only supports Win32 as of now..."
#endif

#endif
