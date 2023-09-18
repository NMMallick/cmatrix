cmake_minimum_required(VERSION 3.0)
project(cmatrix VERSION 1.0)

set(cmatrix_SOURCES src/core.c)
add_library(cmatrix SHARED ${cmatrix_SOURCES})

target_link_libraries(cmatrix m)
target_include_directories(cmatrix PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

# Tests
set(cmatrix_TESTS tests/main.c)
add_executable(tests ${cmatrix_TESTS})

target_link_libraries(tests PUBLIC cmatrix)
target_include_directories(tests PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

