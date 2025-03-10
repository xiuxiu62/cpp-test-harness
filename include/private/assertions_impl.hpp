#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>

#define EPSILON 1e-6

template <typename T> struct is_floating_point_like : std::is_floating_point<T> {};

template <typename T> std::string to_string(const T &val) {
    std::ostringstream oss;
    oss << val;
    return oss.str();
}

template <> inline std::string to_string(const std::string &val) {
    return "\"" + val + "\"";
}

template <> inline std::string to_string(const char *const &val) {
    return val ? ('"' + std::string(val) + '"') : "nullptr";
}

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
    bool condition = std::abs(expected - actual) <= EPSILON;
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
    bool condition = std::abs(expected - actual) > EPSILON;
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
