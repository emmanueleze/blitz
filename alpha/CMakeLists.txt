
if (CMAKE_VERSION VERSION_LESS 3.0)
  project(alpha CXX C)
  set(PROJECT_VERSION ${BLITZ_VERSION})
else()
  cmake_policy(SET CMP0048 NEW)
  project(alpha VERSION ${BLITZ_VERSION} LANGUAGES CXX C )
endif()

cmake_minimum_required(VERSION 2.8.12)

if (POLICY CMP0054)
  cmake_policy(SET CMP0054 NEW)
endif (POLICY CMP0054)

# Require C++20 and disable extensions for all targets
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Where alpha's .h files can be found.
set(ALPHA_INCLUDE_DIR
"${alpha_SOURCE_DIR}/include"
"${alpha_SOURCE_DIR}")
include_directories(${ALPHA_INCLUDE_DIR})


cxx_library(alpha "${cxx_strict}" src/alpha.cc src/core.cc)
set_target_properties(alpha PROPERTIES VERSION ${BLITZ_VERSION} )

if(CMAKE_BUILD_TYPE STREQUAL "Asan")  
  target_compile_options(alpha PRIVATE -fsanitize=address)
  target_link_options(alpha PRIVATE -fsanitize=address)
endif(CMAKE_BUILD_TYPE STREQUAL "Asan")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(alpha PRIVATE -g -O3)
  target_link_options(alpha PRIVATE -g -O3)
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")


if(CMAKE_BUILD_TYPE STREQUAL "Tsan")
  target_compile_options(alpha PRIVATE -fsanitize=thread)
  target_link_options(alpha PRIVATE -fsanitize=thread)
endif(CMAKE_BUILD_TYPE STREQUAL "Tsan")


if (DEFINED CMAKE_VERSION AND NOT "${CMAKE_VERSION}" VERSION_LESS "2.8.11")
  target_include_directories(alpha SYSTEM INTERFACE
    "$<BUILD_INTERFACE:${ALPHA_INCLUDE_DIR}>"
    "$<BUILD_INTERFACE:${GTEST_INCLUDE_DIRS}"
    "$<BUILD_INTERFACE:${BOOST_LIBRARIES}")

  target_link_libraries(alpha PUBLIC ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})

endif()

cxx_executable(alpha-main src alpha src/alpha-main.cc)























