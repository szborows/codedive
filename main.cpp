#include <gtest/gtest.h>

int main(int ac, char ** av) {
    try {
        ::testing::InitGoogleTest(&ac, av);
        return RUN_ALL_TESTS();
    }
    catch(...) {
        return 1;
    }
}
