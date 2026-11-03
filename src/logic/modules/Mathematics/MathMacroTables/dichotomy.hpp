#ifndef DICHOTOMY_HPP
#define DICHOTOMY_HPP

#include <iomanip>
#include <cmath>
#include "../../../ErrorLogic.hpp"

struct DICHOTOMYRESULT
{
    double ROOT;
    int ITERATIONS;
    bool SUCCESS;
};

#define __DICHO_RESULT
#define __DICHO_LINE
#define __DICHO_BUFFER
#define __R_DICHOTOMY_FUNCTION__(F, A, B) [&]() {\
    DICHOTOMYRESULT RESULT = {0.0, 0, false};\
    double FA = F(A);\
    double FB = F(B);\
    if (FA * FB >= 0.0)\
    {\
        __DICHO_RESULT += ErrorLogic::build_msg(__DICHO_LINE, "The function signs at the endpoints must be opposite. f(a)*f(b) >= 0");\
        ErrorLogic::highlight_line(__DICHO_BUFFER, __DICHO_LINE);\
        return RESULT;\
    }\
    double C = A;\
    for (int I = 0; I < 100; ++I)\
    {\
        RESULT.ITERATIONS++;\
        C = A + (B - A) / 2.0;\
        double FC = F(C);\
        if (std::abs(FC) < 1e-7 || (B - A) / 2.0 < 1e-7)\
        {\
            RESULT.ROOT = C;\
            RESULT.SUCCESS = true;\
            return RESULT;\
        }\
        if ((FA * FC) < 0.0)\
        {\
            B = C;\
            FB = FC;\
        }\
        else\
        {\
            A = C;\
            FA = FC;\
        }\
    }\
    RESULT.ROOT = C;\
    RESULT.SUCCESS = true;\
    return RESULT; }()

#endif // DICHOTOMY_HPP