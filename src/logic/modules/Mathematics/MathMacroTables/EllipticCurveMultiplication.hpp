#ifndef ELLIPTICCURVEMULTIPLICATION_HPP
#define ELLIPTICCURVEMULTIPLICATION_HPP

struct __ECM_POINT
{
    long long X;
    long long Y;
    bool IS_INFINITY;
};

#define __ELLIPTIC_CURVE_MULTIPLICATION_MODULAR_INVERSE_FUNCTION__(B, P)[&]() {\
    long long M0 = P;\
    long long Y = 0, X = 1;\
    if (P == 1) return 0;\
    while (B > 1)\
    {\
        if (P == 0) return -1;\
        long long Q = B / P;\
        long long T = P;\
        P = B % P;\
        B = T;\
        T = Y;\
        Y = X - Q * Y;\
        X = T;\
    }\
    if (X < 0) X += M0;\
    return X; }()
#define __ELLIPTIC_CURVE_MULTIPLICATION_FINITE_FIELD_DIVIDE_FUNCTION__(A, B, P)[&]() {\
    A = (A % P + P) % P;\
    B = (B % P + P) % P;\
    if (B == 0) return -1;\
    long long B_INVERSE = __ELLIPTIC_CURVE_MULTIPLICATION_MODULAR_INVERSE_FUNCTION__(B, P);\
    if (B_INVERSE == -1) return -1;\
    return ((__int128)A * B_INVERSE) % P; }()
#define __R_ELLIPTIC_CURVE_MULTIPLICATION_FUNCTION__(P, K, A, B)[&](){\
    if (P.IS_INFINITY || K == 0)\
    {\
        return {0, 0, true};\
    }\
    if (K < 0)\
    {\
        K = -K;\
        P.Y = (B - P.Y) % B;\
    }\
    __ECM_POINT RESULT = {0, 0, true};\
    __ECM_POINT ADDEND = P;\
    while (K > 0)\
    {\
        if (K & 1)\
        {\
            RESULT = __R_ELLIPTIC_CURVE_ADDITION_FUNCTION__(RESULT, ADDEND, A, B);\
        }\
        ADDEND = __R_ELLIPTIC_CURVE_ADDITION_FUNCTION__(ADDEND, ADDEND, A, B);\
        K >>= 1;\
    }\
    return RESULT; }()

#endif // ELLIPTICCURVEMULTIPLICATION_HPP