#ifndef ELLIPTICCURVEOPERATORS_HPP
#define ELLIPTICCURVEOPERATORS_HPP

struct ELL_CURVE_OP_EC_POINT
{
    unsigned long long X;
    unsigned long long Y;
    bool IS_INFINITY;
};

struct ELL_CURVE_OP
{
    unsigned long long A;
    unsigned long long B;
    unsigned long long P;
};

#define __R_ELLIPTIC_CURVE_OPERATOR_EXTENDED_GCD_FUNCTION__(A, B, X, Y)[&]() {\
    if (B == 0) {\
        X = 1;\
        Y = 0;\
        return A;\
    }\
    long long X1, Y1;\
    long long GCD = __R_ELLIPTIC_CURVE_OPERATOR_EXTENDED_GCD_FUNCTION__(B, A % B, X1, Y1);\
    X = Y1;\
    Y = X1 - (A / B) * Y1;\
    return GCD; }()

#define __R_ELLIPTIC_CURVE_OPERATOR_MOD_INVERSE_FUNCTION__(VAL, MOD)[&]() {\
    long long X, Y;\
    long long GCD = __R_ELLIPTIC_CURVE_OPERATOR_EXTENDED_GCD_FUNCTION__(static_cast<long long>(VAL % MOD), static_cast<long long>(MOD), X, Y);\
    if (GCD != 1) return 0;\
    return (X % MOD + MOD) % MOD; }()

#define __R_ELLIPTIC_CURVE_OPERATOR_IS_POINT_ON_CURVE_FUNCTION__(PT, CURVE)[&]() {\
    if (PT.IS_INFINITY) return true;\
    unsigned long long LHS = ((__uint128_t)PT.Y * PT.Y) % CURVE.P;\
    unsigned long long RHS = ((__uint128_t)PT.X * PT.X * PT.X + CURVE.A * PT.X + CURVE.B) % CURVE.P;\
    unsigned long long X2 = ((__uint128_t)PT.X * PT.X) % CURVE.P;\
    unsigned long long X3 = ((__uint128_t)X2 * PT.X) % CURVE.P;\
    unsigned long long AX = ((__uint128_t)CURVE.A * PT.X) % CURVE.P;\
    unsigned long long RHS2 = (X3 + AX + CURVE.B) % CURVE.P;\
    return (LHS == RHS2); }()

#define __R_ELLIPTIC_CURVE_OPERATOR_POINT_NEGATIVE_FUNCTION__(PT, CURVE)[&]() {\
    if (PT.IS_INFINITY || PT.Y == 0) return PT;\
    ELL_CURVE_OP_EC_POINT RESULT;\
    RESULT.X = PT.X;\
    RESULT.Y = CURVE.P - PT.Y;\
    RESULT.IS_INFINITY = false;\
    return RESULT; }()

#define __R_ELLIPTIC_CURVE_OPERATOR_POINT_DOUBLE_FUNCTION__(PT, CURVE)[&]() {\
    if (PT.IS_INFINITY || PT.Y == 0) return { 0, 0, true };\
    unsigned long long NUM = ((__uint128_t)3 * PT.X % CURVE.P * PT.X + CURVE.A) % CURVE.P;\
    unsigned long long DEN = ((__uint128_t)2 * PT.Y) % CURVE.P;\
    unsigned long long INV_DEN = __R_ELLIPTIC_CURVE_OPERATOR_MOD_INVERSE_FUNCTION__(DEN, CURVE.P);\
    if (INV_DEN == 0) return { 0, 0, true };\
    unsigned long long LAMBDA = (__uint128_t)NUM * INV_DEN % CURVE.P;\
    unsigned long long RX = ((__uint128_t)LAMBDA * LAMBDA) % CURVE.P;\
    RX = (RX + CURVE.P - ((__uint128_t)2 * PT.X % CURVE.P)) % CURVE.P;\
    unsigned long long RY = (PT.X + CURVE.P - RX) % CURVE.P;\
    RY = (__uint128_t)LAMBDA * RY % CURVE.P;\
    RY = (RY + CURVE.P - PT.Y) % CURVE.P;\
    return { RX, RY, false }; }()

#define __R_ELLIPTIC_CURVE_OPERATOR_POINT_ADD_FUNCTION__(P, Q, CURVE)[&]() {\
    if (P.IS_INFINITY) return Q;\
    if (Q.IS_INFINITY) return P;\
    if (P.X == Q.X) {\
        if (P.Y != Q.Y || P.Y == 0) return { 0, 0, true };\
        return __R_ELLIPTIC_CURVE_OPERATOR_POINT_DOUBLE_FUNCTION__(P, CURVE);\
    }\
    unsigned long long NUM = (Q.Y >= P.Y) ? (Q.Y - P.Y) : (CURVE.P - (P.Y - Q.Y));\
    unsigned long long DEN = (Q.X >= P.X) ? (Q.X - P.X) : (CURVE.P - (P.X - Q.X));\
    unsigned long long INV_DEN = __R_ELLIPTIC_CURVE_OPERATOR_MOD_INVERSE_FUNCTION__(DEN, CURVE.P);\
    if (INV_DEN == 0) return { 0, 0, true };\
    unsigned long long LAMBDA = (__uint128_t)NUM * INV_DEN % CURVE.P;\
    unsigned long long RX = ((__uint128_t)LAMBDA * LAMBDA) % CURVE.P;\
    RX = (RX + CURVE.P - P.X) % CURVE.P;\
    RX = (RX + CURVE.P - Q.X) % CURVE.P;\
    unsigned long long RY = (P.X + CURVE.P - RX) % CURVE.P;\
    RY = (__uint128_t)LAMBDA * RY % CURVE.P;\
    RY = (RY + CURVE.P - P.Y) % CURVE.P;\
    return { RX, RY, false }; }()

#define __R_ELLIPTIC_CURVE_OPERATOR_POINT_SUBTRACT_FUNCTION__(P, Q, CURVE)[&]() {\
    ELL_CURVE_OP_EC_POINT NEG_Q = __R_ELLIPTIC_CURVE_OPERATOR_POINT_NEGATIVE_FUNCTION__(Q, CURVE);\
    return __R_ELLIPTIC_CURVE_OPERATOR_POINT_ADD_FUNCTION__(P, NEG_Q, CURVE); }()

#endif // ELLIPTICCURVEOPERATORS_HPP