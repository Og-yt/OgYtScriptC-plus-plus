#ifndef MONTGOMERYLADDER_HPP
#define MONTGOMERYLADDER_HPP

#include <cmath>

struct __MONTGOMERY_LADDER_POINT
{
    long long X;
    long long Y;
    bool IS_INFINITY;
};

#define __MONTGOMERY_LADDER_MODULAR_INVERSE_FUNCTION__(B, P) [&]() {\
    long long M0 = P;\
    long long Y = 0, X = 1;\
    if (P == 1) return 0;\
    while (B > 1) {\
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
#define __MONTGOMERY_LADDER_FINITE_FIELD_DIVIDE_FUNCTION__(A, B, P) [&]() {\
    A = (A % P + P) % P;\
    B = (B % P + P) % P;\
    if (B == 0) return -1;\
    long long B_INVERSE = __MONTGOMERY_LADDER_MODULAR_INVERSE_FUNCTION__(B, P);\
    if (B_INVERSE == -1) return -1;\
    return ((__int128)A * B_INVERSE) % P; }()
#define __MONTGOMERY_LADDER_EC_ADD_FUNCTION__(P, Q, A, B) [&]() {\
    if (P.IS_INFINITY) return Q;\
    if (Q.IS_INFINITY) return P;\
    P.X = (P.X % B + B) % B;\
    P.Y = (P.Y % B + B) % B;\
    Q.X = (Q.X % B + B) % B;\
    Q.Y = (Q.Y % B + B) % B;\
    if (P.X == Q.X && (P.Y + Q.Y) % B == 0) {\
        return {0, 0, true};\
    }\
    long long LAMBDA = 0;\
    if (P.X == Q.X && P.Y == Q.Y) {\
        long long NUMERATOR = (3 * ((__int128)std::pow(P.X,2) % B) + A) % B;\
        long long DENOMINATOR = (2 * P.Y) % B;\
        LAMBDA = __MONTGOMERY_LADDER_FINITE_FIELD_DIVIDE_FUNCTION__(NUMERATOR, DENOMINATOR, B);\
    }\
    else\
    {\
        long long NUMERATOR = (Q.Y - P.Y + B) % B;\
        long long DENOMINATOR = (Q.X - P.X + B) % B;\
        LAMBDA = __MONTGOMERY_LADDER_FINITE_FIELD_DIVIDE_FUNCTION__(NUMERATOR, DENOMINATOR, B);\
    }\
    if (LAMBDA == -1) return {0, 0, true};\
    long long X3 = ((__int128)LAMBDA * LAMBDA - P.X - Q.X + B) % B;\
    long long Y3 = ((__int128)LAMBDA * (P.X - X3 + B) - P.Y + B) % B;\
    return {X3, Y3, false}; }()
#define __R_MENTGOMERY_LADDER_FUNCTION__(P, K, A, B)[&]() {\
    if (K == 0) return {0, 0, true};\
    if (K < 0) {\
        K = -K;\
        P.Y = (B - P.Y + B) % B;\
    }\
    __MONTGOMERY_LADDER_POINT R0 = {0, 0, true};\
    __MONTGOMERY_LADDER_POINT R1 = P;\
    long long MSB_POSITION = 63;\
    while (MSB_POSITION >= 0 && !(K & (1ULL << MSB_POSITION))){\
        MSB_POSITION--;\
    }\
    for (int i = MSB_POSITION; i >= 0; i--){\
        long long BIT = (K >> i) & 1;\
        if (BIT == 0) {\
            R1 = __MONTGOMERY_LADDER_EC_ADD_FUNCTION__(R0, R1, A, B);\
            R0 = __MONTGOMERY_LADDER_EC_ADD_FUNCTION__(R0, R0, A, B);\
        }\
        else {\
            R0 = __MONTGOMERY_LADDER_EC_ADD_FUNCTION__(R0, R1, A, B);\
            R1 = __MONTGOMERY_LADDER_EC_ADD_FUNCTION__(R1, R1, A, B);\
        }\
    }\
    return R0; }()

#endif // MONTGOMERYLADDER_HPP