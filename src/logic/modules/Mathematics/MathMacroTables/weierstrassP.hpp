#ifndef WEIERSTRASSP_HPP
#define WEIERSTRASSP_HPP

#include <cmath>
#include <complex>

#define __R_WEI_P_PI std::acos(-1.0)
#define __R_WEI_P_EPS 1e-12

#define __R_WEIERSTRASS_P_THETA_3__(Q) [&]() {\
    double SUM = 1.0;\
    double TERM = 1.0;\
    int N = 1;\
    while (true)\
    {\
        TERM = std::pow(Q, N * N);\
        SUM += 2.0 * TERM;\
        if (TERM < __R_WEI_P_EPS) break;\
        N++;\
    }\
    return SUM; }()
#define __R_WEIERSTRASS_P_THETA_4__(Q) [&]() {\
    double SUM = 1.0;\
    double TERM = 1.0;\
    int N = 1;\
    while (true)\
    {\
        TERM = std::pow(Q, N * N);\
        if (N % 2 == 1)\
        {\
            SUM -= 2.0 * TERM;\
        }\
        else\
        {\
            SUM += 2.0 * TERM;\
        }\
        if (TERM < __R_WEI_P_EPS) break;\
        N++;\
    }\
    return SUM; }()
#define __R_WEIERSTRASS_P_THETA_2__(Q) [&]() {\
    double SUM = 0.0;\
    double TERM = 0.0;\
    int N = 0;\
    while (true)\
    {\
        TERM = std::pow(Q, (N + 0.5) * (N + 0.5));\
        SUM += 2.0 * TERM;\
        if (TERM < __R_WEI_P_EPS) break;\
        N++;\
    }\
    return SUM; }()

#define __R_WEIERSTRASS_P_FUNCTION__(Z, G2, G3) [&]() {\
    double DELTA = G2 * G2 * G2 - 27.0 * G3 * G3;\
    double Q = 0.1;\
    double TH3 = __R_WEIERSTRASS_P_THETA_3__(Q);\
    double TH4 = __R_WEIERSTRASS_P_THETA_4__(Q);\
    double TH2 = __R_WEIERSTRASS_P_THETA_2__(Q);\
    double OMEGA1 = __R_WEI_P_PI * TH3 * TH3;\
    double TERM_IN = (__R_WEI_P_PI * Z) / (2.0 * OMEGA1);\
    double THETA_RATIO = TH2 * std::sin(TERM_IN) / TH3;\
    double P_Z = TH3 * TH4 * TH4 * TH3 * (std::pow(THETA_RATIO,2));\
    return P_Z; }()

#endif // WEIERSTRASSP_HPP