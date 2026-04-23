cmake_minimum_required(VERSION 3.12..4.3)

project(
  Vx
  LANGUAGES C
  VERSION 0.1.0
  HOMEPAGE_URL "https://github.com/sarkar-segfault/Vx"
  DESCRIPTION "A windowing library for simpletons and wizards alike"
)

add_library(Vx Sources/EventRing.c Sources/Status.c)

set(VxEventRing_Length 128 CACHE STRING "The length of the event circular queue/ring buffer")

option(Vx_Testing "Whether to build tests and enable CTest integration" OFF)
option(VxContext_UseAngle "Whether to use the ANGLE OpenGL ES implementation to create graphics contexts" ON)
option(VxEvent_SendUnknown "Whether to send VxEventType_KeyPress/VxEventType_KeyRelease events with VxEventKey_Unknown" ON)

target_compile_definitions(Vx PUBLIC VxEventRing_Length=${VxEventRing_Length})

if(VxContext_UseAngle)
  target_compile_definitions(Vx PUBLIC VxContext_UseAngle)
  target_link_libraries(Vx PRIVATE EGL GLESv2)
endif()

if(VxEvent_SendUnknown)
  target_compile_definitions(Vx PUBLIC VxEvent_SendUnknown)
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
  set(SRCW32 Sources/Win32)
  target_sources(Vx PRIVATE ${SRCW32}/Window.c ${SRCW32}/Context.c ${SRCW32}/Lifecycle.c)
  target_link_libraries(Vx PRIVATE user32)
else()
  message(FATAL_ERROR "Vx only supports Win32 as of now...")
endif()

if(Vx_Testing)
  function(Vx_Test name)
      add_executable(${name} Tests/${name}.c)
      target_link_libraries(${name} PRIVATE Vx)
      add_test(NAME ${name} COMMAND ${name})
  endfunction()

  Vx_Test(Basic)
  Vx_Test(Clear)

  enable_testing()
endif()
