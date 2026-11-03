#ifndef FDISTRIBUTION_HPP
#define FDISTRIBUTION_HPP

#include <iomanip>
#include <cmath>

#define __R_F_DISTRIBUTION_PDF_FUNCTION__(X, DF1, DF2) [&]() {\
    if (DF1 < 1 || DF2 < 1 || X <= 0.0)\
    {\
        return 0.0;\
    }\
    double D1 = static_cast<double>(DF1);\
    double D2 = static_cast<double>(DF2);\
    double LOG_BETA_FUNCTION = std::lgamma(D1 / 2.0) + std::lgamma(D2 / 2.0) - std::lgamma((D1 + D2) / 2.0);\
    double LOG_PDF = (D1 / 2.0 * std::log(D1))\
                     + (D2 / 2.0 * std::log(D2))\
                     + ((D1 / 2.0 - 1.0) * std::log(X))\
                     - (((D1 + D2) / 2.0) * std::log(D1 * X + D2))\
                     - LOG_BETA_FUNCTION;\
    return std::exp(LOG_PDF); }()

#endif // FDISTRIBUTION_HPP