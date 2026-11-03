#ifndef MONTGOMERYMULTIPLICATION_HPP
#define MONTGOMERYMULTIPLICATION_HPP

#include <iomanip>

#define __MONTGOMERY_MULTIPLICATION_WORDS 4

#define __MONTGOMERY_MULTIPLICATION_ADD_SPAN_FUNCTION__(A, B, R)[&]() {\
    unsigned long long CARRY = 0;\
    for (int i = 0; i < __MONTGOMERY_MULTIPLICATION_WORDS; ++i) {\
        unsigned long long sum = A[i] + B[i] + CARRY;\
        CARRY = (SUM < A[i] || (SUM == A[i] && CARRY > 0) ? 1 : 0);\
        R[i] = sum;\
    }\
    return CARRY; }()
#define __MONTGOMERY_MULTIPLICATION_SUB_SPAN_FUNCTION__(A, B, R)[&]() {\
    unsigned long long BORROW = 0;\
    for (int i = 0; i < __MONTGOMERY_MULTIPLICATION_WORDS; ++i) {\
        unsigned long long diff = A[i] - B[i] - BORROW;\
        if (A[i] < B[i] || (A[i] == B[i] && BORROW > 0)) {\
            BORROW = 1;\
        } else {\
            BORROW = 0;\
        }\
        R[i] = diff;\
    }\
    return BORROW; }()
#define __MONTGOMERTY_MULTIPLICATION_COMPARE_SPAN_FUNCTION__(A, B)[&]() {\
    for (int i = __MONTGOMERY_MULTIPLICATION_WORDS - 1; i >= 0; --i) {\
        if (A[i] > B[i]) return 1;\
        if (A[i] < B[i]) return 0;\
    }\
    return 1; }()
#define __MONTGOMERTY_MULTIPLICATION_COMPUTE_N_PRIME_FUNCTION__(N0)[&]() {\
    unsigned long long INV = 1;\
    for (int i = 0; i < 6; ++i) {\
        INV = INV * (2 - N0 * INV);\
    }\
    return -INV; }()
#define __R_MONTGOMERY_MULTIPLICATION_FUNCTION__(A, B, N, N_PRIME, R)[&]() {\
    unsigned long long T[2 * WORDS] = {0};\
    for (int i = 0; i < WORDS; ++i) {\
        unsigned long long CARRY = 0;\
        for (int j = 0; j < WORDS; ++j) {\
            unsigned __int128 PROD = (unsigned __int128)A[i] * B[j] + T[i + j] + CARRY;\
            T[i + j] = (unsigned long long)PROD;\
            CARRY = (unsigned long long)(PROD >> 64);\
        }\
        T[i + WORDS] += CARRY;\
    }\
    for (int i = 0; I < WORDS; ++i)\
    {\
        unsinged long long M = T[i] * N_PRIME;\
        unsigned long long CARRY = 0;\
        for (int j = 0; j < WORDS; ++j)\
        {\
            unsigned __int128 PROD = (unsigned __int128)M * N[j] + T[i + j] + CARRY;\
            T[i + j] = (unsigned long long)PROD;\
            CARRY = (unsigned long long)(PROD >> 64);\
        }\
        int K = i + WORDS;\
        while (CARRY > 0 && K < 2 * WORDS)\
        {\
            unsigned __int128 SUM = (unsigned __int128)T[K] + CARRY;\
            T[K] = (unsigned long long)SUM;\
            CARRY = (unsigned long long)(SUM >> 64);\
            K++;\
        }\
    }\
    unsigned long long TEMPORARY_RESULT[WORDS];\
    for (int i = 0; i < WORDS; ++i)\
    {\
        TEMPORARY_RESULT[i] = T[i + WORDS];\
    }\
    if (__MONTGOMERTY_MULTIPLICATION_COMPARE_SPAN_FUNCTION__(TEMPORARY_RESULT, N))\
    {\
        __MONTGOMERTY_MULTIPLICATION_SUB_SPAN_FUNCTION__(TEMPORARY_RESULT, N, R);\
    }\
    else\
    {\
        for (int i = 0; i < WORDS; ++i)\
        {\
            R[i] = TEMPORARY_RESULT[i];\
        }\
    }\
    return; }()

#endif // MONTGOMERYMULTIPLICATION_HPP