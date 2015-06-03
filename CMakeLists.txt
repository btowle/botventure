cmake_minimum_required(VERSION 2.8.12)
project(Botventure)
set(Botventure_VERSION_MAJOR 0)
set(Botventure_VERSION_MINOR 1)

configure_file(
  "${PROJECT_SOURCE_DIR}/src/botventureconfig.h.in"
  "${PROJECT_SOURCE_DIR}/src/botventureconfig.h"
  )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/cpp")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/cpp")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/cpp")

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${CMAKE_BINARY_DIR}/src/network/messages)

add_subdirectory(swig)
add_subdirectory(src)
file(COPY data/maps DESTINATION "${CMAKE_BINARY_DIR}/data")
