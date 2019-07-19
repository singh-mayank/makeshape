#----------------------------------------------------------------------
#
#----------------------------------------------------------------------
project ( ${CMAKE_PROJECT_NAME} )

# library 
set( lib "spatial" )

# headers
set( headers 
    aabb.hh
    bsphere.hh
    edges.hh
    intersections.hh
    kdtree.hh
    kdtree2.hh
    octree.hh
    trimesh.hh
)

# source files
set( sources
    aabb.cc
    bsphere.cc
    edges.cc
    intersections.cc
    kdtree.cc
    kdtree2.cc
    octree.cc
    trimesh.cc
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
        "common"
)

target_link_libraries( ${lib}
    PRIVATE
        "common"
    PUBLIC
        igl::core
)

# copies 'spatial' into lib_dir
add_custom_command(TARGET ${lib} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${lib}> ${lib_dir}
)

add_subdirectory( unittests )
