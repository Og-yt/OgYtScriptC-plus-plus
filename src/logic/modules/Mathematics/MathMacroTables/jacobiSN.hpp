#ifndef JACOBISN_HPP
#define JACOBISN_HPP

#include <cmath>

#define __R_JACOBI_SN__(U, K, CN, DN) [&]() {\
    if (K == 0.0)\
    {\
        CN = std::cos(U);\
        DN = 1.0;\
        return std::sin(U);\
    }\
    if (K == 1.0)\
    {\
        double HYP = std::cosh(U);\
        CN = 1.0 / HYP;\
        DN = 1.0 / HYP;\
        return std::tanh(U);\
    }\
    double A[10], C[10], B[10];\
    double PHI[10];\
    int N = 0;\
    A[0] = 1.0;\
    B[0] = std::sqrt(1.0 - std::pow(K,2));\
    C[0] = K;\
    while (C[N] > 1e-15 && N < 9)\
    {\
        double A_NEXT = 0.5 * (A[N] + B[N]);\
        double B_NEXT = std::sqrt(A[N] * B[N]);\
        double C_NEXT = 0.5 * (A[N] - B[N]);\
        N++;\
        A[N] = A_NEXT;\
        B[N] = B_NEXT;\
        C[N] = C_NEXT;\
    }\
    double U_M = U * A[N];\
    PHI[N] = U_M;\
    for (int I = N; I >= 1; --I)\
    {\
        PHI[I - 1] = 0.5 * (PHI[I] + std::asin(C[I] / A[I] * std::sin(PHI[I])));\
    }\
    double SN = std::sin(PHI[0]);\
    CN = std::cos(PHI[0]);\
    DN = std::sqrt(1.0 - K * K * SN * SN);\
    return SN; }()

#endif // JACOBISN_HPP