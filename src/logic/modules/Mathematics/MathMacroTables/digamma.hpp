#ifndef DIGAMMA_HPP
#define DIGAMMA_HPP

#include <cmath>

#define __R_DI_GAMMA_FUNCTION__(X) [&]() {\
    if (X <= 0.0) return NAN;\
    float RESULT = 0.0;\
    while (X < 8.0)\
    {\
        RESULT -= 1.0 / X;\
        X += 1.0;\
    }\
    float R_X = 1.0 / X;\
    float R_X2 = std::pow(R_X, 2);\
    RESULT += std::log(X) - 0.5 * R_X;\
    RESULT -= R_X2 * (\
        (1.0 / 12.0) - R_X2 * (\
            (1.0 / 120.0) - R_X2 * (\
                (1.0 / 252.0) - R_X2 * (1.0 / 240.0)\
            )\
        )\
    );\
    return RESULT; }()

#endif // DIFGAMMA_HPP