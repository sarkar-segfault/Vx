/**
  This file defines the enum `VxStatus` for error management.

  This file defines the enum `VxStatus`, its enumerations, and
  its accompanying `VxStatus_Strings` to convert between enumerations
  and their string counterparts.
**/

#ifndef Vx__StatusH
#define Vx__StatusH

#include "_Expose.h"

/**
  ## Enum `VxStatus`
  Error codes to signal problems/success.

  This enum contains enumerations which represent the different
  ways that a function can fail. `VxStatus_Pass` should always
  be the last here, since we use it in `VxStatus_Strings` as the
  length of the enum.
**/
typedef enum VxStatus {
  /**
    ### Member `VxStatus_NotConfigured`
    The specified feature is unconfigured.

    Sent when graphics work is tried and not `VxContext_UseAngle`.
    Also when opacity configuration is tried and `VxFlag_Unlayered`.
  **/
  VxStatus_NotConfigured,

  /**
    ### Member `VxStatus_WindowingFail`
    Encountered a windowing-related failure.
  **/
  VxStatus_WindowingFail,

  /**
    ### Member `VxStatus_GraphicsFail`
    Encounteed a graphics-related failure.
  **/
  VxStatus_GraphicsFail,

  /**
    ### Member `VxStatus_AllocFail`
    Failed to allocate memory using `calloc`.
  **/
  VxStatus_AllocFail,

  /**
    ### Member `VxStatus_BadInput`
    Bad arguments, like `NULL` or invalid handles, were passed.
  **/
  VxStatus_BadInput,

  /**
    ### Member `VxStatus_Pass`
    The operation completed successfully.
  **/
  VxStatus_Pass
} VxStatus;

/**
  ## Constant `VxStatus_Strings`
  Strings for each `VxStatus`.

  This constant is a compile-time array of strings for each
  enumeration in `VxStatus`. `VxStatus_Pass` is used as the
  length of the array.
**/
Vx__Expose const char *const VxStatus_Strings[VxStatus_Pass];

#endif
