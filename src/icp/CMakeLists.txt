#----------------------------------------------------------------------
# makeshape | icp 
#----------------------------------------------------------------------
project(${CMAKE_PROJECT_NAME})

# library 
set( lib "icp" )

# headers
set( headers 
    least_sq_rigid_motion.hh
)

# source files
set( sources
    least_sq_rigid_motion.cc
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
    PRIVATE
        "common"
        "spatial"
    PUBLIC
        ./
)

target_link_libraries( ${lib}
    PRIVATE
        "common"
        "spatial"
    PUBLIC
        igl::core 
)

# copies 'common' into lib_dir
add_custom_command(TARGET ${lib} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${lib}> ${lib_dir}
)

add_subdirectory( unittests )
