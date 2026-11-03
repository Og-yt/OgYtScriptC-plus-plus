#ifndef CATALAN_HPP
#define CATALAN_HPP

#include <vector>

#define __R_CATALAN_FUNCTION_DP__(N) [&]() {\
    if (N <= 1)\
    {\
        return 1;\
    }\
    int CATALAN = 1;\
    for (int K = 1; K <= N; ++K)\
    {\
        CATALAN = CATALAN * (2 * N - K) / K;\
    }\
    return CATALAN; }()


#define __R_CATALAN_FUNCTION_EFFICIENT__(N) [&]() -> long long { \
    if (N <= 1) return 1;                                       \
    long long RES = 1;                                          \
    for (int I = 0; I < N; ++I)                                 \
    {                                                           \
        RES = RES * (4LL * N - 2 * I) / (I + 1);                \
    }                                                           \
    return RES / (N + 1); }()

/*
int main() {
    const int count = 10;

    std::cout << "First " << count << " Catalan numbers (DP Approach):\n";
    for (int i = 0; i < count; ++i) {
        std::cout << "C(" << i << ") = " << getCatalanDP(i) << "\n";
    }

    std::cout << "\nFirst " << count << " Catalan numbers (O(n) Formula):\n";
    for (int i = 0; i < count; ++i) {
        std::cout << "C(" << i << ") = " << getCatalanEfficient(i) << "\n";
    }

    return 0;
}
*/

#endif // CATALAN_HPP