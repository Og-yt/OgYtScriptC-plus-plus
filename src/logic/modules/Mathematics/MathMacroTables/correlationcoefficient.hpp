#ifndef CORRELATIONCOEFFICIENT_HPP
#define CORRELATIONCOEFFICIENT_HPP

#include <iomanip>
#include <cmath>

#define __R_CORRELATION_COEFFICIENT_FUNCTION__(ARR_X, ARR_Y, CORE_SIZE) [&]() {\
    if (CORE_SIZE <= 1)\
    {\
        return 0.0;\
    }\
    double SUMX = 0.0, SUMY = 0.0;\
    for (int I = 0; I < CORE_SIZE; ++I)\
    {\
        SUMX += ARR_X[I];\
        SUMY += ARR_Y[I];\
    }\
    double MEANX = SUMX / CORE_SIZE;\
    double MEANY = SUMY / CORE_SIZE;\
    double TOTAL_PRODUCT_DIFF = 0.0;\
    double VARX_SUM = 0.0;\
    double VARY_SUM = 0.0;\
    for (int I = 0; I < CORE_SIZE; ++I)\
    {\
        double DIFF_X = ARR_X[I] - MEANX;\
        double DIFF_Y = ARR_Y[I] - MEANY;\
        TOTAL_PRODUCT_DIFF += DIFF_X * DIFF_Y;\
        VARX_SUM += DIFF_X * DIFF_X;\
        VARY_SUM += DIFF_Y * DIFF_Y;\
    }\
    if (VARX_SUM == 0.0 || VARY_SUM == 0.0)\
    {\
        return 0.0;\
    }\
    return TOTAL_PRODUCT_DIFF / std::sqrt(VARX_SUM * VARY_SUM); }()

#endif // CORRELATIONCOEFFICIENT_HPP