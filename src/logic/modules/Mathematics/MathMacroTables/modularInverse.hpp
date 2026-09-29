#ifndef MODULARINVERSE_HPP
#define MODULARINVERSE_HPP

#define __R_MODULAR_INVERSE_FUNCTION__(A, M)[&]() {\
    long long M0 = M;\
    long long Y = 0, X = 1;\
    if (M == 1) return 0;\
    A = A % M;\
    if (A < 0) A += M;\
    while (A > 1)\
    {\
        if (M == 0) return -1;\
        long long Q = A / M;\
        long long T = M;\
        M = A % M;\
        A = T;\
        T = Y;\
        Y = X - Q * Y;\
        X = T;\
    }\
    if (X < 0)\
    {\
        X += M0;\
    }\
    if (A != 1) return -1;\
    return X; }()

#endif // MODULARINVERSE_HPP