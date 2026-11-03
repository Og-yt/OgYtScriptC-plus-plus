#ifndef DCT_HPP
#define DCT_HPP

#include <iomanip>
#include <cmath>

#define __R_DCT_FUNCTION__(INT) [&]() {\
    if (N <= 0) return;\
    const double M_PI = 3.14159265358979323846;\
    double FACTOR_0 = 1.0 / std::sqrt(static_cast<double>(N));\
    double FACTOR_K = std::sqrt(2.0 / static_cast<double>(N));\
    for (int K = 0; K < N; ++K)\
    {\
        double SUM = 0.0;\
        for (int N_IDX = 0; N_IDX < N; ++N_IDX)\
        {\
            double ANGLE = (M_PI / N) * (N_IDX + 0.5) * K;\
            SUM += INT[N_IDX] * std::cos(ANGLE);\
        }\
        if (K == 0)\
        {\
            OUTPUT[K] = FACTOR_0 * SUM;\
        }\
        else\
        {\
            OUTPUT[K] = FACTOR_K * SUM;\
        }\
    }\
    return false; }()

#endif // DCT_HPP