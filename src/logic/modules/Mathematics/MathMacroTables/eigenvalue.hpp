#ifndef EIGENVALUE_HPP
#define EIGENVALUE_HPP

#include <cmath>
#include <iomanip>

#define __R_EIGEN_MAX_ITERATIONS 100
#define __FIND_MAX_OFF_DIAGONAL_FUNCTION__(N, A, ROW, COL) [&]() {\
    double MAXVAL = 0.0;\
    ROW = 0;\
    COL = 0;\
    for (int I = 0; I < N; I++)\
    {\
        for (int J = I + 1; J < N; J++)\
        {\
            double VAL = std::abs(A * (I * N + J));\
            if (VAL > MAXVAL)\
            {\
                MAXVAL = VAL;\
                ROW = I;\
                COL = J;\
            }\
        }\
    }\
    return MAXVAL; }()
#define __R_EIGENVALUE_FUNCTION__(N, A, EIGENVALUES) [&]() {\
    const double EPSILON = 1e-9;\
    int P, Q;\
    for (int ITER = 0; ITER < __R_EIGEN_MAX_ITERATIONS; ITER++)\
    {\
        double MAXOFF_DIAG = __FIND_MAX_OFF_DIAGONAL_FUNCTION__(N, A, P, Q);\
        if (MAXOFF_DIAG < EPSILON)\
        {\
            break;\
        }\
        double APP = A[P * N + P];\
        double AQQ = A[Q * N + Q];\
        double APQ = A[P * N + Q];\
        double THETA = 0.5 * std::atan2(2.0 * APQ, AQQ - APP);\
        double C = std::cos(THETA);\
        double S = std::sin(THETA);\
        double APP_NEW = C * C * APP - 2.0 * S * C * APQ + S * S * AQQ;\
        double AQQ_NEW = S * S * APP + 2.0 * S * C * APQ + C * C * AQQ;\
        A[P * N + P] = APP_NEW;\
        A[Q * N + Q] = AQQ_NEW;\
        A[P * N + Q] = 0.0;\
        A[Q * N + P] = 0.0;\
        for (int I = 0; I < N; I++)\
        {\
            if (I != P && I != Q)\
            {\
                double AIP = A[I * N + P];\
                double AIQ = A[I * N + Q];\
                A[I * N + P] = C * AIP - S * AIQ;\
                A[P * N + I] = A[I * N + P];\
                A[I * N + Q] = S * AIP + C * AIQ;\
                A[Q * N + I] = A[I * N + Q];\
            }\
        }\
    }\
    for (int I = 0; I < N; I++)\
    {\
        EIGENVALUES[I] = A[I * N + I];\
    }\
    return false; }()

#endif // EIGENVALUE_HPP