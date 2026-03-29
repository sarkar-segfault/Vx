/**
  @file Vx__Expose.h
  @since 0.1.0
  @license MIT
  @author Adhrit Sarkar <adhritsarkar@proton.me>
  @brief Defines macros which allow for easy exposure of public functions on different platforms.
*/

#ifndef Vx__ExposeH
#define Vx__ExposeH

#ifdef Vx__Shared
  #ifdef _WIN32
    #ifdef Vx__Build
      #define Vx__Export __declspec(dllimport)
    #else
      #define Vx__Export __declspec(dllexport)
    #endif
  #elif defined(__GNUC__)
    #define Vx__Export __attribute__((visibility("default")))
  #else
    #define Vx__Export
  #endif
#endif

#ifdef __cplusplus
  #define Vx__Extern extern "C"
#else
  #define Vx__Extern extern
#endif

#define Vx__Expose Vx__Extern Vx__Export

#endif
