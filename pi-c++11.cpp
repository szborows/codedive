#include <gtest/gtest.h>

#include <iostream>
using namespace std;

constexpr unsigned get_x(unsigned const n) {
    return n == 0 ? 3 : 2 + get_x(n - 1);
}

constexpr int get_sign(unsigned const n) {
    return n % 2 ? -1 : 1;
}

constexpr double pi(unsigned const n) {
    return n == 0
        ? 3.0
        : (pi(n - 1) + (get_sign(n) * 4.0) / (get_x(n) - 1) * get_x(n) * (get_x(n) + 1));
}

template <unsigned V> struct TestInCompileTime {
    static const unsigned value;
};

template <unsigned V>
const unsigned TestInCompileTime<V>::value = V;

TEST(PiTest, DISABLED_Cxx11) {
    double const result = pi(3);
    ASSERT_NEAR(3.1415, result, 2e-2);
    ASSERT_EQ(3u, TestInCompileTime<static_cast<unsigned>(-pi(3))>::value);
}
