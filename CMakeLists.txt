cmake_minimum_required(VERSION 3.10..4.2)

project(
  Vx
  LANGUAGES C
  VERSION 0.1.0
  DESCRIPTION "A pure C library for creating and controlling windows"
)

add_library(Vx)

target_compile_definitions(
  Vx PUBLIC
  VX_VERSION="${PROJECT_VERSION}"
  VX_VERSION_MAJOR="${PROJECT_VERSION_MAJOR}"
  VX_VERSION_MINOR="${PROJECT_VERSION_MINOR}"
  VX_VERSION_MICRO="${PROJECT_VERSION_PATCH}"
)

target_include_directories(Vx PUBLIC Headers)

target_compile_features(Vx PUBLIC c_std_99)

if(WIN32)
  target_link_libraries(Vx PRIVATE user32)
endif()
