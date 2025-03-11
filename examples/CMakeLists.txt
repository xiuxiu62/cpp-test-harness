# CMakeLists.txt for examples
cmake_minimum_required(VERSION 3.14)

# Function to automatically build all example cpp files
function(build_examples_from_directory dir)
    # Get all cpp files in the specified directory
    file(GLOB EXAMPLE_SOURCES "${dir}/*.cpp")
    
    # Loop through each cpp file
    foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
        # Extract the filename without extension to use as the target name
        get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE)
        
        # Create an executable target for this example
        add_executable(${EXAMPLE_NAME}_example ${EXAMPLE_SOURCE})
        
        # Link it with the test_harness library
        target_link_libraries(${EXAMPLE_NAME}_example PRIVATE test_harness)
        
        message(STATUS "Added example: ${EXAMPLE_NAME}_example from ${EXAMPLE_SOURCE}")
    endforeach()
endfunction()

# Call the function to build all examples in the current directory
build_examples_from_directory(${CMAKE_CURRENT_SOURCE_DIR})
