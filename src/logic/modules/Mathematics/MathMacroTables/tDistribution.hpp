#ifndef TDISTRIBUTION_HPP
#define TDISTRIBUTION_HPP

#include <iomanip>
#include <cmath>

#define __R_T_DISTRIBUTION_FUNCTION__(T, DF) [&]() {\
    if (DF < 1)\
    {\
        return 0.0;\
    }\
    const double _R_T_DIS_FUNC__M_PI__ = 3.14159265358979323846;\
    double NU = static_cast<double>(DF);\
    double LOG_NUMERATOR_GAMMA = std::lgamma((NU + 1.0) / 2.0);\
    double LOG_DENOMINATOR_CONSTANT = 0.5 * std::log(NU * _R_T_DIS_FUNC__M_PI__) + std::lgamma(NU / 2.0);\
    double LOG_BASE_TERM = -((NU + 1.0) / 2.0) * std::log(1.0 + (std::pow(T,2)) / 2.0);\
    double LOG_PDF = LOG_NUMERATOR_GAMMA - LOG_DENOMINATOR_CONSTANT + LOG_BASE_TERM;\
    return std::exp(LOG_PDF); }()

#endif // TDISTRIBUTION_HPP