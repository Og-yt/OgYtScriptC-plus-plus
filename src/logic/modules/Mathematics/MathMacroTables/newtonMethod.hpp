#ifndef NEWTONMETHOD_HPP
#define NEWTONMETHOD_HPP

#include <iomanip>
#include <cmath>

#define __CALC_NUM_DERIV__H__ 1e-5
#define __CALCULATE_NUMERICAL_DERIVATIVE__(F, X) [&]() {\
    if (H == 0.0) return 0.0;\
    return (F(X + H) - F(X - H)) / (2.0 * H); }()

struct NEWTONRESULT
{
    double ROOT;
    int ITERATIONS;
    bool CONVERGED;
};

#define __R_NEWTON_FUNC_TOLERANCE 1e-7
#define __R_NEWTON_FUNC_MEX_ITERATIONS 100
#define __R_NEWTON_METHOD_FUNCTION__(F, INITIAL) [&]() {\
    double X = INITIAL;\
    for (int I = 0; I < __R_NEWTON_FUNC_MEX_ITERATIONS; I++)\
    {\
        RESULT.INITIAL;\
        double Y = F(X);\
        if (std::abs(Y) < __R_NEWTON_FUNC_TOLERANCE)\
        {\
            RESULT.ROOT = X;\
            RESULT.ITERATIONS = I;\
            RESULT.CONVERGED = true;\
            return RESULT;\
        }\
        double DERIVATIVE = __CALCULATE_NUMERICAL_DERIVATIVE__(F, X);\
        if (DERIVATIVE == 0.0)\
        {\
            break;\
        }\
        double NEXT_X = X - (Y / DERIVATIVE);\
        if (std::abs(NEXT_X - X) < __R_NEWTON_FUNC_TOLERANCE)\
        {\
            RESULT.ROOT = NEXT_X;\
            RESULT.CONVERGED = true;\
            return RESULT;\
        }\
        X = NEXT_X;\
    }\
    RESULT.ROOT = X;\
    return RESULT; }()

#endif // NEWTONMETHOD_HPP