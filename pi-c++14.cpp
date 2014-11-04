#include <gtest/gtest.h>

#include <iostream>
using namespace std;

constexpr double pi(unsigned const n) {
    double result = 3.;
    for (unsigned i = 0, x = 3; i < n; ++i, x += 2) {
        auto const& term = 4.0
            / static_cast<double>((x - 1) * x * (x + 1));
        result = (i % 2) ? result - term : result + term;
    }
    return result;
}

template <unsigned V> struct TestInCompileTime {
    static const unsigned value;
};

template <unsigned V>
const unsigned TestInCompileTime<V>::value = V;

TEST(PiTest, Cxx14) {
    double const result = pi(3);
    ASSERT_NEAR(3.1415, result, 2e-2);
    ASSERT_EQ(3u, TestInCompileTime<static_cast<unsigned>(pi(3))>::value);
}

// Old impl.
struct Frac {
    constexpr Frac operator+(Frac const& f) const {
        return {N * f.D + f.N * D, D * f.D};
    }

    constexpr Frac operator-(Frac const& f) const {
        return {N * f.D - f.N * D, D * f.D};
    }

    long long unsigned N, D;
};

constexpr Frac pi_working(unsigned const n) {
    Frac result = {3, 1};
    for (unsigned i = 0, x = 3; i < n; ++i, x += 2) {
        auto const& term = Frac{4, (x - 1) * x * (x + 1)};
        result = (i % 2) ? result - term : result + term;
    }
    return result;
}

