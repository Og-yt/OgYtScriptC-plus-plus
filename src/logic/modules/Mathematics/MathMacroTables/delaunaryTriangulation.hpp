#ifndef DELAUNARYTRIANGLATION_HPP
#define DELAUNARYTRIANGLATION_HPP

#include <iomanip>
#include <cmath>

#define __DEL_TRI_MAX_POINTS 32
#define __DEL_TRI_MAX_TRIANGLES 32 * 3

struct __DELA_TRI_POINT_2D
{
    double X;
    double Y;
};

struct TRIANGLE
{
    int V0;
    int V1;
    int V2;
    bool IS_ACTIVE;
};

struct EDGE
{
    int U;
    int V;
};

#define __IN_CIRCUMCIRCLE__(P, A, B, C)[&]() {\
    double AX = A.X - P.X, AY = A.Y - P.Y;\
    double BX = B.X - P.X, BY = B.Y - P.Y;\
    double CX = C.X - P.X, CY = C.Y - P.Y;\
    double DET = (AX * AX + AY * AY) * (BX * BY - CX * CY) - (BX * BX + BY * BY) * (AX * CY - CX * AY) + (CX * CX + CY * CY) * (AX * BY - BX * AY);\
    double AB_WINDING = (B.X - A.X) * (C.Y - A.Y) - (B.Y - A.Y) * (C.X - A.X);\
    if (AB_WINDING < 0.0) {\
        return DET < 0.0;\
    }\
    return DET > 0.0; }()
#define __R_DELAUNARY_TRIANGLE_FUNCTION__(INPUT_POINTS, NUM_POINTS, TRIANGLE_OUTPUT, TRIANGLE_COUNT)[&]() {\
    TRIANGLE_COUNT = 0;\
    if (NUM_POINTS < 3) return;\
    __DELA_TRI_POINT_2D LOCAL_POINTS[__DEL_TRI_MAX_POINTS + 3];\
    for (int I = 0; I < NUM_POINTS; ++I) {\
        LOCAL_POINTS[I] = INPUT_POINTS[I];\
    }\
    double MIN_X = LOCAL_POINTS[0].X, MAX_X = MIN_X;\
    double MIN_Y = LOCAL_POINTS[0].Y, MAX_Y = MIN_Y;\
    for (int I = 1; I < NUM_POINTS; ++I) {\
        if (LOCAL_POINTS[I].X < MIN_X) MIN_X = LOCAL_POINTS[I].X;\
        if (LOCAL_POINTS[I].X > MAX_X) MAX_X = LOCAL_POINTS[I].X;\
        if (LOCAL_POINTS[I].Y < MIN_Y) MIN_Y = LOCAL_POINTS[I].Y;\
        if (LOCAL_POINTS[I].Y > MAX_Y) MAX_Y = LOCAL_POINTS[I].Y;\
    }\
    double DX = MAX_X - MIN_X;\
    double DY = MAX_Y - MIN_Y;\
    double DELTA_MAX = (DX > DY) ? DX : DY;\
    double MID_X = (MIN_X + MAX_X) * 0.5;\
    double MID_Y = (MIN_Y + MAX_Y) * 0.5;\
    int ST0 = NUM_POINTS, ST1 = NUM_POINTS + 1, ST2 = NUM_POINTS + 2;\
    LOCAL_POINTS[ST0] = { MID_X - 20.0 * DELTA_MAX, MID_Y - DELTA_MAX };\
    LOCAL_POINTS[ST1] = { MID_X, MID_Y + 20.0 * DELTA_MAX };\
    LOCAL_POINTS[ST2] = { MID_X + 20.0 * DELTA_MAX, MID_Y - DELTA_MAX };\
    TRIANGLE TRIANGLES[__DEL_TRI_MAX_TRIANGLES];\
    int TRI_COUNT = 0;\
    TRIANGLES[TRI_COUNT++] = { ST0, ST1, ST2, true };\
    for (int I = 0; I < NUM_POINTS; ++I)\
    {\
        EDGE EDGE_BUFFER[__DEL_TRI_MAX_TRIANGLES * 3];\
        int EDGE_COUNT = 0;\
        for (int T = 0; T < TRI_COUNT; ++T)\
        {\
            if (TRIANGLES[T].IS_ACTIVE && __IN_CIRCUMCIRCLE__(LOCAL_POINTS[I], LOCAL_POINTS[TRIANGLES[T].V0], LOCAL_POINTS[TRIANGLES[T].V1], LOCAL_POINTS[TRIANGLES[T].V2]))\
            {\
                TRIANGLES[T].IS_ACTIVE = false;\
                EDGE_BUFFER[EDGE_COUNT++] = { TRIANGLES[T].V0, TRIANGLES[T].V1 };\
                EDGE_BUFFER[EDGE_COUNT++] = { TRIANGLES[T].V1, TRIANGLES[T].V2 };\
                EDGE_BUFFER[EDGE_COUNT++] = { TRIANGLES[T].V2, TRIANGLES[T].V0 };\
            }\
        }\
        for (int E1 = 0; E1 < EDGE_COUNT; ++E1)\
        {\
            for (int E2 = E1 + 1; E2 < EDGE_COUNT; ++E2)\
            {\
                if (((EDGE_BUFFER[E1].U == EDGE_BUFFER[E2].U) && (EDGE_BUFFER[E1].V == EDGE_BUFFER[E2].V)) || ((EDGE_BUFFER[E1].U == EDGE_BUFFER[E2].V) && (EDGE_BUFFER[E1].V == EDGE_BUFFER[E2].U)))\
                {\
                    EDGE_BUFFER[E1].U = -1; EDGE_BUFFER[E1].V = -1;\
                    EDGE_BUFFER[E2].U = -1; EDGE_BUFFER[E2].V = -1;\
                }\ 
            }\
        }\
        for (int E = 0; E < EDGE_COUNT; ++E)\
        {\
            if (EDGE_BUFFER[E].U != -1 && EDGE_BUFFER[E].V != -1 && TRI_COUNT < __DEL_TRI_MAX_TRIANGLES)\
            {\
                TRIANGLES[TRI_COUNT++] = { EDGE_BUFFER[E].U, EDGE_BUFFER[E].V, I, true };\
            }\
        }\
    }\
    for (int T = 0; T < TRI_COUNT; ++T)\
    {\
        if (TRIANGLES[T].IS_ACTIVE)\
        {\
            if (TRIANGLES[T].V0 < NUM_POINTS && TRIANGLES[T].V1 < NUM_POINTS && TRIANGLES[T].V2 < NUM_POINTS)\
            {\
                TRIANGLE_OUTPUT[TRIANGLE_COUNT++] = TRIANGLES[T];\
            }\
        }\
    }\
    return false; }()

#endif // DELAUNARYTRIANGLATION_HPP