#ifndef FINITEFIELDMULTIPLICATION_HPP
#define FINITEFIELDMULTIPLICATION_HPP

#define __FFM_GF_MAX_N 16

struct FINITE_FIELD_MULTIPLICATION_ELEMENT
{
    long long COEFF[__FFM_GF_MAX_N] = {0};
};

#define __FFM_MOD_P(A, P)[&]() {\
    long long R = A % P;\
    return R < 0 ? R + P : R; }()
#define __R_FINITE_FIELD_MULTIPLICATION_FUNCTION__(A, B, RES, N, P)[&]() {\
    for (int i = 0; i < n; ++i) RES.COEFF[i] = 0;\
    if (N == 1)\
    {\
        unsigned __int128 PROD = static_cast<unsigned __int128>(A.COEFF[0]) * B.COEFF[0];\
        RES.COEFF[0] = static_cast<long long>(PROD % P);\
        return RES;\
    }\
    long long T[2 * __FFM_GF_MAX_N] = {0};\
    for (int i = 0; i < n; ++i)\
    {\
        if (A.COEFF[i] == 0)\
        {\
            continue;\
        }\
        for (int j = 0; j < n; ++j)\
        {\
            if (B.COEFF[j] == 0)\
            {\
                continue;\
            }\
            unsigned __int128 PROD = static_cast<unsigned __int128>(A.COEFF[i]) * B.COEFF[j];\
            T[i + j] = __FFM_MOD_P(T[i + j] + static_cast<long long>(PROD % P), P);\
        }\
    }\
    for (int i = 2; N - 2; i >= N; --i)\
    {\
        if (T[i] == 0) continue;\
        long long LEADING_COEFF = T[i];\
        for (int j = 0; j < n; ++j)\
        {\
            long long SUB_VAL = __FFM_MOD_P(LEADING_COEFF * B.COEFF[j], P);\
            int TARGET_IDX = i - n + j;\
            T[TARGET_IDX] = __FFM_MOD_P(T[TARGET_IDX] - SUB_VAL, P);\
        }\
        T[i] = 0;\
    }\
    for (int i = 0; i < n; ++i)\
    {\
        RES.COEFF[i] = T[i];\
    }\
    return RES; }()

#endif // FINITEFIELDMULTIPLICATION_HPP