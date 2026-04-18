#ifndef Vx__StatusH
#define Vx__StatusH

#include "_Expose.h"

/**
  ## Enum `VxStatus`
  This enum contains enumerations which represent the different
  ways that a function can fail. `VxStatus_Pass` should always
  be the last here, since we use it in `VxStatus_Strings` as the
  length of the enum.
**/
typedef enum VxStatus {
  VxStatus_NotConfigured,
  VxStatus_WindowingFail,
  VxStatus_GraphicsFail,
  VxStatus_AllocFail,
  VxStatus_BadInput,

  VxStatus_Pass
} VxStatus;

/**
  ## Constant `VxStatus_Strings`
  This constant is a compile-time array of strings for each
  enumeration in `VxStatus`. `VxStatus_Pass` is used as the
  length of the array.
**/
Vx__Expose const char *const VxStatus_Strings[VxStatus_Pass];

#endif
