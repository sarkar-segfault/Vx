/**
  @file Window.c
  @since 0.1.0
  @license MIT
  @author Adhrit Sarkar <adhritsarkar@proton.me>
  @brief Defines semantics for the VxWindow struct. As of now, only supports windows.
*/

#include "Vx/Window.h"
#include <stdbool.h>

#ifdef _WIN32
  #define NOMINMAX
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h>
#else
  #error "VxWindow only supports Win32"
#endif
