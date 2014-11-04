#include <gtest/gtest.h>

double pi(unsigned const n) {
    double result = 3.;
    for (unsigned i = 0, x = 3; i < n; ++i, x += 2) {
        auto const& term = 4.0 /
            static_cast<double>((x - 1) * x * (x + 1));
        result = (i % 2) ? result - term : result + term;
    }
    return result;
}

TEST(PiTest, Rt) {
    double const result = pi(3);
    ASSERT_NEAR(3.1415, result, 2e-2);
}
