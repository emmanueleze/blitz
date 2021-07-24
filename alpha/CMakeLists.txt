
option(alpha_build_tests "Build all alpha's tests" OFF)


if (CMAKE_VERSION VERSION_LESS 3.0)
  project(alpha CXX C)
  set(PROJECT_VERSION ${BLITZ_VERSION})
else()
  cmake_policy(SET CMP0048 NEW)
  project(alpha VERSION ${BLITZ_VERSION} LANGUAGES CXX C )
endif()

cmake_minimum_required(VERSION 2.8.12)

if (POLICY CMP0063)
  cmake_policy(SET CMP0063 NEW)
endif (POLICY CMP0063)

# Require C++20 and disable extensions for all targets
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# These commands only run if this is the main project
if(CMAKE_PROJECT_NAME STREQUAL "alpha" OR CMAKE_PROJECT_NAME STREQUAL "blitz")

  # BUILD_SHARED_LIBS is a standard CMake variable, but we declare it here to
  # make it prominent in the GUI.
  option(BUILD_SHARED_LIBS "Build shared libraries (DLLs)." OFF)

else()

  mark_as_advanced(
    alpha_build_tests
    alpha_build_samples)

endif()


# Define helper functions and macros used by Blitz.
include(cmake/util.cmake)

config_compiler_and_linker()  # Defined in internal_utils.cmake.


# Where alpha's .h files can be found.
set(alpha_build_include_dirs
"${alpha_SOURCE_DIR}/include"
"${alpha_SOURCE_DIR}")
include_directories(${alpha_build_include_dirs})

#Find GTest
find_package(PkgConfig)
find_package(GTest REQUIRED)

#Find Boost
find_package(Boost 1.75.0 REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread -fsanitize=undefined -g -O3")

########################################################################

# Blitz libraries.  We build them using more strict warnings than what
# are used for other targets, to ensure that alpha can be compiled by a user
# aggressive about warnings.
cxx_library(alpha "${cxx_strict}" src/alpha.cc)
set_target_properties(alpha PROPERTIES VERSION ${BLITZ_VERSION} CMAKE_CXX_STANDARD 20)

if (DEFINED CMAKE_VERSION AND NOT "${CMAKE_VERSION}" VERSION_LESS "2.8.11")
  target_include_directories(alpha SYSTEM INTERFACE
    "$<BUILD_INTERFACE:${alpha_build_include_dirs}>"
    "$<BUILD_INTERFACE:${Boost_INCLUDE_DIRS}>"
    "$<BUILD_INTERFACE:${GTEST_INCLUDE_DIR}")
    target_link_libraries(alpha PUBLIC ${Boost_LIBRARIES} PUBLIC ${GTEST_LIBRARIES})
endif()



cxx_executable(alpha-main src alpha src/alpha-main.cc)

if(alpha_build_tests)

  enable_testing()
  
  cxx_test(alpha_controls_test alpha)
  cxx_test(alpha_base_test alpha)
  cxx_test(alpha-tests alpha)


endif()
