#ifndef POLYGAMMA_HPP
#define POLYGAMMA_HPP

#include <cmath>

#define __POLY_GAMMA_FACT__(X) [&]() { long long f = 1; for (int i = 1; i <= X; i++){f *= i;} return f; }()
#define __R_POLY_GAMMA_FUNCTION__(M, X) [&]() {\
    if (X <= 0.0 || M < 1) return NAN;\
    float SHIFT_SUM = 0.0;\
    float FACT_M = __POLY_GAMMA_FACT__(M);\
    float SIGN = (M % 2 == 0) ? -1.0 : 1.0;\
    while (X < 8.0)\
    {\
        SHIFT_SUM += SIGN * FACT_M / std::pow(X, M + 1);\
        X += 1.0;\
    }\
    float R_X = 1.0 / X;\
    float RESULT = FACT_M * std::pow(R_X, M) * (R_X + 0.5 * M * R_X * R_X);\
    float R_X2 = std::pow(R_X,2);\
    float T2 = (1.0 / 6.0) * __POLY_GAMMA_FACT__(M + 1) / 2.0 * std::pow(R_X, M + 2);\
    float T4 = (-1.0 / 30.0) * __POLY_GAMMA_FACT__(M + 3) / 24.0 * std::pow(R_X, M + 4);\
    float T6 = (1.0 / 42.0) * __POLY_GAMMA_FACT__(M + 5) / 720.0 * std::pow(R_X, M + 6);\
    RESULT += T2 + T4 + T6;\
    return RESULT - SHIFT_SUM; }()

#endif // POLYGAMMA_HPP