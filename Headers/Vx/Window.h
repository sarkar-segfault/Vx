#ifndef Vx__WindowH
#define Vx__WindowH

#include "_Expose.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifndef VxWindow_Class
  #define VxWindow_Class "VxWindow"
#endif

#ifndef VxWindow_DefaultWidth
  #define VxWindow_DefaultWidth 800
#endif

#ifndef VxWindow_DefaultHeight
  #define VxWindow_DefaultHeight 600
#endif

#ifndef VxWindow_DefaultTitle
  #define VxWindow_DefaultTitle "VxWindow"
#endif

typedef struct VxWindow VxWindow;

Vx__Expose bool VxWindow_Create(VxWindow **window);

Vx__Expose bool VxWindow_Delete(VxWindow **window);

Vx__Expose bool VxWindow_Update(VxWindow *window);

Vx__Expose bool VxWindow_IsOpen(const VxWindow *window);

Vx__Expose bool VxWindow_GetFps(const VxWindow *window, uint8_t *fps);

Vx__Expose bool VxWindow_SetFps(VxWindow *window, const uint8_t fps);

Vx__Expose bool VxWindow_GetSize(const VxWindow *window, uint32_t *w, uint32_t *h);

Vx__Expose bool VxWindow_SetSize(const VxWindow *window, const uint32_t w, const uint32_t h);

Vx__Expose bool VxWindow_GetPos(const VxWindow *window, int32_t *x, int32_t *y);

Vx__Expose bool VxWindow_SetPos(const VxWindow *window, const int32_t x, const int32_t y);

Vx__Expose bool VxWindow_GetTitle(const VxWindow *window, char *buf, const size_t len);

Vx__Expose bool VxWindow_SetTitle(const VxWindow *window, const char *const title);

Vx__Expose bool VxWindow_GetOpacity(const VxWindow *window, float *o);

Vx__Expose bool VxWindow_SetOpacity(const VxWindow *window, const float o);

Vx__Expose bool VxWindow_Minimize(const VxWindow *window);

Vx__Expose bool VxWindow_Restore(const VxWindow *window);

Vx__Expose bool VxWindow_Maximize(const VxWindow *window);

Vx__Expose bool VxWindow_Show(const VxWindow *window);

Vx__Expose bool VxWindow_Hide(const VxWindow *window);

Vx__Expose bool VxWindow_Focus(const VxWindow *window);

Vx__Expose bool VxWindow_Flash(const VxWindow *window);

#endif
