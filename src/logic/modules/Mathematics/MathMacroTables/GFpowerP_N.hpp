#ifndef GFPOWERP_N_HPP
#define GFPOWERP_N_HPP

#include <iomanip>

template <long long P, int N>
struct GF_PN_ELEMENT
{
    long long COEFF[N] = {0};
};

template <long long P>
#define __GFPN_MOD(A)[&]() {\
    long long R = A % P;\
    return R < 0 ? R + P : R; }()

template<long long P, int N>
#define __R_GF_PN_ADD_FUNCTION__(A, B)[&]() {\
    GF_PN_ELEMENT<P, N> R;\
    for (int i = 0; i < N; ++i) {\
        long long SUM = A.COEFF[i] + B.COEFF[i];\
        if (SUM >= P) SUM -= P;\
        R.COEFF[i] = SUM;\
    }\
    return R; }()
template <long long P, int N>
#define __R_GF_PN_SUB_FUNCTION__(A, B)[&]() {\
    GF_PN_ELEMENT<P, N> R;\
    for (int i = 0; i < N; ++i) {\
        long long DIFF = A.COEFF[i] - B.COEFF[i];\
        if (DIFF < 0) DIFF += P;\
        R.COEFF[i] = DIFF;\
    }\
    return R; }()
template <long long P, int N>
#define __R_GF_PN_MUL_FUNCTION__(A, B, P_POLY)[&]() {\
    long long T[2 * N - 1] = {0};\
    for (int i = 0; i < N; ++i) {\
        for (int j = 0; j < N; ++j) {\
            unsigned __int128 prod = static_cast<unsigned __int128>(A.COEFF[i]) * B.COEFF[j];\
            T[i + j] = __GFPN_MOD(T[i + j] + static_cast<long long>(prod % P));\
        }\
    }\
    for (int i = 2 * N - 2; i >= N; --i) {\
        if (T[i] == 0) continue;\
        long long LEADING_COEFF = T[i];\
        for (int j = 0; j < N; ++j) {\
            long long SUB_VAL = __GFPN_MOD(LEADING_COEFF * P_POLY[j]);\
            int TARGET_IDX = i - N + j;\
            T[TARGET_IDX] = __GFPN_MOD(T[TARGET_IDX] - SUB_VAL);\
        }\
        T[i] = 0;\
    }\
    GF_PN_ELEMENT<P, N> R;\
    for (int i = 0; i < N; ++i) {\
        R.COEFF[i] = T[i];\
    }\
    return R; }()

#endif // GFPOWERP_N_HPP