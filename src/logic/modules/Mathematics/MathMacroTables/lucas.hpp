#ifndef LUCAS_HPP
#define LUCAS_HPP

#define __R_LUCAS_FUNCTION__(N) [&]() {   \
    if (N == 0) return 2;                 \
    if (N == 1) return 1;                 \
    int PREV_2 = 2;        \
    int PREV_1 = 1;        \
    int CURRENT = 0;       \
    for (int I = 2; I <= N; ++I)          \
    {                                     \
        CURRENT = PREV_1 + PREV_2;        \
        PREV_2 = PREV_1;                  \
        PREV_1 = CURRENT;                 \
    }                                     \
    return CURRENT; }()

#endif // LUCAS_HPP