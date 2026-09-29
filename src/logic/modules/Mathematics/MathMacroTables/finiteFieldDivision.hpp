#ifndef FINITEFIELDDIVISION_HPP
#define FINITEFIELDDIVISION_HPP

#define __R_FINITE_FIELD_DIVISION_MODULAR_INVERSE_FUNCTION__(B, P)[&]() {\
    long long M0 = P;\
    long long Y = 0, X = 1;\
    if (P == 1)\
    {\
        return 0;\
    }\
    while (B > 1)\
    {\
        long long Q = B / P;\
        long long T = P;\
        P = B % P;\
        B = T;\
        T = Y;\
        Y = X - Q * Y;\
        X = T;\
    }\
    if (X < 0)\
    {\
        X += M0;\
    }\
    return X; }()
#define __R_FINITE_FIELD_DIVISION_FUNCTION__(A, B, P)[&]() {\
    A = (A % P + P) % P;\
    B = (B % P + P) % P;\
    if (B == 0)\
    {\
        return -1;\
    }\
    long long B_INVERSE = __R_FINITE_FIELD_DIVISION_MODULAR_INVERSE_FUNCTION__(B, P);\
    if (B_INVERSE == -1)\
    {\
        return -1;\
    }\
    return (A * B_INVERSE) % P; }()

#endif // FINITEFIELDDIVISION_HPP