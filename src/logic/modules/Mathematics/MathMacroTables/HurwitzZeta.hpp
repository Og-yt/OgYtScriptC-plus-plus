#ifndef HURWITZZETA_HPP
#define HURWITZZETA_HPP

#include <cmath>
#include <limits>

#define __R_HURWITZ_ZETA_FUNCTION__(S, A) [&]() {\
    double HURW_SUM = 0.0;\
    if (std::abs(S - 1.0) < 1e-15)\
    {\
        return std::numeric_limits<double>::infinity();\
    }\
    const int N = 15;\
    for (int I = 0; I < N; ++I)\
    {\
        HURW_SUM += std::pow(A + I, -S);\
    }\
    double A_N = A + N;\
    double INTEGRAL_TERM = std::pow(A_N, 1.0 - S) / (S - 1.0);\
    double MIDPOINT_TERM = 0.5 * std::pow(A_N, -S);\
    HURW_SUM += INTEGRAL_TERM + MIDPOINT_TERM;\
    const double B_COEFF[] = {\
        1.0 / 12.0,\
        -1.0 / 720.0,\
        1.0 / 30240.0,\
        -1.0 / 1209600.0,\
        1.0 / 47900160.0,\
        -691.0 / 1307674368000.0\
    };\
    double TERM_FACTOR = S;\
    double CURRENT_POWER = std::pow(A_N, -S - 1.0);\
    double INV_A_N_SQ = 1.0 / (A_N * A_N);\
    for (int K = 1; K <= 6; ++K)\
    {\
        double DELTA = B_COEFF[K - 1] * TERM_FACTOR * CURRENT_POWER;\
        HURW_SUM += DELTA;\
        if (std::abs(DELTA) < 1e-15)\
        {\
            break;\
        }\
        TERM_FACTOR *= (S + 2 * K) * (S + 2 * K + 1);\
        CURRENT_POWER *= INV_A_N_SQ;\
    }\
    return HURW_SUM; }()

#endif // HURWITZZETA_HPP