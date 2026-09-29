#ifndef NUMERICALINTEGRAL_HPP
#define NUMERICALINTEGRAL_HPP

#include <iomanip>
#include <cmath>

#define __R_NUMERICAL_INTEGRAL__(F, A, B, SUB) [&]() {\
    if (SUB < 2 || SUB % 2 != 0)\
    {\
        return 0.0;\
    }\
    double H = (B - A);\
    double I = F(A) + F(B);\
    for (int I = 1; I < SUB; ++I)\
    {\
        double X = A + I * H;\
        if (I % 2 != 0)\
        {\
            I += 4.0 * F(X);\
        }\
        else\
        {\
            I += 2.0 * F(X);\
        }\
    }\
    return (H / 3.0) * I; }()

#endif // NUMRICALINTEGRAL_HPP