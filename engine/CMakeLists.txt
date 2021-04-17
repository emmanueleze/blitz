
option(engine_build_tests "Build all of engine's own tests." OFF)

option(engine_build_samples "Build engine's sample programs." OFF)


if (CMAKE_VERSION VERSION_LESS 3.0)
  project(engine LANGUAGES CXX C)
  set(PROJECT_VERSION ${BLITZ_VERSION})
else()
  cmake_policy(SET CMP0048 NEW)
  project(engine VERSION ${BLITZ_VERSION} LANGUAGES CXX C )
endif()

cmake_minimum_required(VERSION 2.8.12)

if (POLICY CMP0063)
  cmake_policy(SET CMP0063 NEW)
endif (POLICY CMP0063)

# Require C++17 and disable extensions for all targets
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define helper functions and macros used by Blitz.
include(cmake/util.cmake)

config_compiler_and_linker()  # Defined in internal_utils.cmake.


# Where engine's .h files can be found.
set(engine_build_include_dirs
"${engine_SOURCE_DIR}/include"
"${engine_SOURCE_DIR}/include/engine-core"
"${engine_SOURCE_DIR}/engine-cv")
include_directories(${engine_build_include_dirs})

#Find GTest
find_package(PkgConfig)
pkg_search_module(GTEST REQUIRED gtest_main)
#Find Gsl
find_package(PkgConfig)
pkg_search_module(gsl REQUIRED gsl gslcblas m)


cxx_library_with_type(engine STATIC "${cxx_default}" src/engine.cc)
set_target_properties(engine PROPERTIES VERSION ${BLITZ_VERSION} CMAKE_CXX_STANDARD 17)

if (DEFINED CMAKE_VERSION AND NOT "${CMAKE_VERSION}" VERSION_LESS "2.8.11")
  target_include_directories(engine SYSTEM INTERFACE
    "$<BUILD_INTERFACE:${engine_build_include_dirs}>"
    "$<BUILD_INTERFACE:${gsl_INCLUDEDIR}>")
    target_link_libraries(engine PUBLIC ${gsl_LIBRARIES})
endif()




cxx_executable(engine-main src engine src/engine-main.cc)


