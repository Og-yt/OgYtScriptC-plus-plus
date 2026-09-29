#ifndef JACOBITHETA_HPP
#define JACOBITHETA_HPP

#include <cmath>

#define __R_JACOBI_THETA_1_TOLERANCE__ 1e-12
#define __R_JACOBI_THETA_1__(Z, Q) [&]() {\
    double SUM = 0.0;\
    double TERM = 0.0;\
    int N = 0;\
    do\
    {\
        double POWER_Q = Q * N * (N + 1);\
        double SIGN = (N % 2 == 0) ? 1.0 : -1.0;\
        double ANGLE = (2 * N + 1) * Z;\
        TERM = SIGN * POWER_Q * std::sin(ANGLE);\
        SUM += TERM;\
        N++;\
    }\
    while (std::abs(TERM) > __R_JACOBI_THETA_1_TOLERANCE__ && N < 1000);\
    return 2.0 * std::pow(Q, 0.25) * SUM; }()

#endif // JACOBITHETA_HPP