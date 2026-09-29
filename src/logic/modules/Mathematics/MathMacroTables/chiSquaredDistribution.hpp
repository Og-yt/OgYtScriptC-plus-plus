#ifndef CHISQUAREDDISTRIBUTION_HPP
#define CHISQUAREDDISTRIBUTION_HPP

#include <iomanip>
#include <cmath>

#define __R_CHI_SQUARED_DISTRIBUTION_PDF_FUNCTION__(X, DF) [&]() {\
    if (DF < 1 || X <= 0.0)\
    {\
        return 0.0;\
    }\
    double K = static_cast<double>(DF);\
    double LOG_DENOMINATOR = (K / 2.0) * std::log(2.0) + std::lgamma(K / 2.0);\
    double LOG_NUMERATOR = ((K / 2.0) - 1.0) * std::log(X) - (X / 2.0);\
    double LOG_PDF = LOG_NUMERATOR - LOG_DENOMINATOR;\
    return std::exp(LOG_PDF); }()

#endif // CHISQUAREDDISTRIBUTION_HPP