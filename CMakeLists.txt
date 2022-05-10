cmake_minimum_required(VERSION 3.14)

if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

project(blitz)
set(BLITZ_VERSION 1.1.0)

find_package(PkgConfig)
find_package( Boost 1.78.0 COMPONENTS system regex thread REQUIRED )
find_package(GTest REQUIRED)
find_package( OpenCV REQUIRED core)

# Include helper functions and macros used by blitz.
include(cmake/util.cmake)

config_compiler_and_linker()  # Defined in utils.cmake.

option(BLITZ_BUILD_TESTS "Build all alpha's tests" OFF)
option(BLITZ_BUILD_SAMPLES "Build alpha's sample programs" OFF)

mark_as_advanced(
  BLITZ_BUILD_TESTS
  BLITZ_BUILD_SAMPLES)

include(CMakeDependentOption)
include(GNUInstallDirs)

add_subdirectory(blitz)

if(BLITZ_BUILD_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()
