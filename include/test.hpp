#pragma once

#include <string>

typedef bool (*TestFn)();

struct Test {
    std::string name;
    const char *local_name;
    const char *file_path;
    int line;
    TestFn fn;
};

static std::string create_test_name(const char *file_path, const char *local_name);

static void register_test(const char *local_name, TestFn fn, const char *file_path, int line);

static bool run_tests();

#define TEST(name)                                                                                                     \
    static bool test_func_##name(void);                                                                                \
    struct RegisterTest_##name {                                                                                       \
        RegisterTest_##name() {                                                                                        \
            register_test(#name, test_func_##name, __FILE__, __LINE__);                                                \
        }                                                                                                              \
    } register_test_##name;                                                                                            \
    static bool test_func_##name()
