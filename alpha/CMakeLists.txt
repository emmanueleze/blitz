



if (CMAKE_VERSION VERSION_LESS 3.0)
  project(alpha LANGUAGES CXX C)
  set(PROJECT_VERSION ${BLITZ_VERSION})
else()
  cmake_policy(SET CMP0048 NEW)
  project(alpha VERSION ${BLITZ_VERSION} LANGUAGES CXX C )
endif()

cmake_minimum_required(VERSION 2.8.12)

if (POLICY CMP0063)
  cmake_policy(SET CMP0063 NEW)
endif (POLICY CMP0063)

# Require C++17 and disable extensions for all targets
set(CMAKE_CXX_STANDARD 17)
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
"${alpha_SOURCE_DIR}/include/core"
"${alpha_SOURCE_DIR}/util")
include_directories(${alpha_build_include_dirs})

#Find GTest
find_package(PkgConfig)
pkg_search_module(GTEST REQUIRED gtest_main)
find_package(GTest REQUIRED)
#Find Boost
find_package(Boost 1.72 REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

########################################################################

# Blitz libraries.  We build them using more strict warnings than what
# are used for other targets, to ensure that alpha can be compiled by a user
# aggressive about warnings.
cxx_library_with_type(alpha STATIC "${cxx_default}" src/alpha.cc)
set_target_properties(alpha PROPERTIES VERSION ${BLITZ_VERSION} CMAKE_CXX_STANDARD 17)

if (DEFINED CMAKE_VERSION AND NOT "${CMAKE_VERSION}" VERSION_LESS "2.8.11")
  target_include_directories(alpha SYSTEM INTERFACE
    "$<BUILD_INTERFACE:${alpha_build_include_dirs}>"
    "$<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>")
    target_link_libraries(alpha PUBLIC ${Boost_LIBRARIES})
endif()



cxx_executable(alpha-main src alpha src/alpha-main.cc)

enable_testing()

add_executable(alpha_base_test test/alpha_base_test.cc)

target_link_libraries(alpha_base_test PUBLIC alpha PRIVATE GTest::GTest)
add_test(NAME AlphaBaseTest COMMAND alpha_base_test)


