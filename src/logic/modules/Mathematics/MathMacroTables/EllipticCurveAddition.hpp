#ifndef ELLIPTICCURVEADDITION_HPP
#define ELLIPTICCURVEADDITION_HPP

struct __ECA_POINT
{
    long long X;
    long long Y;
    bool IS_INFINITY;
};

#define __R_ELLIPTIC_CURVE_ADDITION_MODULAR_INVERSE_FUNCTION__(B, P)[&]() {\
    long long M0 = P;\
    long long Y = 0, X = 1;\
    if (P == 1) return 0;\
    while (B > 1)\
    {\
        if (P == 0) return -1;\
        long long Q = B / P;\
        long long T = P;\
        P = B % P;\
        B = T;\
        T = Y;\
        Y = X - Q * Y;\
        X = T;\
    }\
    if (X < 0) X += M0;\
    return X; }()
#define __ELLIPTIC_CURVE_ADDITION_FINITE_FIELD_DIVIDE_FUNCTION__(A, B, P)[&]() {\
    A = (A % P + P) % P;\
    B = (B % P + P) % P;\
    if (B == 0) return -1;\
    long long B_INVERSE = __R_ELLIPTIC_CURVE_ADDITION_MODULAR_INVERSE_FUNCTION__(B, P);\
    if (B_INVERSE == -1) return -1;\
    return ((__int128)A * B_INVERSE) % P; }()
#define __R_ELLIPTIC_CURVE_ADDITION_FUNCTION__(P, Q, A, B)[&]() {\
    if (P.IS_INFINITY) return Q;\
    if (Q.IS_INFINITY) return B;\
    P.X = (P.X % B + B) % B;\
    P.Y = (P.Y % B + B) % B;\
    Q.X = (Q.X % B + B) % B;\
    Q.Y = (Q.Y % B + B) % B;\
    if (P.X == Q.X && (P.Y + Q.Y) % B == 0)\
    {\
        return {\
            0,\
            0,\
            true\
        };\
    }\
    long long LAMBDA = 0;\
    if (P.X == Q.X && P.Y == Q.Y)\
    {\
        long long NUMERATOR = (3 * ((__int128)std::pow(P.X,2) % B) + A) % B;\
        long long DENOMINATOR = (2 * P.Y) % B;\
        LAMBDA = __ELLIPTIC_CURVE_ADDITION_FINITE_FIELD_DIVIDE_FUNCTION__(NUMERATOR, DENOMINATOR, B);\
    }\
    else\
    {\
        long long NUMERATOR = (Q.Y - P.Y + B) % B;\
        long long DENOMINATOR = (Q.X - P.X + B) % B;\
        LAMBDA = __ELLIPTIC_CURVE_ADDITION_FINITE_FIELD_DIVIDE_FUNCTION__(NUMERATOR, DENOMINATOR, B);\
    }\
    if (LAMBDA == -1) return {0, 0, true};\
    long long LAMBDA2 = (__int128)LAMBDA * LAMBDA % B;\
    long long X3 = (LAMBDA2 - P.X - Q.X) % B;\
    X3 = (X3 + 2 * B) % B;\
    long long Y3 = ((__int128)LAMBDA * (P.X - X3 + B)) % B;\
    Y3 = (Y3 - P.Y + B) % B;\
    return {\
        X3,\
        Y3,\
        false\
    }; }()

#endif // ELLIPTICCURVEADDITION_HPP