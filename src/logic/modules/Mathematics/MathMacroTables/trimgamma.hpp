#ifndef TRIGAMMA_HPP
#define TRIGAMMA_HPP

#include <cmath>

#define __R_TRI_GAMMA_FUNCTION__(X) [&]() {\
    if (X <= 0.0)\
    {\
        return NAN;\
    }\
    float RESULT = 0.0;\
    while (X < 8.0)\
    {\
        RESULT += 1.0 / (X * X);\
        X += 1.0;\
    }\
    float R_X = 1.0 / X;\
    float R_X2 = std::pow(R_X, 2);\
    RESULT += R_X + 0.5 * R_X2;\
    RESULT += R_X * R_X2 * (\
        (1.0 / 6.0) - R_X2 * (\
            (1.0 / 30.0) - R_X2 * (\
                (1.0 / 42.0) - R_X2 * (1.0 / 30.0)\
            )\
        )\
    );\
    return RESULT; }()

#endif // TRIGAMMA_HPP