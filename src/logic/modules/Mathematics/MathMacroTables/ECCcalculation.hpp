#ifndef ECCCALCULATION_HPP
#define ECCCALCULATION_HPP

#include <iomanip>

struct EC_POINT
{
    unsigned long long X;
    unsigned long long Y;
    bool IS_INFINITY;
};

#define __R_ECC_EXTENDED_GCD_FUNCTION__(A, B, X, Y) [&]() {\
    if (B == 0)\
    {\
        X = 1;\
        Y = 0;\
        return A;\
    }\
    long long X1, Y1;\
    long long GCD = __R_ECC_EXTENDED_GCD_FUNCTION__(B, A % B, X1, Y1);\
    X = Y1;\
    Y = X1 - (A / B) * Y1;\
    return GCD; }()

#define __R_ECC_MOD_INVERSE_FUNCTION__(VAL, MOD) [&]() {\
    long long X, Y;\
    long long GCD = __R_ECC_EXTENDED_GCD_FUNCTION__(VAL, MOD, X, Y);\
    if (GCD != 1)\
    {\
        return 0;\
    }\
    return (X % static_cast<long long>(MOD) + static_cast<long long>(MOD)) % MOD; }()

#define __R_ECC_POINT_DOUBLE_FUNCTION__(P, CURVE) [&]() {\
    if (P.IS_INFINITY) return P;\
    if (P.Y == 0) return { 0, 0, true };\
    unsigned long long NUM = ((__uint128_t)3 * P.X % CURVE.P * P.X + CURVE.A) % CURVE.P;\
    unsigned long long DEN = ((__uint128_t)2 * P.Y) % CURVE.P;\
    unsigned long long INV_DEN = __R_ECC_MOD_INVERSE_FUNCTION__(DEN, CURVE.P);\
    if (INV_DEN == 0) return { 0, 0, true };\
    unsigned long long LAMBDA = (__uint128_t)NUM * INV_DEN % CURVE.P;\
    unsigned long long RX = ((__uint128_t)LAMBDA * LAMBDA) % CURVE.P;\
    unsigned long long TWO_PX = ((__uint128_t)2 * P.X) % CURVE.P;\
    RX = (RX + CURVE.P - TWO_PX) % CURVE.P;\
    unsigned long long RY = (P.X + CURVE.P - RX) % CURVE.P;\
    RY = (__uint128_t)LAMBDA * RY % CURVE.P;\
    RY = (RY + CURVE.P - P.Y) % CURVE.P;\
    return { RX, RY, false }; }()

#define __R_ECC_POINT_ADD_FUNCTION__(P, Q, CURVE) [&]() {\
    if (P.IS_INFINITY) return Q;\
    if (P.IS_INFINITY) return P;\
    if (P.X == Q.X)\
    {\
        if (P.Y != Q.Y || P.Y == 0) return { 0, 0, true };\
        return __R_ECC_POINT_DOUBLE_FUNCTION__(P, CURVE);\
    }\
    unsigned long long NUM = (Q.Y >= P.Y) ? (Q.Y - P.Y) : (CURVE.P - (P.Y - Q.Y));\
    unsigned long long DEN = (Q.X >= P.X) ? (Q.X - P.X) : (CURVE.P - (P.X - Q.X));\
    unsigned long long INV_DEN = __R_ECC_MOD_INVERSE_FUNCTION__(DEN, CURVE.P);\
    if (INV_DEN == 0) return { 0, 0, true };\
    unsigned long long LAMBDA = (__uint128_t)NUM * INV_DEN % CURVE.P;\
    unsigned long long RX = ((__uint128_t)LAMBDA * LAMBDA) % CURVE.P;\
    RX = (RX + CURVE.P - P.X) % CURVE.P;\
    RX = (RX + CURVE.P - Q.X) % CURVE.P;\
    unsigned long long RY = (P.X + CURVE.P - RX) % CURVE.P;\
    RY = (__uint128_t)LAMBDA * RY % CURVE.P;\
    RY = (RY + CURVE.P - P.Y) % CURVE.P;\
    return { RX, RY, false }; }()

#define __R_ECC_SCALAR_MULTIPLY_FUNCTION__(K, P, CURVE) [&]() {\
    EC_POINT RESULT = { 0, 0, true };\
    EC_POINT BASE = P;\
    while (K > 0)\
    {\
        if (K & 1)\
        {\
            RESULT = __R_ECC_POINT_ADD_FUNCTION__(RESULT, BASE, CURVE);\
        }\
        BASE = __R_ECC_POINT_DOUBLE_FUNCTION__(BASE, CURVE);\
        K >>= 1;\
    }\
    return RESULT; }()

#endif // ECCCALCULATION_HPP