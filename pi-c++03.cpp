#include <gtest/gtest.h>

#include <iostream>
using namespace std;

typedef const long long unsigned llu;

template <llu N, llu D> struct Fraction {
    static llu Numerator = N;
    static llu Denominator = D;
};

template <llu N, typename F> struct ScalarMultiplication {
    typedef Fraction<N * F::Numerator, N * F::Denominator> type;
};

template <llu X, llu Y> struct MCD {
    static llu value = MCD<Y, X % Y>::value;
};

template <llu X> struct MCD<X, 0> {
    static llu value = X;
};

template <typename F> struct Simplify {
    static llu mcd = MCD<F::Numerator, F::Denominator>::value;
    typedef Fraction<F::Numerator / mcd, F::Denominator / mcd> type;
};

template <typename X1, typename Y1> struct SameBase {
    typedef typename ScalarMultiplication<Y1::Denominator, X1>::type X;
    typedef typename ScalarMultiplication<X1::Denominator, Y1>::type Y;
};

template <typename X, typename Y> struct Sum {
    typedef SameBase<X, Y> B;
    static llu Numerator = B::X::Numerator + B::Y::Numerator;
    static llu Denominator = B::X::Denominator;
    typedef Fraction<Numerator, Denominator> type;
};

template <unsigned N> struct Term {
    static llu X = Term<N - 1>::X + 2;
    static llu value = (X - 1) * X * (X + 1);
};

template <> struct Term<1> {
    static llu X = 3;
    static llu value = 24;
};

template <unsigned N> struct IsOdd {
    static const unsigned intValue = static_cast<unsigned>((N % 2) != 0);
    typedef Fraction<intValue, 1> frac;
};

template <unsigned N> struct IsEven {
    static const unsigned intValue = 1u - IsOdd<N>::intValue;
    typedef Fraction<intValue, 1> frac;
};

template <unsigned N> struct SumOdd {
    typedef Fraction<IsOdd<N>::frac::Numerator * 4, Term<N>::value> this_frac;
    //typedef typename ScalarMultiplication<IsEven<N>::intValue, Fraction<N, 1>>::type this_frac;
    typedef typename Sum<this_frac, typename SumOdd<N-1>::type>::type type;
};

template <> struct SumOdd<0> {
    typedef Fraction<0, 1> type;
};

template <unsigned N> struct SumEven {
    typedef Fraction<IsEven<N>::frac::Numerator * 4, Term<N>::value> this_frac;
    typedef typename Sum<this_frac, typename SumEven<N-1>::type>::type type;
};

template <> struct SumEven<0> {
    typedef Fraction<0, 1> type;
};

template <typename X, typename Y> struct Subtract {
    typedef SameBase<X, Y> B;
    static llu Numerator = B::X::Numerator - B::Y::Numerator;
    static llu Denominator = B::X::Denominator;
    typedef Fraction<Numerator, Denominator> type;
};

template <unsigned N> struct Pi {
    typedef Subtract<
        typename Simplify<typename SumOdd<N>::type>::type,
        typename Simplify<typename SumEven<N>::type>::type> terms;
    typedef typename Sum<Fraction<3, 1>, terms>::type type;
};

TEST(PiTest, Cxx03) {
    typedef Pi<5>::type PI;
    double const result = static_cast<double>(PI::Numerator) / static_cast<double>(PI::Denominator);
    ASSERT_NEAR(3.1415, result, 2e-2);
}
