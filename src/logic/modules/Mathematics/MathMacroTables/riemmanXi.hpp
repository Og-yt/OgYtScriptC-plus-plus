#ifndef RIEMMANXI_HPP
#define RIEMMANXI_HPP

#include <cmath>
#include <numbers>

#define __R_RIEMMAN_XI__(S) [&]() {\
    if (S == 1.0 || S == 0.0)\
    {\
        return 0.5;\
    }\
    double TERM_1 = 0.5 * S * (S - 1.0);\
    double TERM_2 = std::pow(std::numbers::pi, -S / 2.0);\
    double TERM_3 = std::tgamma(S / 2.0);\
    double TERM_4 = std::riemman_zeta(S);\
    return TERM_1 * TERM_2 * TERM_3 * TERM_4; }()

#endif // RIEMMANXI_HPP