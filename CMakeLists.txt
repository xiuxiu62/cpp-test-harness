cmake_minimum_required(VERSION 3.14)
project(test_harness VERSION 0.1.0 LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Option to enable testing support
option(TEST_MODE "Enable testing support" OFF)

file(GLOB_RECURSE PUBLIC_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/test.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/include/assertions.hpp")
file(GLOB_RECURSE PRIVATE_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/test_impl.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/include/assertions_impl.hpp")

# Create the library
add_library(test_harness INTERFACE)

set(PUBLIC_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/public")
set(PRIVATE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/private")

# Configure include directories - note the syntax fix
target_include_directories(test_harness
    PRIVATE
        ${PRIVATE_INCLUDE_DIR}
    PUBLIC 
        ${PUBLIC_INCLUDE_DIR}
)

# Set compile definitions based on TEST_MODE option
if(TEST_MODE)
    target_compile_definitions(test_harness PUBLIC TEST_MODE)
endif()

# Example tests (optional)
option(TEST_HARNESS_BUILD_EXAMPLES "Build example tests" OFF)
if(TEST_HARNESS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
