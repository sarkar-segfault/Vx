cmake_minimum_required(VERSION 3.10..4.2)

project(
  Vx
  LANGUAGES C
  VERSION 0.1.0
  DESCRIPTION "A windowing library for simpletons and wizards alike"
)

add_library(Vx Sources/Window.c Sources/Lifecycle.c)

set(VxWindow__DefaultWidth 800 CACHE STRING "The default width for all windows")
set(VxWindow__DefaultHeight 600 CACHE STRING "The default height for all windows")
set(VxWindow__DefaultTitle "VxWindow" CACHE STRING "The default title for all windows")

if(DEFINED VxWindow__DefaultWidth)
  target_compile_definitions(Vx PUBLIC VxWindow__DefaultWidth=${VxWindow__DefaultWidth})
endif()

if(DEFINED VxWindow__DefaultHeight)
  target_compile_definitions(Vx PUBLIC VxWindow__DefaultHeight=${VxWindow__DefaultHeight})
endif()

if(DEFINED VxWindow__DefaultTitle)
  target_compile_definitions(Vx PUBLIC VxWindow__DefaultTitle=${VxWindow_DefaultTitle})
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
  set(Vx__WindowClass "VxWindow" CACHE STRING "The name of the Win32 window class")
  target_compile_definitions(Vx PUBLIC Vx__WindowClass="${Vx__WindowClass}")
  target_link_libraries(Vx PRIVATE user32)
endif()

add_executable(test test.c)

target_link_libraries(test PRIVATE Vx)
