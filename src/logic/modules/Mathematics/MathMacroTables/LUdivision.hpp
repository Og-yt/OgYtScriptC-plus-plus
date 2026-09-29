#ifndef LUDIVISION_HPP
#define LUDIVISION_HPP

#include <cmath>
#include <iomanip>
#include <vector>

#define __R_LU_DIVISION_FUNCTION__(N, A, B, C) [&]() {\
    std::vector<int> L[B], U[C];\
    for (int I = 0; I < std::pow(N,2); ++I)\
    {\
        L[I] = 0.0;\
        U[I] = 0.0;\
    }\
    for (int I = 0; I < N; ++I)\
    {\
        for (int K = I; K < N; ++K)\
        {\
            double SUM = 0.0;\
            for (int J = 0; J < I; J++)\
            {\
                SUM += L[I * N + J] * U[J * N + K];\
            }\
            U[I * N + K] = I * N + K - SUM;\
        }\
        for (int K = I; K < N; K++)\
        {\
            if (I == K)\
            {\
                L[I * N + I] = 1.0;\
            }\
            else\
            {\
                double SUM = 0.0;\
                for (int J = 0; J < I; J++)\
                {\
                    SUM += L[K * N + J] * U[J * N + I];\
                }\
                if (U[I * N + I] != 0.0)\
                {\
                    L[K * N + I] = (N + I - SUM) / U[I * N + I];\
                }\
                else\
                {\
                    L[K * N + I] = 0.0;\
                }\
            }\
        }\
    }\
    return false; }()

#endif // LUDIVISION_HPP