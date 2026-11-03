#ifndef NORMALDISTRIBUTIONCDF_HPP
#define NORMALDISTRIBUTIONCDF_HPP

#include <iomanip>
#include <cmath>

#define __R_NORMAL_DISTRIBUTION_CDF_FUNCTION__(X, MEAN, STD_DEV) [&]() {\
    if (STD_DEV <= 0.0)\
    {\
        return 0.0;\
    }\
    double VALLUE_FOR_ERF = (X - MEAN) / (STD_DEV * std::sqrt(2.0));\
    return 0.5 * (1.0 + std::erf(VALLUE_FOR_ERF)); }()

#endif // NORMALDISTRIBUTIONCDF_HPP