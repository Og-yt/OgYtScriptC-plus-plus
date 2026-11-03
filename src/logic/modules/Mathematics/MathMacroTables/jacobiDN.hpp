#ifndef JACOBIDN_HPP
#define JACOBIDN_HPP

#include <cmath>

#define __R_JACOBI_DN__(U, M) [&]() {\
    if (M < 0.0 || M > 1.0)\
    {\
        return 0.0;\
    }\
    if (M == 0.0) return 1.0;\
    if (M == 1.0) return 1.0 / std::cosh(U);\
    double A = 1.0;\
    double B = std::sqrt(1.0 - M);\
    double C = std::sqrt(M);\
    double A_ARR[10], C_ARR[10];\
    int N = 0;\
    while (C > 1e-15 && N < 10)\
    {\
        A_ARR[N] = A;\
        C_ARR[N] = C;\
        double NEXT_A = (A + B) / 2.0;\
        double NEXT_B = std::sqrt(A * B);\
        double NEXT_C = (A - B) / 2.0;\
        A = NEXT_A;\
        B = NEXT_B;\
        C = NEXT_C;\
        N++;\
    }\
    double PHI = A * U * std::pow(2.0, N);\
    for (int I = N - 1; I >= 0; I--)\
    {\
        PHI = (PHI + std::asin(C_ARR[I] / A_ARR[I] * std::sin(PHI))) / 2.0;\
    }\
    double SIN_PHI = std::sin(PHI);\
    return std::sqrt(1.0 - M * SIN_PHI * SIN_PHI); }()

#endif // JACOBI_DN