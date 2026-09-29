#ifndef PRIME_HPP
#define PRIME_HPP

#include <cmath>

#define __R_PRIME__(N) [&]() {                    \
    if (N < 2) return 0;                          \
    for (long long I = 2; I <= std::sqrt(N); I++) \
    {                                             \
        if (N % I == 0)                           \
        {                                         \
            return 0;                             \
        }                                         \
    }                                             \
    return 1; }()

#endif // PRIME_HPP