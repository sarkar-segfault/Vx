cmake_minimum_required(VERSION 3.10..4.2)

project(
  Vx
  LANGUAGES C
  VERSION 0.1.0
  DESCRIPTION "A windowing library for simpletons and wizards alike"
)

add_library(Vx Sources/Window.c Sources/Context.c Sources/Internal.c Sources/Lifecycle.c)

set(VxWindow_DefaultWidth 800 CACHE STRING "The default width for all windows")
set(VxWindow_DefaultHeight 600 CACHE STRING "The default height for all windows")
set(VxWindow_DefaultTitle "VxWindow" CACHE STRING "The default title for all windows")
set(VxEventRing_Length 128 CACHE STRING "The length of the event circular queue/ring buffer")
option(VxContext_UseAngle "Whether to use the ANGLE OpenGL ES implementation to create graphics contexts" ON)

if(DEFINED VxWindow_DefaultWidth)
  target_compile_definitions(Vx PUBLIC VxWindow_DefaultWidth=${VxWindow_DefaultWidth})
endif()

if(DEFINED VxWindow_DefaultHeight)
  target_compile_definitions(Vx PUBLIC VxWindow_DefaultHeight=${VxWindow_DefaultHeight})
endif()

if(DEFINED VxWindow_DefaultTitle)
  target_compile_definitions(Vx PUBLIC VxWindow_DefaultTitle="${VxWindow_DefaultTitle}")
endif()

if(DEFINED VxEventRing_Length)
  target_compile_definitions(Vx PUBLIC VxEventRing_Length=${VxEventRing_Length})
endif()

if(VxContext_UseAngle)
  target_compile_definitions(Vx PUBLIC VxContext_UseAngle)
  target_link_libraries(Vx PRIVATE EGL GLESv2)
endif()

if(BUILD_SHARED_LIBS)
  target_compile_definitions(Vx PRIVATE Vx__Shared)
endif()

target_compile_definitions(Vx PRIVATE Vx__Build)

target_compile_definitions(
  Vx PUBLIC
  Vx_Version="${PROJECT_VERSION}"
  Vx_VersionMajor="${PROJECT_VERSION_MAJOR}"
  Vx_VersionMinor="${PROJECT_VERSION_MINOR}"
  Vx_VersionMicro="${PROJECT_VERSION_PATCH}"
)

target_include_directories(Vx PUBLIC Headers)

target_compile_features(Vx PUBLIC c_std_99)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows" OR CMAKE_SYSTEM_NAME STREQUAL "MSYS")
  set(VxWindow_Class "VxWindow" CACHE STRING "The name of the Win32 window class")

  if(DEFINED VxWindow_Class)
    target_compile_definitions(Vx PUBLIC VxWindow_Class="${VxWindow_Class}")
  endif()

  target_link_libraries(Vx PRIVATE user32)
endif()

add_executable(test test.c)

target_link_libraries(test PRIVATE Vx)
