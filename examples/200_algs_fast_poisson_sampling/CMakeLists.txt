#----------------------------------------------------------------------
# makeshape | 200_algs_fast_poisson_sampling
#----------------------------------------------------------------------
project ( ${CMAKE_PROJECT_NAME} )

# executable 
set( exe "200_algs_fast_poisson_sampling" )

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
        "algs"
        "spatial"
        "app"
    PUBLIC
        "cxxopts"
)

target_link_libraries( ${exe}
    PRIVATE
        "common"
        "algs"
        "spatial"
        "app"
    PUBLIC
        "cxxopts"
)

# copies 'makeshape_bin' into bin_dir
add_custom_command(TARGET ${exe} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${exe}> ${bin_dir}
)
