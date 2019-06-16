#----------------------------------------------------------------------
# makeshape
#----------------------------------------------------------------------
project ( ${CMAKE_PROJECT_NAME} )

# executable 
set( exe "100_spatial_octree" )

# headers
set( headers 
)

# source files
set( sources
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


# use this in cases where exectuable needs data files.
# copies everything from data/ into build/data directory
#add_custom_command(TARGET ${exe} PRE_BUILD
    #COMMAND ${CMAKE_COMMAND} -E copy_directory
    #${CMAKE_SOURCE_DIR}/data ${data_dir}
#)

