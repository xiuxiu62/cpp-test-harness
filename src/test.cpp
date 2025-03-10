#include "../include/test.hpp"

#include <iostream>
#include <vector>

static std::vector<Test> tests;

static std::string create_test_name(const char *file_path, const char *local_name) {
    std::string path(file_path);
    std::string result;

    // Remove file extension
    size_t dot_pos = path.find_last_of('.');
    if (dot_pos != std::string::npos) {
        path = path.substr(0, dot_pos);
    }

    // Replace directory separators with ::
    size_t pos = 0;
    while ((pos = path.find('/', pos)) != std::string::npos) {
        path.replace(pos, 1, "::");
        pos += 2;
    }

    pos = 0;
    while ((pos = path.find('\\', pos)) != std::string::npos) {
        path.replace(pos, 1, "::");
        pos += 2;
    }

    // Combine the module path with the test name
    return path + "::" + local_name;
}

static void register_test(const char *local_name, TestFn fn, const char *file_path, int line) {
    auto name = create_test_name(file_path, local_name);
    tests.push_back({
        .name = name,
        .local_name = local_name,
        .file_path = file_path,
        .line = line,
        .fn = fn,
    });
}

static bool run_tests() {
    auto test_count = tests.size();

    std::cout << "running " << test_count << " test";
    if (test_count != 1) std::cout << 's';
    std::cout << std::endl;
    std::cout.flush();

    int failures = 0;
    for (const auto &test : tests) {

        bool passed = test.fn();
        if (passed) {
            std::cout << "[PASS]";
        } else {
            std::cout << "[FAIL]";
            failures++;
        }

        std::cout << "test " << test.name << std::endl;
        std::cout.flush();
    }

    std::cout << std::endl;
    if (failures > 0) {
        std::cout << "failures:" << std::endl;
        std::cout << std::endl;

        // TODO: store and print failure messages

        std::cout << "test result: FAILED. " << (test_count - failures) << " passed; " << failures << " failed"
                  << std::endl;
    } else {
        std::cout << "test result: ok. " << test_count << " passed; 0 failed" << std::endl;
    }

    return failures == 0;
}

#define TEST(name)                                                                                                     \
    static bool test_func_##name(void);                                                                                \
    struct RegisterTest_##name {                                                                                       \
        RegisterTest_##name() {                                                                                        \
            register_test(#name, test_func_##name, __FILE__, __LINE__);                                                \
        }                                                                                                              \
    } register_test_##name;                                                                                            \
    static bool test_func_##name()
