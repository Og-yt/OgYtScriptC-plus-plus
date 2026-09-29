#ifndef BELL_HPP
#define BELL_HPP

#include <cmath>

#define __R_BELL_FUNCTION__(X, MU, SIGMA) [&]() {double EXPONENT = -0.5 * std::pow((X - MU) / SIGMA, 2.0);return std::exp(EXPONENT); }()

#endif // BELL_HPP