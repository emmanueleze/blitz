
if (CMAKE_VERSION VERSION_LESS 3.0)
project(tests CXX C)
set(PROJECT_VERSION ${BLITZ_VERSION})
else()
cmake_policy(SET CMP0048 NEW)
project(tests VERSION ${BLITZ_VERSION} LANGUAGES CXX C )
endif()

cmake_minimum_required(VERSION 2.8.12)

if (POLICY CMP0054)
cmake_policy(SET CMP0054 NEW)
endif (POLICY CMP0054)

# Require C++20 and disable extensions for all targets
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(GTest COMPONENTS gtest-main)


if(BLITZ_BUILD_TESTS)
  add_executable(blitz_test blitz_test.cc)
  target_link_libraries(blitz_test PRIVATE gtest-main PUBLIC core)
  add_test(NAME BLITZ_TEST COMMAND blitz_test)
endif()


