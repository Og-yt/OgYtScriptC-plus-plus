#ifndef FINITEFIELDADDITION_HPP
#define FINITEFIELDADDITION_HPP

#define __FFA_GF_MAX_N 16

struct FINITE_FIELD_ELEMENT
{
    long long COEFF[__FFA_GF_MAX_N] = {0};
};

#define __R_FINITE_FIELD_ADDITION_FUNCTION__(A, B, RES, N, P)[&]() {\
    if (P == 2)\
    {\
        for (int i = 0; i < n; ++i)\
        {\
            RES.COEFF[i] = A.COEFF[i] ^ B.COEFF[i];\
        }\
    }\
    else\
    {\
        for (int i = 0; i < n; ++i)\
        {\
            long long SUM = A.COEFF[i] + B.COEFF[i];\
            if (SUM >= P)\
            {\
                SUM -= P;\
            }\
            RES.COEFF[i] = SUM;\
        }\
    }\
    return RES; }()

#endif // FINITEFIELDADDITION_HPP