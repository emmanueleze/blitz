
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
set(CMAKE_CXX_EXTENSIONS OFF)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lGL -lX11 -lpthread -lXrandr -lXi -ldl -g -O3")

# Where blitz's .h files can be found.
set(BLITZ_INCLUDE_DIR
"${blitz_SOURCE_DIR}/include"
"${blitz_SOURCE_DIR}")
include_directories(${BLITZ_INCLUDE_DIR})


cxx_library(vkgp "${cxx_strict}" src/vkgp.cc)
cxx_library(core "${cxx_strict}" src/core.cc)


# cxx_library(engine "${cxx_strict}" src/engine.cc)
# cxx_library(e64gl "${cxx_strict}" src/e64gl.cc)


# add_library(glad src/glad.c)
# target_include_directories(glad PUBLIC "${blitz_SOURCE_DIR}/include")
# target_include_directories(e64gl PUBLIC "${BLITZ_INCLUDE_DIR}")
#target_link_libraries(e64gl PUBLIC glfw3 PUBLIC glad)


set_target_properties(core PROPERTIES VERSION ${BLITZ_VERSION} )
set_target_properties(vkgp PROPERTIES VERSION ${BLITZ_VERSION} )

if(CMAKE_BUILD_TYPE STREQUAL "Asan")  
  target_compile_options(core PRIVATE -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer)
  target_link_options(core PUBLIC -fsanitize=address)
  target_compile_options(vkgp PRIVATE -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer)
  target_link_options(vkgp PUBLIC -fsanitize=address)
endif(CMAKE_BUILD_TYPE STREQUAL "Asan")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(core PRIVATE -g -O3 -fno-omit-frame-pointer)
  target_link_options(core PUBLIC -g -O3)
  target_compile_options(vkgp PRIVATE -g -O3 -fno-omit-frame-pointer)
  target_link_options(vkgp PUBLIC -g -O3)
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")


if(CMAKE_BUILD_TYPE STREQUAL "Tsan")
  target_compile_options(core PRIVATE -fsanitize=thread -fsanitize=undefined -fno-omit-frame-pointer)
  target_link_options(core PUBLIC -fsanitize=thread)
  target_compile_options(vkgp PRIVATE -fsanitize=thread -fsanitize=undefined -fno-omit-frame-pointer)
  target_link_options(vkgp PUBLIC -fsanitize=thread)
endif(CMAKE_BUILD_TYPE STREQUAL "Tsan")


if (DEFINED CMAKE_VERSION AND NOT "${CMAKE_VERSION}" VERSION_LESS "2.8.11")
  target_include_directories(core SYSTEM INTERFACE
    "$<BUILD_INTERFACE:${BLITZ_INCLUDE_DIR}>"
    "$<BUILD_INTERFACE:${GTEST_INCLUDE_DIRS}"
    "$<BUILD_INTERFACE:${BOOST_LIBRARIES}")

    target_include_directories(vkgp SYSTEM INTERFACE
    "$<BUILD_INTERFACE:${BLITZ_INCLUDE_DIR}>"
    )

  target_link_libraries(core PUBLIC ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})
  target_link_libraries(vkgp PUBLIC glfw3 PUBLIC ${Vulkan_LIBRARY})
  

endif()
























