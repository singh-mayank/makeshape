#----------------------------------------------------------------------
# makeshape 
#----------------------------------------------------------------------
project ( ${CMAKE_PROJECT_NAME} )

# library 
set( lib "app" )

# headers
set( headers 
    app.hh
)

# source files
set( sources
    app.cc
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
        "spatial"
)

target_link_libraries( ${lib}
    PRIVATE
        "spatial"
    PUBLIC
        igl::core 
        igl::opengl_glfw 
        igl::opengl_glfw_imgui 
        igl::png # not needed.
)

# copies 'app' into lib_dir
add_custom_command(TARGET ${lib} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${lib}> ${lib_dir}
)

# add_subdirectory( unittests )
