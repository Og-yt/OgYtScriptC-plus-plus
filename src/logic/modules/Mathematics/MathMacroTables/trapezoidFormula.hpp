#ifndef TRAPEZOIDFORMULA_HPP
#define TRAPEZOIDFORMULA_HPP

#include <iomanip>
#include <cmath>

#define __R_TRAPEZOID_FORMULA_FUNCTION__(F, A, B, SUB) [&]() {\
    if (SUB < 1)\
    {\
        return 0.0;\
    }\
    double H = (B - A);\
    double INTEGRAL_SUM = F(A) + F(B);\
    for (int I = 1; I < SUB; ++I)\
    {\
        double X = A + I * H;\
        INTEGRAL_SUM += 2.0 * F(X);\
    }\
    return (H / 2.0) * INTEGRAL_SUM; }()

#endif // TRAPEZOIDFORMULA_HPP