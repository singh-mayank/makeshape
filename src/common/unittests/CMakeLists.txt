#----------------------------------------------------------------------
#
#----------------------------------------------------------------------
project ( ${CMAKE_PROJECT_NAME} )

# library 
set( test "unittest_common" )

# headers
set( headers 
)

# source files
set( sources
    unittest_octree.cc
)

# copy headers to include directory
# file( COPY ${headers} DESTINATION ${inc} )

# create lib
add_executable( ${test} "" )
set_property(TARGET ${test} PROPERTY CXX_STANDARD 11)
target_sources( ${test} 
    PRIVATE
        ${sources} 
        ${headers}
)

target_include_directories( ${test}
    PUBLIC
        ./
        "common"
)

target_link_libraries( ${test}
    PRIVATE
        "common"
    PUBLIC
        gtest_main
)

# copies 'unittest_commmon' into 'builds/tests'
add_custom_command(TARGET ${test} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${test}> ${test_dir}
)

add_test(NAME ${test} COMMAND ${test_dir}/${test} )
