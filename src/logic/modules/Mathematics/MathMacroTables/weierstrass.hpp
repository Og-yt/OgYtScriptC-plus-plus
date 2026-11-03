#ifndef WEIERSTRASS_HPP
#define WEIERSTRASS_HPP

#include <cmath>

#define __R_WEIERSTRASS_FUNCTION__(X, A, B, MAX_ITERATIONS) [&]() {\
    double SUM = 0.0;\
    for (int N = 0; N < MAX_ITERATIONS; ++N)\
    {\
        double TERM = std::pow(A, N) * std::cos(std::pow(B, N) * PI * X);\
        SUM += TERM;\
    }\
    return SUM; }()

#endif // WEIERSTRASS_HPP