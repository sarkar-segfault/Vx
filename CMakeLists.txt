cmake_minimum_required(VERSION 3.10..4.2)

project(
  Vx
  LANGUAGES C
  VERSION 0.1.0
  DESCRIPTION "A pure C library for creating and controlling windows"
)

add_library(Vx)

if(BUILD_SHARED_LIBS)
  target_compile_definitions(Vx PRIVATE Vx__Shared)
endif()

target_compile_definitions(Vx PRIVATE Vx__Build)

target_compile_definitions(
  Vx PUBLIC
  VxVersion="${PROJECT_VERSION}"
  VxVersion_Major="${PROJECT_VERSION_MAJOR}"
  VxVersion_Minor="${PROJECT_VERSION_MINOR}"
  VxVersion_Micro="${PROJECT_VERSION_PATCH}"
)

target_include_directories(Vx PUBLIC Headers)

target_compile_features(Vx PUBLIC c_std_99)

if(WIN32)
  target_link_libraries(Vx PRIVATE user32)
endif()
