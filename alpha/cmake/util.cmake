# Defines functions and macros useful for building BlitzAlpha

if (POLICY CMP0054)
  cmake_policy(SET CMP0054 NEW)
endif (POLICY CMP0054)


macro(config_compiler_and_linker)
  # BlitzAlpha: pthreads on MinGW is not supported, even if available
  # instead, we use windows threading primitives
  unset(BLITZ_ALPHA_HAS_PTHREAD)
  if (NOT blitz-alpha_disable_pthreads AND NOT MINGW)
    # Defines CMAKE_USE_PTHREADS_INIT and CMAKE_THREAD_LIBS_INIT.
    find_package(Threads)
    if (CMAKE_USE_PTHREADS_INIT)
      set(BLITZ_ALPHA_HAS_PTHREAD ON)
    endif()
  endif()

  

  if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(cxx_base_flags "-Wall -Wshadow -Wconversion")
    set(cxx_exception_flags "-fexceptions")
    set(cxx_no_exception_flags "-fno-exceptions")
    set(cxx_strict_flags "-W -Wpointer-arith -Wreturn-type -Wcast-qual -Wwrite-strings -Wswitch -Wpedantic -Wcast-align -Wchar-subscripts -Winline -Wredundant-decls")
    set(cxx_no_rtti_flags "-fno-rtti")
  elseif (CMAKE_COMPILER_IS_GNUCXX)
    set(cxx_base_flags "-Wall -Wshadow -Wpedantic ")
    if(NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7.0.0)
      set(cxx_base_flags "${cxx_base_flags} -Wno-error=dangling-else")
    endif()
    set(cxx_exception_flags "-fexceptions")
    set(cxx_no_exception_flags "-fno-exceptions")
    # Until version 4.3.2, GCC doesn't define a macro to indicate
    # whether RTTI is enabled.  Therefore we define BLITZ_ALPHA_HAS_RTTI
    # explicitly.
    set(cxx_no_rtti_flags "-fno-rtti -DBLITZ_ALPHA_HAS_RTTI=0")
    #removed -Wno-unused-parameter  -Wno-missing-field-initializers
    set(cxx_strict_flags
      "-Wextra -Wpedantic")
  endif()

  # The pthreads library is available and allowed?
  if (DEFINED BLITZ_ALPHA_HAS_PTHREAD)
    set(BLITZ_ALPHA_HAS_PTHREAD_MACRO "-DBLITZ_ALPHA_HAS_PTHREAD=1")
  else()
    set(BLITZ_ALPHA_HAS_PTHREAD_MACRO "-DBLITZ_ALPHA_HAS_PTHREAD=0")
  endif()
  set(cxx_base_flags "${cxx_base_flags} ${BLITZ_ALPHA_HAS_PTHREAD_MACRO}")

  # For building BlitzAlpha's own tests and samples.
  set(cxx_exception "${cxx_base_flags} ${cxx_exception_flags}")
  set(cxx_no_exception
    "${CMAKE_CXX_FLAGS} ${cxx_base_flags} ${cxx_no_exception_flags}")
  set(cxx_default "${cxx_exception}")
  set(cxx_no_rtti "${cxx_default} ${cxx_no_rtti_flags}")

  # For building the BlitzAlpha libraries.
  #removed ${cxx_strict_flags}
  set(cxx_strict "${cxx_default} ")
endmacro()

# Defines the blitz-alpha & blitz-alpha_main libraries.  User tests should link
# with one of them.
function(cxx_library_with_type name type cxx_flags)
  # type can be either STATIC or SHARED to deblitz-alpha a static or shared library.
  # ARGN refers to additional arguments after 'cxx_flags'.
  add_library(${name} ${type} ${ARGN})
  set_target_properties(${name}
    PROPERTIES
    COMPILE_FLAGS "${cxx_flags}")
  # Generate debug library name with a postfix.
  set_target_properties(${name}
    PROPERTIES
    DEBUG_POSTFIX "d")
  # Set the output directory for build artifacts
  set_target_properties(${name}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
  # make PDBs match library name
  get_target_property(pdb_debug_postfix ${name} DEBUG_POSTFIX)
  set_target_properties(${name}
    PROPERTIES
    PDB_NAME "${name}"
    PDB_NAME_DEBUG "${name}${pdb_debug_postfix}"
    COMPILE_PDB_NAME "${name}"
    COMPILE_PDB_NAME_DEBUG "${name}${pdb_debug_postfix}")

  if (DEFINED BLITZ_ALPHA_HAS_PTHREAD)
    if ("${CMAKE_VERSION}" VERSION_LESS "3.1.0")
      set(threads_spec ${CMAKE_THREAD_LIBS_INIT})
    else()
      set(threads_spec Threads::Threads)
    endif()
    target_link_libraries(${name} PUBLIC ${threads_spec})
  endif()

  if (NOT "${CMAKE_VERSION}" VERSION_LESS "3.8")
    target_compile_features(${name} PUBLIC cxx_std_11)
  endif()
endfunction()

########################################################################
#
# Helper functions for creating build targets.

function(cxx_shared_library name cxx_flags)
  cxx_library_with_type(${name} SHARED "${cxx_flags}" ${ARGN})
endfunction()

function(cxx_library name cxx_flags)
  cxx_library_with_type(${name} "" "${cxx_flags}" ${ARGN})
endfunction()

# cxx_executable_with_flags(name cxx_flags libs srcs...)
#
# creates a named C++ executable that depends on the given libraries and
# is built from the given source files with the given compiler flags.
function(cxx_executable_with_flags name cxx_flags libs)
  add_executable(${name} ${ARGN})
  if (MSVC)
    # BigObj required for tests.
    set(cxx_flags "${cxx_flags} -bigobj")
  endif()
  if (cxx_flags)
    set_target_properties(${name}
      PROPERTIES
      COMPILE_FLAGS "${cxx_flags}"
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
  endif()
  
  # To support mixing linking in static and dynamic libraries, link each
  # library in with an extra call to target_link_libraries.
  foreach (lib "${libs}")
    target_link_libraries(${name} ${lib})
  endforeach()
endfunction()

# cxx_executable(name dir lib srcs...)
#
# creates a named target that depends on the given libs and is built
# from the given source files.  dir/name.cc is implicitly included in
# the source file list.
function(cxx_executable name dir libs)
  cxx_executable_with_flags(
    ${name} "${cxx_default}" "${libs}" "${dir}/${name}.cc" ${ARGN})
endfunction()

# cxx_test_with_flags(name cxx_flags libs srcs...)
#
# creates a named C++ test that depends on the given libs and is built
# from the given source files with the given compiler flags.
function(cxx_test_with_flags name cxx_flags libs)
  cxx_executable_with_flags(${name} "${cxx_flags}" "${libs}" ${ARGN})
    add_test(NAME ${name} COMMAND "$<TARGET_FILE:${name}>")
endfunction()

# cxx_test(name libs srcs...)
#
# creates a named test target that depends on the given libs and is
# built from the given source files.  Unlike cxx_test_with_flags,
# test/name.cc is already implicitly included in the source file list.
function(cxx_test name libs)
  cxx_test_with_flags("${name}" "${cxx_default}" "${libs}"
    "test/${name}.cc" ${ARGN})
endfunction()
