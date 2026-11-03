#ifndef RSACALCULATION_HPP
#define RSACALCULATION_HPP

#include <iomanip>

struct RSA_KEY_PAIR
{
    unsigned long long EXPONENT;
    unsigned long long MODULUS;
};

#define __R_RSA_MODULAR_POWER_FUNCTION__(BASE, EXP, MOD) [&]() {\
    unsigned long long RESULT = 1;\
    BASE = BASE % MOD;\
    while (EXP > 0)\
    {\
        if (EXP & 1)\
        {\
            RESULT = (__uint128_t)RESULT * BASE % MOD;\
        }\
        BASE = (__uint128_t)BASE * BASE % MOD;\
        EXP >>= 1;\
    }\
    return RESULT; }()

#define __R_RSA_EXTENDED_GCD_FUNCTION__(A, B, X, Y) [&]() {\
    if (B == 0)\
    {\
        X = 1;\
        Y = 0;\
        return A;\
    }\
    long long X1, Y1;\
    long long GCD = __R_RSA_EXTENDED_GCD_FUNCTION__(B, A % B, X1, Y1);\
    X = Y1;\
    Y = X1 - (A / B) * Y1;\
    return GCD; }()

#define __R_RSA_COMPUTE_MODULAR_INVERSE_FUNCTION__(E, PHI) [&]() {\
    long long X, Y;\
    long long GCD = __R_RSA_EXTENDED_GCD_FUNCTION__(E, PHI, X, Y);\
    if (GCD != 1)\
    {\
        return 0;\
    }\
    return (X % static_cast<long long>(PHI) + static_cast<long long>(PHI)) % PHI; }()

#define __R_RSA_GET_GCD_FUNCTION__(A, B) [&]() {\
    while (B != 0)\
    {\
        unsigned long long TEMP = B;\
        B = A % B;\
        A = TEMP;\
    }\
    return A; }()

#endif // RSACALCULATION_HPP