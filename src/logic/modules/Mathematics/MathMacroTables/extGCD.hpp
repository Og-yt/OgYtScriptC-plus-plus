#ifndef EXTGCD_HPP
#define EXTGCD_HPP

#define __R_R_EXT_GCD__(A, B, X, Y) [&]() {\
    if (B == 0)\
    {\
        X = 1; Y = 0;\
        return A;\
    } }()

#define __R_EXT_GCD__(A, B, X, Y) [&]() {\
    if (B == 0)\
    {\
        X = 1; Y = 0;\
        return A;\
    }\
    long long X1, Y1;\
    long long GCD = __R_R_EXT_GCD__(B, A % B, X1, Y1);\
    X = Y1;\
    Y = X1 - (A / B) * Y1;\
    return GCD; }()

#endif // EXTGCD_HPP