#----------------------------------------------------------------------
# makeshape | common
#----------------------------------------------------------------------
project(${CMAKE_PROJECT_NAME})

# library 
set( lib "common" )

# headers
set( headers 
    common.hh
)

# source files
set( sources
    common.cc
)

# copy headers to include directory
# file( COPY ${headers} DESTINATION ${inc} )

# create lib
add_library( ${lib} "" )
set_property(TARGET ${lib} PROPERTY CXX_STANDARD 11)
target_sources( ${lib} 
    PRIVATE
        ${sources} 
        ${headers}
)

target_include_directories( ${lib}
    PUBLIC
        ./
)

target_link_libraries( ${lib}
    PRIVATE
    PUBLIC
        igl::core 
)

# copies 'common' into lib_dir
add_custom_command(TARGET ${lib} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${lib}> ${lib_dir}
)

# add_subdirectory( unittests )
