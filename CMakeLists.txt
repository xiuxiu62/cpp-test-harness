cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE HEADERS "{CMAKE_CURRENT_SOURCE_DIR}/include/*.h" "{CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")
file(GLOB_RECURSE SOURCES "{CMAKE_CURRENT_SOURCE_DIR}/src/*.c" "{CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(test-core src/main.cpp)

function(add_engine_test TEST_NAME TEST_SOURCE)
  add_executable(${TEST_NAME} ${TEST_SOURCE})
  target_link_libraries(${TEST_NAME} PRIVATE ${PROJECT_NAME}_lib)

  if(USE_CATCH2)
    target_link_libraries(${TEST_NAME} PRIVATE Catch2::Catch2WithMain)
  endif()

  # Add the test so it can be run with ctest
  add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

  # Optional: Set timeouts or other test properties
  set_tests_properties(${TEST_NAME} PROPERTIES TIMEOUT 30)
endfunction()
