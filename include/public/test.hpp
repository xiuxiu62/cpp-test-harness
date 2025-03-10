#pragma once

#ifdef TEST_MODE

#include "../private/test_impl.hpp"

#define TEST(name)                                                                                                     \
    static bool test_func_##name(void);                                                                                \
    struct RegisterTest_##name {                                                                                       \
        RegisterTest_##name() {                                                                                        \
            register_test(#name, test_func_##name, __FILE__, __LINE__);                                                \
        }                                                                                                              \
    } register_test_##name;                                                                                            \
    static bool test_func_##name()

#else

#define TEST(name) static void test_func_##name(void) __attribute__((unused))

#endif
