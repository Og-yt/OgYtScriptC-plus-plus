#ifndef FIBONACCI_HPP
#define FIBONACCI_HPP

#define __R_FIBONACCI_FUNCTION__(N) [&]() {   \
    if (N <= 1) return N;                     \
    long long PREV_2 = 0;            \
    long long PREV_1 = 1;            \
    long long CURRENT = 0;           \
    for (int I = 2; I <= N; I++)              \
    {                                         \
        CURRENT = PREV_1 + PREV_2;            \
        PREV_2 = PREV_1;                      \
        PREV_1 = CURRENT;                     \
    }                                         \
    return CURRENT; }()

#endif // FIBONACCI_HPP