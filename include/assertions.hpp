#pragma once

#include <type_traits>

template <typename T> struct is_floating_point_like : std::is_floating_point<T> {};

inline bool assert_impl(bool condition, const char *expr, const char *file, int line);

template <typename T> // Floating point impl
typename std::enable_if<is_floating_point_like<T>::value, bool>::type
assert_eq_impl(const T &expected, const T &actual, const char *expected_expr, const char *actual_expr, const char *file,
               int line);

template <typename T> // Non-Floating point impl
typename std::enable_if_t<!is_floating_point_like<T>::value, bool>::type
assert_eq_impl(const T &expected, const T &actual, const char *expected_expr, const char *actual_expr, const char *file,
               int line);

template <typename T> // Floating point impl
typename std::enable_if<is_floating_point_like<T>::value, bool>::type
assert_ne_impl(const T &expected, const T &actual, const char *expected_expr, const char *actual_expr, const char *file,
               int line);

template <typename T> // Non-Floating point impl
typename std::enable_if_t<!is_floating_point_like<T>::value, bool>::type
assert_ne_impl(const T &expected, const T &actual, const char *expected_expr, const char *actual_expr, const char *file,
               int line);

#define assert(condition)                                                                                              \
    if (!assert_impl((condition), #condition, __FILE__, __LINE__)) return false;

#define assert_eq(expected, actual)                                                                                    \
    if (!assert_eq_impl((expected), (actual), #expected, #actual, __FILE__, __LINE__)) return false;

#define assert_ne(expected, actual)                                                                                    \
    if (!assert_ne_impl((expected), (actual), #expected, #actual, __FILE__, __LINE__)) return false;
