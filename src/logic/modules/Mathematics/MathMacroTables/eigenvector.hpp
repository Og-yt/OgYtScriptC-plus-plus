#ifndef EIGENVECTOR_HPP
#define EIGENVECTOR_HPP

#include <iomanip>
#include <cmath>

#define __R_EIGENVEC_FUNC_MAX_ITERATIONS 100
#define __FIND_MAX_OFF_DIAGONAL_FUNCTION__(N, A, ROW, COL) [&]() {\
    double MAXVAL = 0.0;\
    ROW = 0;\
    COL = 1;\
    for (int I = 0; I < N; I++)\
    {\
        for (int J = I + 1; J < N; J++)\
        {\
            double VAL = std::abs(A[I * N + J]);\
            if (VAL > MAXVAL)\
            {\
                MAXVAL = VAL;\
                ROW = I;\
                COL = J;\
            }\
        }\
    }\
    return MAXVAL; }()
#define __R_EIGENVECTOR_FUNCTION__(N, A, EIGENVALUES, EGENVEC) [&]() {\
    const double EPSILON = 1e-9;\
    int P, Q;\
    for (int I = 0; I < N; I++)\
    {\
        for (int J = 0; J < N; J++)\
        {\
            EGENVEC[I * N + J] = (I == J) ? 1.0 : 0.0;\
        }\
    }\
    for (int ITER = 0; ITER < __R_EIGENVEC_FUNC_MAX_ITERATIONS; ITER++)\
    {\
        double MAX_OFF_DIAG = __FIND_MAX_OFF_DIAGONAL_FUNCTION__(N, A, P, Q);\
        if (MAX_OFF_DIAG < EPSILON)\
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
                double AP = A[I * N + P];\
                double AQ = A[I * N + Q];\
                A[I * N + P] = C * AP - S * AQ;\
                A[P * N + I] = A[I * N + P];\
                A[I * N + Q] = S * AP + C * AQ;\
                A[Q * N + I] = A[I * N + Q];\
            }\
        }\
        for (int I = 0; I < N; I++)\
        {\
            double VIP = EGENVEC[I * N + P];\
            double VIQ = EGENVEC[I * N + Q];\
            EGENVEC[I * N + P] = C * VIP - S * VIQ;\
            EGENVEC[I * N + Q] = S * VIP + C * VIQ;\
        }\
    }\
    for (int I = 0; I < N; I++)\
    {\
        EIGENVALUES[I] = A[I * N + I];\
    }\
    return EGENVEC; }()

#endif // EIGENVECTOR_HPP