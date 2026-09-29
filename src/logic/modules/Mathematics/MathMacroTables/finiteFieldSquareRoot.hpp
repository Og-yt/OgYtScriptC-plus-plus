#ifndef FINITEFIELDSQUAREROOT_HPP
#define FINITEFIELDSQUAREROOT_HPP

#include <cmath>

#define __FFSR_POWER_MOD_FUNCTION__(BASE, EXP, MOD)[&]() {\
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
#define __R_FINITE_FIELD_SQUARE_ROOT_FUNCTION__(A, P)[&]() {\
    A = (A % P + P) % P;\
    if (A == 0) return 0;\
    if (P == 2) return A;\
    if (__FFSR_POWER_MOD_FUNCTION__(A, (P - 1) / 2, P) != 1)\
    {\
        return -1;\
    }\
    if (P % 4 == 3)\
    {\
        return __FFSR_POWER_MOD_FUNCTION__(A, (P + 1) / 4, P);\
    }\
    long long Q = P - 1;\
    long long S = 0;\
    while (Q % 2 == 0)\
    {\
        Q /= 2;\
        S++;\
    }\
    long long Z = 2;\
    while (__FFSR_POWER_MOD_FUNCTION__(Z, (P - 1) / 2, P) == 1)\
    {\
        Z++;\
    }\
    long long M = S;\
    long long C = __FFSR_POWER_MOD_FUNCTION__(Z, Q, P);\
    long long T = __FFSR_POWER_MOD_FUNCTION__(A, Q, P);\
    long long R = __FFSR_POWER_MOD_FUNCTION__(A, (Q + 1) / 2, P);\
    while (T != 1)\
    {\
        long long I = 0;\
        long long TEMP = T;\
        while (TEMP != 1 && I < M)\
        {\
            TEMP = (__int128)TEMP * TEMP % P;\
            I++;\
        }\
        if (I == M)\
        {\
            return -1;\
        }\
        long long EXPONENT = 1ULL << (M - I - 1);\
        long long B = __FFSR_POWER_MOD_FUNCTION__(C, EXPONENT, P);\
        R = (__int128)R * B % P;\
        T = (__int128)T * std::pow(B % P,2);\
        C = (__int128)B * B % P;\
        M = I;\
    }\
    return R; }()

#endif // FINITEFIELDSQUAREROOT_HPP