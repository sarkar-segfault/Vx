cmake_minimum_required(VERSION 3.10..4.2)

project(
  Vx
  LANGUAGES C
  VERSION 0.1.0
  DESCRIPTION "A pure C library for creating and controlling windows"
)

add_library(Vx Sources/Window.c Sources/Lifecycle.c)

if(WIN32)
  set(Vx__WindowClass "VxWindow" CACHE STRING "Set the name of the window class (win32)")
  target_compile_definitions(Vx PUBLIC Vx__WindowClass="${Vx__WindowClass}")
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

if(WIN32)
  target_link_libraries(Vx PRIVATE user32 )
endif()

add_executable(test test.c)

target_link_libraries(test PRIVATE Vx)
