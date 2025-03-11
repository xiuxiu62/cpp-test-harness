#include "../include/public/assertions.hpp"
#include "../include/public/test.hpp"

struct IVec2 {
    int x, y;

    inline bool operator==(IVec2 &rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    inline bool operator!=(IVec2 &rhs) const {
        return x != rhs.x || y != rhs.y;
    }
};

TEST(passes) {
    IVec2 a{1, 2};
    IVec2 b{1, 2};

    assert_eq(a, b);
    assert_ne(a, b);
}

TEST(fails) {
    IVec2 a{1, 2};
    IVec2 b{2, 1};

    assert_eq(a, b);
    assert_ne(a, b);
}
