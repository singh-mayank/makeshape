#----------------------------------------------------------------------
# 
#----------------------------------------------------------------------
cmake_minimum_required(VERSION 3.1)
project("makeshape")
enable_testing()

#----------------------------------------------------------------------
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
#----------------------------------------------------------------------

#----------------------------------------------------------------------
# libigl
#----------------------------------------------------------------------
option(LIBIGL_WITH_OPENGL            "Use OpenGL"         ON)
option(LIBIGL_WITH_OPENGL_GLFW       "Use GLFW"           ON)
option(LIBIGL_WITH_OPENGL_GLFW_IMGUI "Use ImGUI"          ON)
option(LIBIGL_WITH_PNG               "Use PNG"            ON)

#----------------------------------------------------------------------

find_package(LIBIGL REQUIRED QUIET)

#----------------------------------------------------------------------
# make directories
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

# test dir
set( data_dir "${CMAKE_BINARY_DIR}/data" CACHE PATH "Path to data" )
file(MAKE_DIRECTORY ${data_dir})

#----------------------------------------------------------------------
add_subdirectory(googletest)
add_subdirectory(src)
