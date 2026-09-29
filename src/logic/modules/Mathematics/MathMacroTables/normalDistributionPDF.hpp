#ifndef NORMALDISTRIBUTIONPDF_HPP
#define NORMALDISTRIBUTIONPDF_HPP

#include <iomanip>
#include <cmath>

#define __R_NORMAL_DISTRIBUTION_PDF_FUNCTION__(X, MEAN, STD_DEV) [&]() {\
    if (STD_DEV <= 0.0)\
    {\
        return 0.0;\
    }\
    const double NOR_DIS_PDF__M_PI__ = 3.14159265358979323846;\
    double EXPONENT = -0.5 * std::pow((X - MEAN) / STD_DEV, 2);\
    double DENOMINATOR = STD_DEV * std::sqrt(2.0 * NOR_DIS_PDF__M_PI__);\
    return std::exp(EXPONENT) / DENOMINATOR; }()

#endif // NORMALDISTRIBUTIONPDF_HPP