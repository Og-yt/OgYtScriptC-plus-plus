#ifndef POINTEXPANSION_HPP
#define POINTEXPANSION_HPP

#include <cmath>
#include "../../../ErrorLogic.hpp"

#define __POINT_EXPANSION_LINE
#define __POINT_EXPANSION_RESULT
#define __POINT_EXPANSION_BUFFER

struct __POINT_EXPANSION_POINT
{
    long long X;
    long long Y;
    bool IS_INFINITY;
};

struct __POINT_EXPANSION_COMPRESSED_POINT
{
    long long X;
    long long Y;
    bool IS_INFINITY;
};

#define __POINT_EXPANSION_POWER_MODULAR_FUNCTION__(BASE, EXP, MOD)[&]() {\
    long long RESULT = 1;\
    BASE = BASE % MOD;\
    while (EXP > 0) {\
        if (EXP % 2 == 1) {\
            RESULT = (__int128)RESULT * BASE % MOD;\
        }\
        BASE = (__int128)BASE * BASE % MOD;\
        EXP /= 2;\
    }\
    return RESULT; }()
#define __POINT_EXPANSION_FINITE_FIELD_SQUARE_ROOT_FUNCTION__(A, P)[&]() {\
    A = (A % P + P) % P;\
    if (A == 0) return 0;\
    if (P == 2) return A;\
    if (__POINT_EXPANSION_POWER_MODULAR_FUNCTION__(A, (P - 1) / 2, P) != 1) return -1;\
    if (P % 4 == 3) return __POINT_EXPANSION_POWER_MODULAR_FUNCTION__(A, (P + 1) / 4, P);\
    long long Q = P - 1;\
    long long S = 0;\
    while (Q % 2 == 0) {\
        Q /= 2;\
        S++;\
    }\
    long long Z = 2;\
    while (__POINT_EXPANSION_POWER_MODULAR_FUNCTION__(Z, (P - 1) / 2, P) == 1) {\
        Z++;\
    }\
    long long M = S;\
    long long C = __POINT_EXPANSION_POWER_MODULAR_FUNCTION__(Z, Q, P);\
    long long T = __POINT_EXPANSION_POWER_MODULAR_FUNCTION__(A, Q, P);\
    long long R = __POINT_EXPANSION_POWER_MODULAR_FUNCTION__(A, (Q + 1) / 2, P);\
    while (T != 1) {\
        long long I = 0;\
        long long TEMP = T;\
        while (TEMP != 1 && I < M) {\
            TEMP = (__int128)TEMP * TEMP % P;\
            I++;\
        }\
        if (I == M) return -1;\
        long long EXPONENT = 1ULL << (M - I - 1);\
        long long B = __POINT_EXPANSION_POWER_MODULAR_FUNCTION__(C, EXPONENT, P);\
        R = (__int128)R * B % P;\
        T = (__int128)T * B % P * B % P;\
        C = (__int128)B * B % P;\
        M = I;\
    }\
    return R; }()
#define __R_POINT_EXPANSION_FUNCTION__(CP, A, B, P)[&]() {\
    if (CP.IS_INFINITY) return {0, 0, true};\
    CP.X = (CP.X % P + P) % P;\
    long long X3 = ((__int128)std::pow(CP.X,2) % P) * CP.X % P;\
    long long AX = ((__int128)A * CP.X) % P;\
    long long RHS = (X3 + AX + B) % P;\
    RHS = (RHS + P) % P;\
    long long Y = __POINT_EXPANSION_FINITE_FIELD_SQUARE_ROOT_FUNCTION__(RHS, P);\
    if (Y == -1) {\
        __POINT_EXPANSION_RESULT += ErrorLogic::build_msg(__POINT_EXPANSION_LINE, "Expansion Error: Invalid x-coordinate. Point does not exist on the curve.\n");\
        ErrorLogic::highlight_line(__POINT_EXPANSION_BUFFER, __POINT_EXPANSION_LINE);\
        return {0, 0, true};\
    }\
    bool CALCULATED_IS_ODD = (Y % 2 != 0);\
    if (CALCULATED_IS_ODD != CP.IS_ODD) {\
        Y = P - Y; \
    }\
    return {CP.X, Y, false}; }()

#endif // POINTEXPANSION_HPP