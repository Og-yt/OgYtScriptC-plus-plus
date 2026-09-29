#ifndef FINITEFIELDINVERSE_HPP
#define FINITEFIELDINVERSE_HPP

#define __R_FINITE_FILED_INVERSE_FUNCTION__(A, P)[&]() {\
    A = (A % P + P) % P;\
    if (A == 0 || P <= 1)\
    {\
        return -1;\
    }\
    long long M0 = P;\
    long long Y = 0, X = 1;\
    while (A > 1)\
    {\
        if (P == 0)\
        {\
            return -1;\
        }\
        long long Q = A / P;\
        long long T = P;\
        P = A % P;\
        A = T;\
        T = Y;\
        Y = X - Q * Y;\
        X = T;\
    }\
    if (A != 1)\
    {\
        return -1;\
    }\
    if (X < 0)\
    {\
        X += M0;\
    }\
    return X; }()

#endif // FINITEFIELDINVERSE_HPP