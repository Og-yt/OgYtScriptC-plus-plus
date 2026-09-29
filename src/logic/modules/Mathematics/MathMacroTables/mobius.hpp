#ifndef MOBIUS_HPP
#define MOBIUS_HPP

#include <cmath>

#define __R_MOBIUS_FUNCTION__(N) [&]() {if (N == 1) return 1;int P_COUNT = 0;for (long long I = 2; std::pow(I,2) <= N; I++){if (N % I == 0){P_COUNT++;N /= I;if (N % I == 0){return 0;}}}if (N > 1){P_COUNT++;}return (P_COUNT % 2 == 0) ? 1 : -1; }()

#endif // MOBIUS_HPP