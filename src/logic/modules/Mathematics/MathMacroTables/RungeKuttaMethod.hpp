#ifndef RUNGEKUTTAMETHOD_HPP
#define RUNGEKUTTAMETHOD_HPP

#include <iomanip>
#include <cmath>

#define __R_RUNGE_KUTA_4_STEP_METHOD_FUNCTION__(F, T, Y, H) [&]() {\
    double K1 = F(T, Y);\
    double K2 = F(T + H / 2.0, Y + (H * K1 / 2.0));\
    double K3 = F(T + H / 2.0, Y + (H * K2 / 2.0));\
    double K4 = F(T + H, Y + (H * K3));\
    return Y + (H / 6.0) * (K1 + 2.0 * K2 + 2.0 * K3 + K4); }()

#endif // RUNGEKUTTAMETHOD_HPP