
option(engine_build_tests "Build all of engine's own tests." OFF)

option(engine_build_samples "Build engine's sample programs." OFF)


if (CMAKE_VERSION VERSION_LESS 3.0)
  project(engine-8.0 CXX C)
  set(PROJECT_VERSION ${BLITZ_VERSION})
else()
  cmake_policy(SET CMP0048 NEW)
  project(engine-8.0 VERSION ${BLITZ_VERSION} LANGUAGES CXX C )
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
"${engine-8.0_SOURCE_DIR}/include"
"${engine-8.0_SOURCE_DIR}")
include_directories(${engine_build_include_dirs})

#Find GTest
find_package(PkgConfig)
pkg_search_module(GTEST REQUIRED gtest_main)
#Find Gsl
pkg_search_module(gsl REQUIRED gsl gslcblas m)
#FInd OpenCV
find_package( OpenCV REQUIRED )

cxx_library_with_type(engine-8.0 STATIC "${cxx_strict}" src/engine.cc)
set_target_properties(engine-8.0 PROPERTIES VERSION ${BLITZ_VERSION})

if (DEFINED CMAKE_VERSION AND NOT "${CMAKE_VERSION}" VERSION_LESS "2.8.11")
  target_include_directories(engine-8.0 SYSTEM INTERFACE
    "$<BUILD_INTERFACE:${engine-8.0_build_include_dirs}>"
    "$<BUILD_INTERFACE:${gsl_INCLUDEDIR}>"
    "$<BUILD_INTERFACE:${OpenCV_INCLUDE_DIRS}")
    target_link_libraries(engine-8.0 PUBLIC ${gsl_LIBRARIES} PUBLIC ${OpenCV_LIBS})
endif()




cxx_executable(engine-main src engine src/engine-main.cc)


