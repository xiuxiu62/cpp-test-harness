#pragma once

#include "../private/string_conversion.hpp"
#include <iostream>
#include <type_traits>

#define TEST_HARNESS_EPSILON 1e-6

#define assert(condition)                                                                                              \
    if (!assert_impl((condition), #condition, __FILE__, __LINE__)) return false;

#define assert_eq(expected, actual)                                                                                    \
    if (!assert_eq_impl((expected), (actual), #expected, #actual, __FILE__, __LINE__)) return false;

#define assert_ne(expected, actual)                                                                                    \
    if (!assert_ne_impl((expected), (actual), #expected, #actual, __FILE__, __LINE__)) return false;

template <typename T> struct is_floating_point_like : std::is_floating_point<T> {};

inline bool assert_impl(bool condition, const char *expr, const char *file, int line) {
    if (!condition) {
        std::cerr << "Assertion failed: " << expr << '\n';
        std::cerr << "  at: " << file << ':' << line << '\n';
    }
    return condition;
}

template <typename T> // Floating point impl
typename std::enable_if<is_floating_point_like<T>::value, bool>::type
assert_eq_impl(const T &expected, const T &actual, const char *expected_expr, const char *actual_expr, const char *file,
               int line) {
    bool condition = std::abs(expected - actual) <= TEST_HARNESS_EPSILON;
    if (!condition) {
        std::cerr << "Assertion failed: " << expected_expr << " == " << actual_expr << std::endl;
        std::cerr << "  left: " << to_string(expected) << std::endl;
        std::cerr << " right: " << to_string(actual) << std::endl;
        std::cerr << "   at: " << file << ":" << line << std::endl;
        std::cerr.flush();
    }
    return condition;
}

template <typename T> // Non-Floating point impl
typename std::enable_if_t<!is_floating_point_like<T>::value, bool>::type
assert_eq_impl(const T &expected, const T &actual, const char *expected_expr, const char *actual_expr, const char *file,
               int line) {
    bool condition = expected == actual;
    if (!condition) {
        std::cerr << "Assertion failed: " << expected_expr << " == " << actual_expr << std::endl;
        std::cerr << "  left: " << to_string(expected) << std::endl;
        std::cerr << " right: " << to_string(actual) << std::endl;
        std::cerr << "   at: " << file << ":" << line << std::endl;
        std::cerr.flush();
    }
    return condition;
}

template <typename T> // Floating point impl
typename std::enable_if<is_floating_point_like<T>::value, bool>::type
assert_ne_impl(const T &expected, const T &actual, const char *expected_expr, const char *actual_expr, const char *file,
               int line) {
    bool condition = std::abs(expected - actual) > TEST_HARNESS_EPSILON;
    if (!condition) {
        std::cerr << "Assertion failed: " << expected_expr << " != " << actual_expr << std::endl;
        std::cerr << "Both values are: " << to_string(expected) << std::endl;
        std::cerr << "   at: " << file << ":" << line << std::endl;
        std::cerr.flush();
    }
    return condition;
}

template <typename T> // Non-Floating point impl
typename std::enable_if_t<!is_floating_point_like<T>::value, bool>::type
assert_ne_impl(const T &expected, const T &actual, const char *expected_expr, const char *actual_expr, const char *file,
               int line) {
    bool condition = expected != actual;
    if (!condition) {
        std::cerr << "Assertion failed: " << expected_expr << " != " << actual_expr << std::endl;
        std::cerr << "Both values are: " << to_string(expected) << std::endl;
        std::cerr << "   at: " << file << ":" << line << std::endl;
        std::cerr.flush();
    }
    return condition;
}
