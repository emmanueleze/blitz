
if (CMAKE_VERSION VERSION_LESS 3.0)
project(samples CXX C)
set(PROJECT_VERSION ${BLITZ_VERSION})
else()
cmake_policy(SET CMP0048 NEW)
project(samples VERSION ${BLITZ_VERSION} LANGUAGES CXX C )
endif()

cmake_minimum_required(VERSION 2.8.12)

if (POLICY CMP0054)
cmake_policy(SET CMP0054 NEW)
endif (POLICY CMP0054)

# Require C++20 and disable extensions for all targets
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# if(CMAKE_BUILD_TYPE STREQUAL "Asan")  
#   target_compile_options(core PRIVATE -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer)
#   target_link_options(core PUBLIC -fsanitize=address)
# endif(CMAKE_BUILD_TYPE STREQUAL "Asan")

# if(CMAKE_BUILD_TYPE STREQUAL "Debug")
#   target_compile_options(core PRIVATE -g -O3 -fno-omit-frame-pointer)
#   target_link_options(core PUBLIC -g -O3)
# endif(CMAKE_BUILD_TYPE STREQUAL "Debug")


# if(CMAKE_BUILD_TYPE STREQUAL "Tsan")
#   target_compile_options(core PRIVATE -fsanitize=thread -fsanitize=undefined -fno-omit-frame-pointer)
#   target_link_options(core PUBLIC -fsanitize=thread)
# endif(CMAKE_BUILD_TYPE STREQUAL "Tsan")


set(SAMPLES_INCLUDE_DIR "/")
include_directories(${SAMPLES_INCLUDE_DIR})


if(BLITZ_BUILD_SAMPLES)
  cxx_executable(asio-client . blitz asio-client.cc)
  cxx_executable(asio-server . blitz asio-server.cc)
endif()