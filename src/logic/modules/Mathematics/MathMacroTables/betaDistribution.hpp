#ifndef BETADISTRIBUTION_HPP
#define BETADISTRIBUTION_HPP

#include <iomanip>
#include <limits>
#include <cmath>

#define __R_BETA_DISTRIBUTION_FUNCTION__(X, ALPHA, BETA) [&]() {\
    if (ALPHA <= 0.0 || BETA <= 0.0)\
    {\
        return 0.0;\
    }\
    if (X < 0.0 || X > 1.0)\
    {\
        return 0.0;\
    }\
    if (X == 0.0)\
    {\
        return (ALPHA > 1.0) ? 0.0 : ((ALPHA == 1.0) ? BETA : std::numeric_limits<double>::infinity());\
    }\
    if (X == 1.0)\
    {\
        return (BETA > 1.0) ? 0.0 : ((BETA == 1.0) ? ALPHA : std::numeric_limits<double>::infinity());\
    }\
    double LOG_BETA_FUNCTION = std::lgamma(ALPHA) + std::lgamma(BETA) - std::lgamma(ALPHA + BETA);\
    double LOG_PDF = ((ALPHA - 1.0) * std::log(X)) + ((BETA - 1.0) * std::log(1.0 - X)) - LOG_BETA_FUNCTION;\
    return std::exp(LOG_PDF); }()

#endif // BETADISTRIBUTION_HPP