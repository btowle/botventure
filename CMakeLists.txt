cmake_minimum_required(VERSION 2.8.12)
project(Botventure)
set(Botventure_VERSION_MAJOR 0)
set(Botventure_VERSION_MINOR 1)

configure_file(
  "${PROJECT_SOURCE_DIR}/src/botventureconfig.h.in"
  "${PROJECT_SOURCE_DIR}/src/botventureconfig.h"
  )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_subdirectory(src)
