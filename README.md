# Test Harness

A lightweight C++ testing framework inspired by Rust and Zig's testing style. 
Test Harness allows you to write inline tests alongside your code and provides
assertions with built-in floating-point approximate comparison.

## Features

- Inline tests with automatic test discovery
- Clean output format
- Smart assertions with type-specific comparison
- Automatic floating-point approximate equality
- Zero dependencies
- Conditional compilation to remove tests in release builds

## Usage

### Adding Test Harness to Your Project

#### Option 1: CMake Integration

```cmake
# In your project's CMakeLists.txt
find_package(test_harness REQUIRED)

# To enable testing
target_link_libraries(your_target PRIVATE test_harness)
target_compile_definitions(your_target PRIVATE TEST_MODE)
```

#### Option 2: Direct Inclusion

Simply copy the `include/test_harness` directory into your project and include the headers.

### Writing Tests

Tests are written inline with your code:

```cpp
#include <test_harness/test.hpp>

// Your code
int add(int a, int b) {
    return a + b;
}

// Test for your code
TEST(add_works) {
    assert_eq(5, add(2, 3));
    assert_eq(0, add(-2, 2));
    assert_ne(4, add(1, 1));
    return true;
}
```

### Running Tests

```cpp
// In your main.cpp or test_runner.cpp
#include <test_harness/test.hpp>

int main() {
    return test_harness::run_tests() ? 0 : 1;
}
```

## Assertions

Test Harness provides several assertion macros:

- `assert(condition)` - Verifies that a condition is true
- `assert_eq(expected, actual)` - Verifies that two values are equal
- `assert_ne(expected, actual)` - Verifies that two values are not equal

For floating-point types, `assert_eq` and `assert_ne` automatically use approximate equality with a default epsilon of 1e-6. This can be customized by defining `TEST_HARNESS_EPSILON` before including the headers.

## Conditional Compilation

To exclude tests from your builds, simply avoid defining `TEST_MODE`. In this case, the `TEST` macro expands to an unused function stub, which the compiler will typically optimize away completely.

## Example

```cpp
#include <test_harness/test.hpp>
#include <cmath>

float calculate_distance(float x1, float y1, float x2, float y2) {
    return std::sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

TEST(distance_calculation) {
    // Assert equality
    assert_eq(5.0f, calculate_distance(0, 0, 3, 4));
    
    // Also works with mixed types
    assert_eq(5, calculate_distance(0, 0, 3, 4));

    // Assert inequality
    assert_nq(27, calculate_distance(0, 0, 3, 4));
    
    // And basic assertions
    assert(calculate_distance(0, 0, 1, 0) < 2);
    
    return true;
}
```
