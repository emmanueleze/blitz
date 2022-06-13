
# if (CMAKE_VERSION VERSION_LESS 3.0)
# project(blitz CXX C)
# set(PROJECT_VERSION ${BLITZ_VERSION})
# else()
# cmake_policy(SET CMP0048 NEW)
# project(blitz VERSION ${BLITZ_VERSION} LANGUAGES CXX C )
# endif()

# cmake_minimum_required(VERSION 2.8.12)

# if (POLICY CMP0054)
# cmake_policy(SET CMP0054 NEW)
# endif (POLICY CMP0054)

# # Require C++17 and disable extensions for all targets
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)

# find_package(GTest REQUIRED)

# add_executable(blitz_core_test blitz_core_test.cc)
# target_link_libraries(blitz_core_test PRIVATE gtest-main PUBLIC core)
# add_test(NAME BLITZ_TEST COMMAND blitz_core_test)

cmake_minimum_required(VERSION 3.15)

project(
  ${CMAKE_PROJECT_NAME}
  LANGUAGES CXX C
)


file(GLOB TEST_SOURCES "./*.cc")

foreach(SOURCE ${TEST_SOURCES}) 
  get_filename_component(FILE_NAME_WE ${SOURCE} NAME_WE)
  get_filename_component(FILE_NAME ${SOURCE} NAME)

  add_executable(${FILE_NAME_WE}_test ${FILE_NAME})

  target_compile_features(${FILE_NAME_WE}_test PUBLIC cxx_std_17)

  if (${CMAKE_PROJECT_NAME}_ENABLE_CODE_COVERAGE)
    target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -O0 -g -fprofile-arcs -ftest-coverage)
    target_link_options(${CMAKE_PROJECT_NAME} PUBLIC -fprofile-arcs -ftest-coverage)
    message("Code coverage is enabled and provided with GCC.")
  endif()

  find_package(GTest REQUIRED)

  target_link_libraries(
    ${FILE_NAME_WE}_test
    PUBLIC
      GTest::GTest
      GTest::Main
      ${GOOGLE_MOCK_LIBRARIES}
      PUBLIC core
  )

  add_test( NAME ${FILE_NAME_WE}_TEST COMMAND ${FILE_NAME_WE}_test )

endforeach()

