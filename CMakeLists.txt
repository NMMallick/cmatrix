cmake_minimum_required(VERSION 3.0)
project(cmatrix VERSION 1.0)

# Tests
set(cmatrix_SOURCES src/core.c)
set(cmatrix_TESTS tests/main.c)
add_executable(tests ${cmatrix_TESTS} ${cmatrix_SOURCES})

target_include_directories(tests PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

