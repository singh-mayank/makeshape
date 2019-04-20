#----------------------------------------------------------------------
#
#----------------------------------------------------------------------
project ( ${CMAKE_PROJECT_NAME} )

# executable 
set( exe "makeshape_bin" )

# headers
set( headers 
    app.hh
)

# source files
set( sources
    app.cc
    main.cc
)

# copy headers to include directory
# file( COPY ${headers} DESTINATION ${inc} )

# create lib
add_executable( ${exe} "" )
set_property(TARGET ${exe} PROPERTY CXX_STANDARD 11)
target_sources( ${exe} 
    PRIVATE
        ${sources} 
        ${headers}
)

target_include_directories( ${exe}
    PUBLIC
        ./
        "mesh"
)

target_link_libraries( ${exe}
    PRIVATE
        "mesh"
    PUBLIC
        igl::core 
        igl::opengl_glfw 
        igl::opengl_glfw_imgui 
        igl::png
)

# copies 'makeshape_bin' into bin_dir
add_custom_command(TARGET ${exe} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${exe}> ${bin_dir}
)


# copies everything from data/ into build/data directory
add_custom_command(TARGET ${exe} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/data ${data_dir}
)

# add_subdirectory( unittests )
