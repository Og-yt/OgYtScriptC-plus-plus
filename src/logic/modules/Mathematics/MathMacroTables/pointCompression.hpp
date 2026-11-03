#ifndef POINTCOMPRESSION_HPP
#define POINTCOMPRESSION_HPP

#include <cmath>
#include "../../../ErrorLogic.hpp"

#define __POINT_COMPRESSION_LINE
#define __POINT_COMPRESSION_RESULT
#define __POINT_COMPRESSION_BUFFER

struct __POINT_COMPRESSION_POINT
{
    long long X;
    long long Y;
    bool IS_INFINITY;
};

struct __POINT_COMPRESSED_POINT
{
    long long X;
    bool IS_ODD;
    bool IS_INFINITY;
};

#define __POINT_COMPRESSION_POWER_MODULAR_FUNCTION__(BASE, EXP, MOD)[&]() {\
    long long RESULT = 1;\
    BASE = BASE % MOD;\
    while (EXP > 0)\
    {\
        if (EXP % 2 == 1)\
        {\
            RESULT = (__int128)RESULT * BASE % MOD;\
        }\
        BASE = (__int128)BASE * BASE % MOD;\
        EXP /= 2;\
    }\
    return RESULT; }()
#define __POINT_COMPRESSION_FINITE_FIELD_SQUARE_ROOT_FUNCTION__(A, P)[&]() {\
    A = (A % P + P) % P;\
    if (A == 0) return 0;\
    if (P == 2) return A;\
    if (__POINT_COMPRESSION_POWER_MODULAR_FUNCTION__(A, (P - 1) / 2, P) != 1) return -1;\
    if (P % 4 == 3)\
    {\
        return __POINT_COMPRESSION_POWER_MODULAR_FUNCTION__(A, (P + 1) / 4, P);\
    }\
    long long Q = P - 1;\
    long long S = 0;\
    while (Q % 2 == 0)\
    {\
        Q /= 2;\
        S++;\
    }\
    long long Z = 2;\
    while (__POINT_COMPRESSION_POWER_MODULAR_FUNCTION__(Z, (P - 1) / 2, P) == 1)\
    {\
        Z++;\
    }\
    long long M = S;\
    long long C = __POINT_COMPRESSION_POWER_MODULAR_FUNCTION__(Z, Q, P);\
    long long T = __POINT_COMPRESSION_POWER_MODULAR_FUNCTION__(A, Q, P);\
    long long R = __POINT_COMPRESSION_POWER_MODULAR_FUNCTION__(A, (Q + 1) / 2, P);\
    while (T != 1)\
    {\
        long long I = 0;\
        long long TEMP = T;\
        while (TEMP != 1 && I < M)\
        {\
            TEMP = (__int128)std::pow(TEMP,2) % P;\
            I++;\
        }\
        if (I == M)\
        {\
            return -1;\
        }\
        long long EXPONENT = 1ULL << (M - I - 1);\
        long long B = __POINT_COMPRESSION_POWER_MODULAR_FUNCTION__(C, EXPONENT, P);\
        R = (__int128)R * B % P;\
        T = (__int128)T * B % P * B % P;\
        C = (__int128)B * B % P;\
        M = I;\
    }\
    return R; }()
#define __POINT_COMPRESSION_IS_POINT_ON_CURVE_FUNCTION__(P, A, B, C)[&]() {\
    if (P.IS_INFINITY) return true;\
    long long LHS = (__int128)P.Y * P.Y % C;\
    long long X3 = (__int128)P.X * P.X % C;\
    long long AX = (__int128)A * P.X % C;\
    long long RHS = (X3 + AX + B) % C;\
    return LHS == (RHS + C) % C; }()
#define __R_POINT_COMPRESSION_EC_COMPRESS_FUNCTION__(P, A, B, C)[&]() {\
    if (P.IS_INFINITY) return {0, false, true};\
    if (!__POINT_COMPRESSION_IS_POINT_ON_CURVE_FUNCTION__(P, A, B, C)) {\
        __POINT_COMPRESSION_RESUL += ErrorLogic::build_msg(__POINT_COMPRESSION_LINE, "Compression Error: Point is not on the curve.\n");\
        ErrorLogic::highlight_line(__POINT_COMPRESSION_BUFFER, __POINT_COMPRESSION_LINE);\
        return false;\
    }\
    bool IS_ODD = (P.Y % 2 != 0);\
    return {P.X, IS_ODD, false}; }()
#define __R_POINT_COMPRESSION_EC_UNCOMPRESS_FUNCTION__(CP, A, B, P)[&]() {\
    if (CP.IS_INFINITY) return {0, 0, true};\
    long long X3 = (__int128)std::pow(CP.X,2) % C;\
    long long AX = (__int128)A * CP.X % C;\
    long long RHS = (X3 + AX + B) % C;\
    RHS = (RHS + C) % C;\
    long long Y = __POINT_COMPRESSION_FINITE_FIELD_SQUARE_ROOT_FUNCTION__(RHS, C);\
    if (Y == -1) {\
        __POINT_COMPRESSION_RESULT += ErrorLogic::build_msg(__POINT_COMPRESSION_LINE, "Uncompression Error: Invalid x-coordinate for this curve.\n");\
        ErrorLogic::highlight_line(__POINT_COMPRESSION_BUFFER, __POINT_COMPRESSION_LINE);\
        return false;\
    }\
    bool CALCULATED_IS_ODD = (Y % 2 != 0);\
    if (CALCULATED_IS_ODD != CP.IS_ODD) {\
        Y = P - Y;\
    }\
    return {CP.X, Y, false}; }()

#endif // POINTCOMPRESSION_HPP