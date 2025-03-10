#pragma once

#include "../private/assertions_impl.hpp"

#define assert(condition)                                                                                              \
    if (!assert_impl((condition), #condition, __FILE__, __LINE__)) return false;

#define assert_eq(expected, actual)                                                                                    \
    if (!assert_eq_impl((expected), (actual), #expected, #actual, __FILE__, __LINE__)) return false;

#define assert_ne(expected, actual)                                                                                    \
    if (!assert_ne_impl((expected), (actual), #expected, #actual, __FILE__, __LINE__)) return false;
