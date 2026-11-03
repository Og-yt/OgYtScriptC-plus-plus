#ifndef CLAUSENCL2_HPP
#define CLAUSENCL2_HPP

#include <cmath>
#include <string>
#include "../../../ErrorLogic.hpp"

#define TOLERANCE 1e-12

#define __R_CLAUSENCL2_FUNCTION__(X) [&]() {\
    int CL2_LOOP_COUNT = 0;\
    int CL2_LOOP_MAX_COUNT = 1000;\
    double CLAUSEN_SUM = 0.0;\
    double PREV_SUM = 0.0;\
    int CK = 1;\
    double TWO_PI = 2.0 * std::acos(-1.0);\
    X = std::fmod(X, TWO_PI);\
    if (X < 0) X += TWO_PI;\
    while (1000)\
    {\
        double TERM = std::sin(CK * X) / (CK * CK);\
        CLAUSEN_SUM += TERM;\
        if (std::abs(CLAUSEN_SUM - PREV_SUM) < TOLERANCE)\
        {\
            break;\
        }\
        CL2_LOOP_COUNT++;\
        if (CL2_LOOP_COUNT > CL2_LOOP_MAX_COUNT)\
        {\
            break;\
        }\
        PREV_SUM = CLAUSEN_SUM;\
        CK++;\
    }\
    return CLAUSEN_SUM; }()

#endif // CLAUSENCL2_HPP