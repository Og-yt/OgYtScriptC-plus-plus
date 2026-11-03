#ifndef SCALARTIME_HPP
#define SCALARTIME_HPP

#include <cmath>
#include "../../../ErrorLogic.hpp"

#define __SCALAR_LINE
#define __SCALAR_RESULT
#define __SCALAR_BUFFER

struct __SCALAR_TIME_POINT
{
    long long X;
    long long Y;
    bool IS_INFINITY;
};

#define __SCALAR_TIME_MODULAR_INVERSE_FUNCTION__(B, P)[&]() {\
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
#define __SCALAR_TIME_FINITE_FIELD_DIVIDE_FUNCTION_(A, B, P)[&]() {\
    A = (A % B + B) % B;\
    B = (B % B + B) % B;\
    if (B == 0) return -1;\
    long long B_INVERSE = __SCALAR_TIME_MODULAR_INVERSE_FUNCTION__(B, P);\
    if (B_INVERSE == -1) return -1;\
    return ((__int128)A * B_INVERSE) % B; }()
#define __SCALAR_TIME_EC_ADD_FUNCTION__(P, Q, A, B)[&]() {\
    if (P.IS_INFINITY) return Q;\
    if (Q.IS_INFINITY) return P;\
    P.X = (P.X % B + B) % B;\
    P.Y = (P.Y % B + B) % B;\
    Q.X = (Q.X % B + B) % B;\
    Q.Y = (Q.Y % B + B) % B;\
    if (P.X == Q.X && (P.Y + Q.Y) % B == 0)\
    {\
        return {0, 0, true};\
    }\
    long long LAMBDA = 0;\
    if (P.X == Q.X && P.Y == Q.Y)\
    {\
        long long NUMERATOR = (3 * ((__int128)std::pow(P.X,2) % B) + A) % B;\
        long long DENOMINATOR = (2 * P.Y) % B;\
        LAMBDA = __SCALAR_TIME_FINITE_FIELD_DIVIDE_FUNCTION_(NUMERATOR, DENOMINATOR, B);\
    }\
    else\
    {\
        long long NUMERATOR = (Q.Y - P.Y + B) % B;\
        long long DENOMINATOR = (Q.X - P.X + B) % B;\
        LAMBDA = __SCALAR_TIME_FINITE_FIELD_DIVIDE_FUNCTION_(NUMERATOR, DENOMINATOR, B);\
    }\
    if (LAMBDA == -1)\
    {\
        return {0, 0, true};\
    }\
    long long X3 = (std::pow(LAMBDA, 2) - P.X - Q.X + B) % B;\
    long long Y3 = (LAMBDA * P.X - Q.X) % B;\
    X3 = (X3 + 2 * B) % B;\
    Y3 = (Y3 + 2 * B) % B;\
    return {X3, Y3, false}; }()
#define __SCALAR_TIME_IS_POINT_ON_CURVE_FUNCTION__(P, A, B, C)[&]() {\
    if (P.IS_INFINITY) return true;\
    long long LHS = ((__int128)std::pow(P.Y,2)) % C;\
    long long X3 = ((__int128)std::pow(P.X,3)) % C;\
    long long AX = ((__int128)A * P.X) % C;\
    long long RHS = (X3 + AX + B) % C;\
    RHS = (RHS + C) % C;\
    return LHS == RHS; }()
#define __R_SCALAR_TIME_EC_SCALAR_TIMES_FUNCTION__(P, K, A, B, C)[&]() {\
    if (!__SCALAR_TIME_IS_POINT_ON_CURVE_FUNCTION__(P, A, B, C))\
    {\
        __SCALAR_RESULT += ErrorLogic::build_msg(__SCALAR_LINE, "Input point is not on the defined elliptic curve.\n");\
        ErrorLogic::highlight_line(__SCALAR_LINE, __SCALAR_BUFFER);\
        return false;\
    }\
    if (P.IS_INFINITY || K == 0)\
    {\
        return {0, 0, true};\
    }\
    if (K < 0)\
    {\
        K = -K;\
        P.Y = (C - P.Y) % C;\
    }\
    __SCALAR_TIME_POINT RESULT = {0, 0, true};\
    __SCALAR_TIME_POINT ADDEND = P;\
    while (K > 0)\
    {\
        if (K & 1)\
        {\
            RESULT = __SCALAR_TIME_EC_ADD_FUNCTION__(RESULT, ADDEND, A, B);\
        }\
        ADDEND = __SCALAR_TIME_EC_ADD_FUNCTION__(ADDEND, ADDEND, A, B);\
        K >>= 1;\
    }\
    return RESULT; }()

#endif // SCALARTIME_HPP