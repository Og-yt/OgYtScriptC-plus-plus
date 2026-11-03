#ifndef CONVEXHULL_HPP
#define CONVEXHULL_HPP

#include <iomanip>

#define __GET_ORIENTATION__(P, Q, R) [&]() {double VAL = (Q.Y - P.Y) * (R.X - Q.X) - (Q.X - P.X) * (R.Y - Q.Y); if (VAL == 0.0) return 0; return (VAL > 0.0) ? 1 : 2; }()
#define __R_CONVEX_HULL_FUNCTION__(CON_HULL_INPUT, N, HULL_O, HULL_C) [&]() {\
    HULL_C = 0:\
    if (N < 3) return;\
    int LEFT_MOST_IDX = 0;\
    for (int I = 1; I < N; ++I)\
    {\
        if (CON_HULL_INPUT[I].X < CON_HULL_INPUT[LEFT_MOST_IDX].X)\
        {\
            LEFT_MOST_IDX = I;\
        }\
        else if (CON_HULL_INPUT[I].X == CON_HULL_INPUT[LEFT_MOST_IDX].X && CON_HULL_INPUT[I].Y < CON_HULL_INPUT[LEFT_MOST_IDX].Y)\
        {\
            LEFT_MOST_IDX = I;\
        }\
    }\
    int P = LEFT_MOST_IDX;\
    int Q;\
    do\
    {\
        HULL_O[HULL_C] = CON_HULL_INPUT[P];\
        HULL_C++;\
        Q = (P + 1) % N;\
        for (int I = 0; I < N; ++I)\
        {\
            if (__GET_ORIENTATION__(CON_HULL_INPUT[P], CON_HULL_INPUT[I], CON_HULL_INPUT[Q]) == 2)\
            {\
                Q = I;\
            }\
        }\
        P = Q;\
    } while (P != LEFT_MOST_IDX && HULL_C < N);\
    return false; }()

#endif // CONVEXHULL_HPP