
if (CMAKE_VERSION VERSION_LESS 3.0)
  project(blitz LANGUAGES CXX C)
  set(PROJECT_VERSION ${BLITZ_VERSION})
else()
  cmake_policy(SET CMP0048 NEW)
  project(blitz VERSION ${BLITZ_VERSION} LANGUAGES CXX C )
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

# Create the CMake package file descriptors.
if (INSTALL_BLITZ)
  include(CMakePackageConfigHelpers)
  set(cmake_package_name Blitz)
  set(targets_export_name ${cmake_package_name}Targets CACHE INTERNAL "")
  set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated" CACHE INTERNAL "")
  set(cmake_files_install_dir "${CMAKE_INSTALL_LIBDIR}/cmake/${cmake_package_name}")
  set(version_file "${generated_dir}/${cmake_package_name}ConfigVersion.cmake")
  write_basic_package_version_file(${version_file} VERSION ${BLITZ_VERSION} COMPATIBILITY AnyNewerVersion)
  install(EXPORT ${targets_export_name}
    NAMESPACE ${cmake_package_name}::
    DESTINATION ${cmake_files_install_dir})
  set(config_file "${generated_dir}/${cmake_package_name}Config.cmake")
  configure_package_config_file("${blitz_SOURCE_DIR}/cmake/Config.cmake.in"
    "${config_file}" INSTALL_DESTINATION ${cmake_files_install_dir})
  install(FILES ${version_file} ${config_file}
    DESTINATION ${cmake_files_install_dir})
endif()

# Where Blitz's .h files can be found.
set(blitz_build_include_dirs
"${blitz_SOURCE_DIR}/include"
"${blitz_SOURCE_DIR}/include/core"
"${blitz_SOURCE_DIR}/util")
include_directories(${blitz_build_include_dirs})

#Find GTest
find_package(PkgConfig)
pkg_search_module(GTEST REQUIRED gtest_main)
find_package(PkgConfig)
pkg_search_module(gsl REQUIRED gsl gslcblas m)


########################################################################

# Blitz libraries.  We build them using more strict warnings than what
# are used for other targets, to ensure that blitz can be compiled by a user
# aggressive about warnings.
cxx_library_with_type(blitz-alpha STATIC "${cxx_default}" src/alpha.cc)
set_target_properties(blitz-alpha PROPERTIES VERSION ${BLITZ_VERSION} CMAKE_CXX_STANDARD 17)

if (DEFINED CMAKE_VERSION AND NOT "${CMAKE_VERSION}" VERSION_LESS "2.8.11")
  target_include_directories(blitz-alpha SYSTEM INTERFACE
    "$<BUILD_INTERFACE:${blitz_build_include_dirs}>"
    "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>")
endif()

cxx_library_with_type(blitz-engine STATIC "${cxx_default}" src/engine.cc)
set_target_properties(blitz-engine PROPERTIES VERSION ${BLITZ_VERSION} CMAKE_CXX_STANDARD 17)

if (DEFINED CMAKE_VERSION AND NOT "${CMAKE_VERSION}" VERSION_LESS "2.8.11")
  target_include_directories(blitz-engine SYSTEM INTERFACE
    "$<BUILD_INTERFACE:${blitz_build_include_dirs}>"
    "$<BUILD_INTERFACE:${gsl_INCLUDEDIR}>"
    "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>")
endif()

target_link_libraries(blitz-alpha PUBLIC ${Boost_LIBRARIES})
target_link_libraries(blitz-engine PUBLIC ${gsl_LIBRARIES})

cxx_executable(alpha src blitz-alpha src/main.cc)
cxx_executable(engine src blitz-engine src/engine.cc)


