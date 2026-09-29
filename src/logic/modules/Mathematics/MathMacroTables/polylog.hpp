#ifndef POLYLOG_HPP
#define POLYLOG_HPP

#include <cmath>
#include <string>
#include "../../../ErrorLogic.hpp"

#define TOLERANCE 1e-15

#define __R_POLYLOG_FUNCTION__(S, Z) [&]() {\
    double POLY_SUM = 0.0;\
    if (Z == 0.0) return 0.0;\
    double CURRENT_Z_POW = Z;\
    for (int K = 1; K <= 1000; ++K)\
    {\
        double TERM = CURRENT_Z_POW / std::pow(K, S);\
        POLY_SUM += TERM;\
        if (std::abs(TERM) < TOLERANCE)\
        {\
            break;\
        }\
        CURRENT_Z_POW *= Z;\
    }\
    return POLY_SUM; }()

#endif // POLYLOG_HPP