#ifndef BARNESG_HPP
#define BARNESG_HPP

#include <cmath>

#define __BAR_INT_FACTORIAL(X) [&]() { long long f = 1; for (int i = 1; i <= X; i++){f *= i;} return f; }()
#define __R_BARNES_G_FUNCTION_INTEGER_VER__(N) [&]() {\
    if (N <= 2) return 1;\
    int RESULT = 1;\
    for (long long I = 2; I <= N; ++I)\
    {\
        RESULT *= __BAR_INT_FACTORIAL(I);\
    }\
    return RESULT; }()

#define __BARNES_LN 0.9189385332046727
#define __R_BARNES_G_FUNCTION_REAL_VER_LOG_GAMMA__(X) [&]() {\
    return (X - 0.5) * std::log(X) - X + __BARNES_LN + (1.0 / (12.0 * X)) - (1.0 / (360.0 * std::pow(X, 3))); }()
#define __R_BARNES_G_FUNCTION_REAL_VER_LOG_BARNES_G_LARGEST__(X) [&]() {\
    double X2 = std::pow(X,2);\
    double LOG_G = (X2 / 2.0 - 1.0 / 12.0) * std::log(X)\
                   - (3.0 * X2 / 4.0)\
                   + (X / 2.0) * std::log(2.0 * PI);\
                   + 0.04550953986963283;\
    LOG_G += 1.0 / (288.0 * X2) - 1.0 / (240.0 * std::pow(X, 4));\
    return LOG_G;\
}()
#define __R_BARNES_G_FUNCTION_REAL_VER__(X) [&]() {\
    if (X <= 0.0) return 0.0;\
    double SHIFT_FACTOR = 0.0;\
    while (X < 10.0)\
    {\
        SHIFT_FACTOR += __R_BARNES_G_FUNCTION_REAL_VER_LOG_GAMMA__(X);\
        X += 1.0;\
    }\
    double LOG_G = __R_BARNES_G_FUNCTION_REAL_VER_LOG_BARNES_G_LARGEST__(X) - SHIFT_FACTOR;\
    return std::exp(LOG_G); }()

#endif // BARNESG_HPP