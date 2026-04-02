/**
  @file Window.h
  @since 0.1.0
  @author Adhrit Sarkar <adhritsarkar@proton.me>
  @brief Defines the `VxWindow` struct and its operations.
*/

#ifndef Vx__WindowH
#define Vx__WindowH

#include "_Expose.h"
#include <stdbool.h>
#include <stdint.h>

#ifndef VxWindow__DefaultWidth
  #define VxWindow__DefaultWidth 800
#endif

#ifndef VxWindow__DefaultHeight
  #define VxWindow__DefaultHeight 600
#endif

#ifndef VxWindow__DefaultTitle
  #define VxWindow__DefaultTitle "VxWindow"
#endif

/**
  @since 0.1.0
  @brief Represents a platform-specific window.
*/
typedef struct VxWindow VxWindow;

/**
  @since 0.1.0
  @brief Creates a native platform window.
  @returns Whether creation was successful.
*/
Vx__Expose bool VxWindow_Create(VxWindow **window, const uint8_t fps);

/**
  @since 0.1.0
  @brief Deletes the specified window.
  @returns Whether deletion was successful.
*/
Vx__Expose bool VxWindow_Delete(VxWindow *window);

/**
  @since 0.1.0
  @brief Updates the specified window.
  @returns Whether the window successfully updated.
*/
Vx__Expose bool VxWindow_Update(VxWindow *window);

/**
  @since 0.1.0
  @brief Checks whether the window is still open.
  @returns Whether the specified window is still valid.
*/
Vx__Expose bool VxWindow_IsOpen(const VxWindow *window);

/**
  @since 0.1.0
  @brief Gets the dimensions of the window.
  @returns The width and height of the specified window.
*/
Vx__Expose bool VxWindow_GetSize(const VxWindow *window, uint32_t *w, uint32_t *h);

/**
  @since 0.1.0
  @brief Sets the dimensions of the window.
  @returns Whether resizing was successful.
*/
Vx__Expose bool VxWindow_SetSize(const VxWindow *window, const uint32_t w, const uint32_t h);

/**
  @since 0.1.0
  @brief Gets the position of the window.
  @returns The x and y coordinates of the specified window.
*/
Vx__Expose bool VxWindow_GetPos(const VxWindow *window, int32_t *x, int32_t *y);

/**
  @since 0.1.0
  @brief Sets the position of the window.
  @returns Whether repositioning was successful.
*/
Vx__Expose bool VxWindow_SetPos(const VxWindow *window, const int32_t x, const int32_t y);

/**
  @since 0.1.0
  @brief Gets the current title of the window.
  @returns Whether fetching the title was successful.
*/
Vx__Expose bool VxWindow_GetTitle(const VxWindow *window, char *buf, const size_t len);

/**
  @since 0.1.0
  @brief Sets the title of the specified window.
  @returns Whether setting the title was successful.
*/
Vx__Expose bool VxWindow_SetTitle(const VxWindow *window, const char *const title);

/**
  @since 0.1.0
  @brief Gets the opacity of the specified window.
  @returns Whether retrieving the opacity was successful.
*/
Vx__Expose bool VxWindow_GetOpacity(const VxWindow *window, float *o);

/**
  @since 0.1.0
  @brief Sets the opacity of the specified window.
  @returns Whether setting the opacity was successful.
*/
Vx__Expose bool VxWindow_SetOpacity(const VxWindow *window, const float o);

/**
  @since 0.1.0
  @brief Minimizes the specified window.
  @returns Whether minimizing was successful.
*/
Vx__Expose bool VxWindow_Minimize(const VxWindow *window);

/**
  @since 0.1.0
  @brief Restores the previous state of the window.
  @returns Whether restoration was successful.
*/
Vx__Expose bool VxWindow_Restore(const VxWindow *window);

/**
  @since 0.1.0
  @brief Maximizes the specified window.
  @returns Whether maximizing was successful.
*/
Vx__Expose bool VxWindow_Maximize(const VxWindow *window);

/**
  @since 0.1.0
  @brief Makes the specified window visible.
  @returns Whether showing was successful.
*/
Vx__Expose bool VxWindow_Show(const VxWindow *window);

/**
  @since 0.1.0
  @brief Makes the specified window visible.
  @returns Whether hiding was successful.
*/
Vx__Expose bool VxWindow_Hide(const VxWindow *window);

/**
  @since 0.1.0
  @brief Focuses the specified window.
  @returns Whether focusing was successful.
*/
Vx__Expose bool VxWindow_Focus(const VxWindow *window);

/**
  @since 0.1.0
  @brief Flash for the user's attention until the window is focused.
  @returns Whether flashing was successful.
*/
Vx__Expose bool VxWindow_Flash(const VxWindow *window);

#endif
