#----------------------------------------------------------------------
# spatial
#----------------------------------------------------------------------
project ( ${CMAKE_PROJECT_NAME} )

# library 
set( test "unittest_icp" )

# headers
set( headers 
)

# source files
set( sources
    unittest_least_sq.cc
)

# copy headers to include directory
# file( COPY ${headers} DESTINATION ${inc} )

# create test exectuable
add_executable( ${test} "" )
set_property(TARGET ${test} PROPERTY CXX_STANDARD 11)
target_sources( ${test} 
    PRIVATE
        ${sources} 
        ${headers}
)

target_include_directories( ${test}
    PRIVATE
        "spatial"
        "icp"
    PUBLIC
        ./
)

target_link_libraries( ${test}
    PRIVATE
        "spatial"
        "icp"
    PUBLIC
        gtest_main
)

# copies 'unittest_commmon' into 'builds/tests'
add_custom_command(TARGET ${test} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${test}> ${test_dir}
)

add_test(NAME ${test} 
           COMMAND ${test_dir}/${test}
           WORKING_DIRECTORY ${data_dir}
)
