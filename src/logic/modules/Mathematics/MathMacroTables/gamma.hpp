#ifndef GAMMA_HPP
#define GAMMA_HPP

#include <cmath>

#define __R_GAMMA_FUNCTION__(N) [&]() { return std::tgamma(N); }()

#endif // GAMMA_HPP