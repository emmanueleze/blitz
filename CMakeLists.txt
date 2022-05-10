

cmake_minimum_required(VERSION 2.8.12)

if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

project(blitz)
set(BLITZ_VERSION 1.0.1)



find_package(PkgConfig)
find_package( Boost 1.78.0 COMPONENTS system regex thread REQUIRED )
find_package(GTest REQUIRED)
find_package( OpenCV REQUIRED core)

# Include helper functions and macros used by blitz.
include(cmake/util.cmake)

config_compiler_and_linker()  # Defined in internal_utils.cmake.

enable_testing()


option(BLITZ_BUILD_TESTS "Build all alpha's tests" ON)
option(BLITZ_BUILD_SAMPLES "Build alpha's sample programs" ON)


if (CMAKE_VERSION VERSION_GREATER "3.0.2")
  if(NOT CYGWIN AND NOT MSYS AND NOT ${CMAKE_SYSTEM_NAME} STREQUAL QNX)
    set(CMAKE_CXX_EXTENSIONS OFF)
  endif()
endif()



# These commands only run if this is the main project
if(CMAKE_PROJECT_NAME STREQUAL "alpha")

  # BUILD_SHARED_LIBS is a standard CMake variable, but we declare it here to
  # make it prominent in the GUI.
  option(BUILD_SHARED_LIBS "Build shared libraries (DLLs)." OFF)

else()
  mark_as_advanced(
    BLITZ_BUILD_TESTS
    BLITZ_BUILD_SAMPLES)

endif(CMAKE_PROJECT_NAME STREQUAL "alpha")



include(CMakeDependentOption)
include(GNUInstallDirs)

add_subdirectory(blitz)

if(BLITZ_BUILD_TESTS)
  add_subdirectory(test)
endif()


if(BLITZ_BUILD_SAMPLES)
  add_subdirectory(samples)
endif()
