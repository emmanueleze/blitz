
if (CMAKE_VERSION VERSION_LESS 3.14)
  project(blitz CXX C)
  set(PROJECT_VERSION ${BLITZ_VERSION})
else()
  cmake_policy(SET CMP0048 NEW)
  project(blitz VERSION ${BLITZ_VERSION} LANGUAGES CXX C )
endif()

if (POLICY CMP0054)
  cmake_policy(SET CMP0054 NEW)
endif (POLICY CMP0054)

# Require C++20 and disable extensions for all targets
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)


# Where blitz's .h files can be found.
set(BLITZ_INCLUDE_DIR
"${blitz_SOURCE_DIR}/include"
"${blitz_SOURCE_DIR}")
include_directories(${BLITZ_INCLUDE_DIR})


cxx_library(core "${cxx_strict}" src/core.cc)
cxx_library(engine "${cxx_strict}" src/engine.cc)

set_target_properties(core PROPERTIES VERSION ${BLITZ_VERSION} )

if(CMAKE_BUILD_TYPE STREQUAL "Asan")  
  target_compile_options(core PRIVATE -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer)
  target_link_options(core PUBLIC -fsanitize=address)
endif(CMAKE_BUILD_TYPE STREQUAL "Asan")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(core PRIVATE -g -O3 -fno-omit-frame-pointer)
  target_link_options(core PUBLIC -g -O3)
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")


if(CMAKE_BUILD_TYPE STREQUAL "Tsan")
  target_compile_options(core PRIVATE -fsanitize=thread -fsanitize=undefined -fno-omit-frame-pointer)
  target_link_options(core PUBLIC -fsanitize=thread)
endif(CMAKE_BUILD_TYPE STREQUAL "Tsan")


if (DEFINED CMAKE_VERSION AND NOT "${CMAKE_VERSION}" VERSION_LESS "2.8.11")
  target_include_directories(core SYSTEM INTERFACE
    "$<BUILD_INTERFACE:${BLITZ_INCLUDE_DIR}>"
    "$<BUILD_INTERFACE:${GTEST_INCLUDE_DIRS}"
    "$<BUILD_INTERFACE:${BOOST_LIBRARIES}")

  target_link_libraries(core PUBLIC ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})

endif()
























