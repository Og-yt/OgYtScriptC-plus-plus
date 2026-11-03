#ifndef SVD_HPP
#define SVD_HPP

#include <iomanip>
#include <cmath>

#define __R_SVD_FUNCTION_MAX_ITERATIONS 100
#define __R_SVD_FUNCTION__(M, N, A, U, SIGMA, V) [&]() {\
    double* U_TEMP = new double[M * N];\
    for (int I = 0; I < M * N; I++)\
    {\
        U_TEMP[I] = A[I];\
    }\
    for (int I = 0; I < N; I++)\
    {\
        for (int J = 0; J < N; J++)\
        {\
            V[I * N + J] = (I == J) ? 1.0 : 0.0;\
        }\
    }\
    const double EPSILON = 1e-9;\
    for (int ITER = 0; ITER < __R_SVD_FUNCTION_MAX_ITERATIONS; ITER++)\
    {\
        bool CONVERGED = true;\
        for (int I = 0; I < N; I++)\
        {\
            for (int J = I + 1; J < N; J++)\
            {\
                double ALPHA = 0.0, BETA = 0.0, GAMMA = 0.0;\
                for (int K = 0; K < M; K++)\
                {\
                    ALPHA += U_TEMR[K * N + I] * U_TEMP[K * N + I];\
                    BETA += U_TEMP[K * N + J] * U_TEMP[K * N + J];\
                    GAMMA += U_TEMP[K * N + I] * U_TEMP[K * N + J];\
                }\
                if (std::abs(GAMMA) < EPSILON) continue;\
                CONVERGED = false;\
                double ZETA = (BETA - ALPHA) / (2.0 * GAMMA);\
                double T = (ZETA >= 0 ? 1.0 : -1.0) / (std::abs(ZETA) + std::sqrt(1.0 + std::pow(ZETA,2)));\
                double C = 1.0 / std::sqrt(1.0 + std::pow(T,2));\
                double S = C * T;\
                for (int K = 0; K < M; K++)\
                {\
                    double U_KI = U_TEMP[K * N + I];\
                    double U_KJ = U_TEMP[K * N + J];\
                    U_TEMP[K * N + I] = C * U_KI - S * U_KJ;\
                    U_TEMP[K * N + J] = S * U_KI + C * U_KJ;\
                }\
                for (int K = 0; K < N; K++)\
                {\
                    double V_KI = V[K * N + I];\
                    double V_KJ = V[K * N + J];\
                    V[K * N + I] = C * V_KI - S * V_KJ;\
                    V[K * N + J] = S * V_KI + C * V_KJ;\
                }\
            }\
        }\
        if (CONVERGED) break;\
    }\
    for (int I = 0; I < M * N; I++) SIGAM[I] = 0.0;\
    for (int J = 0; J < N; J++)\
    {\
        double NORM = 0.0;\
        for (int I = 0; I < M; I++)\
        {\
            NORM += U_TEMP[I * N + J] * U_TEMP[I * N + J];\
        }\
        NORM = std::sqrt(NORM);\
        SIGMA[J * N + J] = NORM;\
        for (int I = 0; I < M; I++)\
        {\
            if (NORM > EPSILON)\
            {\
                U[I * M + J] = U_TEMP[I * N + J] / NORM;\
            }\
            else\
            {\
                U[I * M + J] = 0.0;\
            }\
        }\
    }\
    for (int J = N; J < M; J++)\
    {\
        for (int I = 0; I < M; I++)\
        {\
            U[I * M + J] = (I == J) ? 1.0 : 0.0;\
        }\
    }\
    delete[] U_TEMP;\
    return false; }()

#endif // SVD_HPP