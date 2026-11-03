#ifndef PHI_HPP
#define PHI_HPP

#include <cmath>

#define __R_PHI_FUNCTION__(N) \
    [&]() {\
    long long RESULT = N;\
    for (long long P = 2; P * P <= N; P++)\
    {\
        if (N % P == 0)\
        {\
            while (N % P == 0)\
            {\
                N /= P;\
            }\
            RESULT -= RESULT / P;\
        }\
    }\
    if (N > 1)\
    {\
        RESULT -= RESULT / N;\
    }\
    return RESULT; }()

#endif // PHI_HPP