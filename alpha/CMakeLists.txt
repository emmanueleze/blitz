
option(alpha_build_tests "Build all alpha's tests" ON)
option(alpha_build_samples "Build alpha's sample programs" OFF)


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

find_package( Boost 1.78.0 COMPONENTS system regex thread REQUIRED )

cxx_library(alpha "${cxx_strict}" src/alpha.cc src/core.cc)
set_target_properties(alpha PROPERTIES VERSION ${BLITZ_VERSION} )

if(CMAKE_BUILD_TYPE STREQUAL "Asan")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=undefined -g -O3 -lsqlite3")
endif(CMAKE_BUILD_TYPE STREQUAL "Asan")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O3 -lsqlite3")
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")


if(CMAKE_BUILD_TYPE STREQUAL "Tsan")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread -fsanitize=undefined -lsqlite3 -g -O3")
endif(CMAKE_BUILD_TYPE STREQUAL "Tsan")


if (DEFINED CMAKE_VERSION AND NOT "${CMAKE_VERSION}" VERSION_LESS "2.8.11")
  target_include_directories(alpha SYSTEM INTERFACE
    "$<BUILD_INTERFACE:${alpha_build_include_dirs}>"
    "$<BUILD_INTERFACE:${GTEST_INCLUDE_DIRS}"
    "$<BUILD_INTERFACE:${BOOST_LIBRARIES}")

  target_link_libraries(alpha PUBLIC ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})

endif()

cxx_executable(alpha-main src alpha src/alpha-main.cc)

if(alpha_build_tests)
  enable_testing()
  
  cxx_test(alpha-tests alpha)
  cxx_test(alpha_controls_test alpha)


endif()

if(alpha_build_samples)
  cxx_executable(tick samples alpha samples/tick.cc)
endif()

#----------------------------------------------------------------------
#------------ ATX_CONFIG-----------------------------------------------

set(atx_build_include_dirs
  "${alpha_SOURCE_DIR}/at"
)
include_directories(atx_build_include_dirs)

cxx_library(atx "${cxx_strict}" src/atx.cc)
set_target_properties(atx PROPERTIES VERSION ${BLITZ_VERSION})

if (DEFINED CMAKE_VERSION AND NOT "${CMAKE_VERSION}" VERSION_LESS "2.8.11")
  
  target_include_directories(atx SYSTEM INTERFACE
    "$<BUILD_INTERFACE:${atx_build_include_dirs}>")

  #target_link_libraries(atx PUBLIC ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})

endif()

cxx_executable(atx-main src atx src/atx-main.cc)

#set(Qt6Core_DIR "/opt/Qt/6.2.2/gcc_64/lib/cmake/Qt6Core")
#set(Qt6_DIR "/opt/Qt/6.2.2/gcc_64/lib/cmake/Qt6")
#set(QT_QMAKE_EXECUTABLE "/opt/Qt/6.2.2/gcc_64/bin/qmake")






















