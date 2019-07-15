#----------------------------------------------------------------------
# makeshape 
#----------------------------------------------------------------------
cmake_minimum_required(VERSION 3.1)
project("makeshape")
enable_testing()

#----------------------------------------------------------------------
# find cmake files here
#----------------------------------------------------------------------
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#----------------------------------------------------------------------
# libigl flags
#----------------------------------------------------------------------
option(LIBIGL_WITH_OPENGL            "Use OpenGL"         ON)
option(LIBIGL_WITH_OPENGL_GLFW       "Use GLFW"           ON)
option(LIBIGL_WITH_OPENGL_GLFW_IMGUI "Use ImGUI"          ON)
option(LIBIGL_WITH_PNG               "Use PNG"            ON)

#----------------------------------------------------------------------
# find libIGL
#----------------------------------------------------------------------
find_package(LIBIGL REQUIRED QUIET)


#----------------------------------------------------------------------
# download and build googletest
#----------------------------------------------------------------------
# Download and unpack googletest at configure time
configure_file(cmake/CMakeLists.txt.googletest googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

#----------------------------------------------------------------------
# download and build cxxopts
#----------------------------------------------------------------------
# Download and unpack cxxopts at configure time
configure_file(cmake/CMakeLists.txt.cxxopts cxxopts-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/cxxopts-download )
if(result)
  message(FATAL_ERROR "CMake step for cxxopts failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/cxxopts-download )
if(result)
  message(FATAL_ERROR "Build step for cxxopts failed: ${result}")
endif()

# Add cxxopts directly to our build.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/cxxopts-src
                 ${CMAKE_CURRENT_BINARY_DIR}/cxxopts-build
                 EXCLUDE_FROM_ALL)

#----------------------------------------------------------------------
# directories for bin, lib, tests, and data
#----------------------------------------------------------------------
# bin dir
set( bin_dir "${CMAKE_BINARY_DIR}/bin" CACHE PATH "Path to executable" )
file(MAKE_DIRECTORY ${bin_dir})

# inc dir
set( inc_dir "${CMAKE_BINARY_DIR}/inc" CACHE PATH "Path to includes" )
file(MAKE_DIRECTORY ${inc_dir})

# lib dir
set( lib_dir "${CMAKE_BINARY_DIR}/lib" CACHE PATH "Path to libraries" )
file(MAKE_DIRECTORY ${lib_dir})

# test dir
set( test_dir "${CMAKE_BINARY_DIR}/tests" CACHE PATH "Path to unittests" )
file(MAKE_DIRECTORY ${test_dir})

# data dir
set( data_dir "${CMAKE_BINARY_DIR}/data" CACHE PATH "Path to data" )
file(MAKE_DIRECTORY ${data_dir})

#----------------------------------------------------------------------
# copy data files in builds/data/
#----------------------------------------------------------------------
file(GLOB data_files "${CMAKE_SOURCE_DIR}/data/*.*")
file(COPY ${data_files} DESTINATION ${data_dir}) 

#----------------------------------------------------------------------
# copy scripts into build
#----------------------------------------------------------------------
if (WIN32)
    file(GLOB scripts "${CMAKE_SOURCE_DIR}/scripts/*.bat")
elseif(UNIX)
    file(GLOB scripts "${CMAKE_SOURCE_DIR}/scripts/*.sh")
endif (WIN32)
file(COPY ${scripts} DESTINATION ${CMAKE_BINARY_DIR}) 

#----------------------------------------------------------------------
add_subdirectory(src)
add_subdirectory(examples)
