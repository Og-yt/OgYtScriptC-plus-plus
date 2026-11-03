#ifndef GAMMADISTRIBUTION_HPP
#define GAMMADISTRIBUTION_HPP

#include <iomanip>
#include <cmath>

#define __R_GAMMA_DISTRIBUTION_FUNCTION__(X, ALPHA, BATA) [&]() {\
    if (X <= 0.0 || ALPHA <= 0.0 || BATA <= 0.0)\
    {\
        return 0.0;\
    }\
    double LOG_PDF = (ALPHA * std::log(BATA)) - std::lgamma(ALPHA) + ((ALPHA - 1.0) * std::log(X)) - (BATA * X);\
    return std::exp(LOG_PDF); }()

#endif // GAMMADISTRIBUTION_HPP