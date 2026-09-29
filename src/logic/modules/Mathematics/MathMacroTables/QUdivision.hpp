#ifndef QUDIVISION_HPP
#define QUDIVISION_HPP

#include <cmath>
#include <iomanip>

#define __R_QU_DIVISION_FUNCTION__(N, A, Q, R) [&]() {\
    for (int I = 0; I < N; ++I)\
    {\
        Q[I] = 0.0;\
        R[I] = 0.0;\
    }\
    double* V = new double[std::pow(N,2)];\
    for (int I = 0; I < std::pow(N,2); ++I)\
    {\
        V[I] = A[I];\
    }\
    for (int I = 0; I < N; I++)\
    {\
        double NORM = 0.0;\
        for (int ROW = 0; ROW < N; ROW++)\
        {\
            NORM += V[ROW * N + I] * V[ROW * N + I];\
        }\
        NORM = std::sqrt(NORM);\
        R[I * N + I] = NORM;\
        for (int ROW = 0; ROW < N; ROW++)\
        {\
            if (NORM > 1e-9)\
            {\
                Q[ROW * N + I] = V[ROW * N + I] / NORM;\
            }\
            else\
            {\
                Q[ROW * N + I] = 0.0;\
            }\
        }\
        for (int J = I + 1; J < N; J++)\
        {\
            double DOTPRODUCT = 0.0;\
            for (int ROW = 0; ROW < N; ROW++)\
            {\
                DOTPRODUCT += Q[ROW * N + I] * V[ROW * N + J];\
            }\
            R[I * N + J] = DOTPRODUCT;\
            for (int ROW = 0; ROW < N; ROW++)\
            {\
                V[ROW * N + J] -= DOTPRODUCT * Q[ROW * N + I];\
            }\
        }\
    }\
    delete[] V;\
    return false; }()

#endif // QUDIVISION_HPP