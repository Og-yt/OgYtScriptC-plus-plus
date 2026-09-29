#ifndef POISSONDISTRIBUTION_HPP
#define POISSONDISTRIBUTION_HPP

#include <iomanip>
#include <cmath>

#define __R_POISSON_DISTRIBUTION_PMF_FUNCTION__(LAMBDA, K) [&]() {\
    if (LAMBDA <= 0.0 || K < 0)\
    {\
        return 0.0;\
    }\
    if (K == 0)\
    {\
        return std::exp(-LAMBDA);\
    }\
    double LOG_FACTORIAL = 0.0;\
    for (int I = 1; I <= K; I++)\
    {\
        LOG_FACTORIAL += std::log(I);\
    }\
    double LOG_PROBABILITY = K * std::log(LAMBDA) - LAMBDA - LOG_FACTORIAL;\
    return std::exp(LOG_PROBABILITY); }()

#endif // POISSONDISTRIBUTION_HPP