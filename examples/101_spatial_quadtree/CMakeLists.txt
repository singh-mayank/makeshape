#----------------------------------------------------------------------
# makeshape
#----------------------------------------------------------------------
project ( ${CMAKE_PROJECT_NAME} )

# executable 
set( exe "101_spatial_quadtree" )

# headers
set( headers 
    quadtree.hh
)

# source files
set( sources
    quadtree.cc
    main.cc
)

# copy headers to include directory
# file( COPY ${headers} DESTINATION ${inc} )

# create exe 
add_executable( ${exe} "" )
set_property(TARGET ${exe} PROPERTY CXX_STANDARD 11)
target_sources( ${exe} 
    PRIVATE
        ${sources} 
        ${headers}
)

target_include_directories( ${exe}
    PRIVATE
        ./
        "common"
        "spatial"
        "app"
)

target_link_libraries( ${exe}
    PRIVATE
        "common"
        "spatial"
        "app"
)

# copies 'makeshape_bin' into bin_dir
add_custom_command(TARGET ${exe} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${exe}> ${bin_dir}
)
