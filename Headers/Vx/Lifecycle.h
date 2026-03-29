/**
  @file Lifecycle.h
  @since 0.1.0
  @author Adhrit Sarkar <adhritsarkar@proton.me>
  @brief Contains functions to manage the library's lifecycle.
*/

#ifndef Vx__LifecycleH
#define Vx__LifecycleH

#include "_Expose.h"
#include <stdbool.h>

/**
  @brief Initates the library so it can create windows. Must be called before `VxWindow_Create`
  @returns Whether initiation was successful.
*/
Vx__Expose bool Vx_Initiate(void);

/**
  @brief Terminates the library so it can no longer create windows. `VxWindow_Create` cannot be called after this.
*/
Vx__Expose void Vx_Terminate(void);

/**
  @brief Get the window class initiated previously.
  @returns The window class initiated in `Vx_Initiate`.
*/
Vx__Expose void *Vx_GetWindowClass(void);

#endif
