#ifndef GF_P_HPP
#define GF_P_HPP

#define __R_GF_P_REDUFUNCTION__(A, B)[&]() {\
    long long VAL = A % P;\
    return VAL < 0 ? VAL + P : VAL; }()
#define __R_GF_P_ADD_FUNCTION__(A, B, P)[&]() {\
    long long RES = A + B;\
    if (RES >= P) RES -= P;\
    return RES; }()
#define __R_GF_P_SUB_FUNCTION__(A, B, P)[&]() {\
    long long RES = A - B;\
    if (RES < 0) RES += P;\
    return RES; }()
#define __R_GF_P_MUL_FUNCTION__(A, B, P)[&]() {\
    unsigned __int128 PROD = static_cast<unsigned __int128>(A) * B;\
    return static_cast<long long>(PROD % P); }()
#define __R_GF_P_INV_FUNCTION__(A, P)[&]() {\
    long long M0 = P;\
    long long Y = 0, X = 1;\
    if (P == 1) return 0;\
    while (A > 1)\
    {\
        long long Q = A / P;\
        long long T = P;\
        P = A % P;\
        A = T;\
        T = Y;\
        Y = X - Q * Y;\
        X = T;\
    }\
    if (X < 0) X += M0;\
    return X; }()
#define __R_GF_P_DIV_FUNCTION__(A, B, P)[&]() {\
    long long B_INV = __R_GF_P_INV_FUNCTION__(B, P);\
    return __R_GF_P_MUL_FUNCTION__(A, B_INV, P); }()
#define __R_GF_P_POW_FUNCTION__(BASE, EXP, P)[&]() {\
    long long RES = 1;\
    BASE = __R_GF_P_REDUFUNCTION__(BASE, P);\
    while (EXP > 0)\
    {\
        if (EXP & 1) RES = __R_GF_P_MUL_FUNCTION__(RES, BASE, P);\
        BASE = __R_GF_P_MUL_FUNCTION__(BASE, BASE, P);\
        EXP >>= 1;\
    }\
    return RES; }()

#endif // GF_P_HPP