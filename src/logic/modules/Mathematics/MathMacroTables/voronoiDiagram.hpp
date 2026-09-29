#ifndef VORONOIDIAGRAM_HPP
#define VORONOIDIAGRAM_HPP

#include <iomanip>
#include <cmath>

#define __R_VOR_DIA_MAX_POINT 32
#define __R_VOR_DIA_MAX_TRIANGLE (__R_VOR_DIA_MAX_POINT * 3)
#define __R_VOR_DIA_MAX_VOR_EDGE (__R_VOR_DIA_MAX_TRIANGLE * 3)

struct __VOR_DIA_POINT_2D
{
    double X;
    double Y;
};

struct TRIANGLE__
{
    int V_0, V_1, V_2;
    bool IS_ACTIVE;
};

struct VORONOI_EDGE
{
    __VOR_DIA_POINT_2D START;
    __VOR_DIA_POINT_2D END;
    int CELL_INDEX_1;
    int CELL_INDEX_2;
};

#define __VOR_DIA_GET_CIRCUMCENTER(A, B, C) [&]() {\
    double D = 2.0 * (A.X * (B.Y - C.Y) + B.X * (C.Y - A.Y) + C.X * (A.Y - B.Y));\
    if (std::abs(D) < 1e-9)\
    {\
        return {\
            (A.X + B.X + C.X) / 3.0, (A.Y + B.Y + C.Y) / 3.0\
        };\
    }\
    double UX = ((std::pow(A.X,2) + std::pow(A.Y,2)) * (B.Y - C.Y) + (std::pow(B.X,2) + std::pow(B.Y,2)) * (C.Y - A.Y) + (std::pow(C.X,2) + std::pow(C.Y,2)) * (A.Y - B.Y)) / D;\
    double UY = ((std::pow(A.X,2) + std::pow(A.Y,2)) * (B.X - C.X) + (std::pow(B.X,2) + std::pow(B.Y,2)) * (C.X - A.X) + (std::pow(C.X,2) + std::pow(C.Y,2)) * (A.X - B.X)) / D;\
    return { UX, UY }; }()
#define __IN_CIRCUMCIRCLE(P, A, B, C) [&]() {\
    double AX = A.X - P.X, AY = A.Y - P.Y;\
    double BX = B.X - P.X, BY = A.Y - P.Y;\
    double CX = C.X - P.X, CY = C.Y - P.Y;\
    double DET = (std::pow(A.X,2) + std::pow(A.Y,2)) * (BX * BY - CX * CY) -\
                 (std::pow(B.X,2) + std::pow(B.Y,2)) * (AX * CY - CX * AY) +\
                 (std::pow(C.X,2) + std::pow(C.Y,2)) * (AX * BY - BX * AY);\
    double AB_WINDING = (B.X - A.X) * (C.Y - A.Y) - (B.Y - A.Y) * (C.X - A.X);\
    if (AB_WINDING < 0.0) return DET < 0.0;\
    return DET > 0.0; }()
#define __RUN_INTERNAL_DELAUNARY(INPUT_POINT, NUM_POINT, TRIANGL_OUTPUT, TRIANGLE_COUNT) [&]() {\
    struct LOCAL_EDGE {\
        int U, V;\
    };\
    TRIANGLE_COUNT = 0;\
    if (NUM_POINT < 3) return;\
    __VOR_DIA_POINT_2D LOCAL_POINT[__R_VOR_DIA_MAX_POINT + 3];\
    for (int I = 0; I < NUM_POINT; ++I) LOCAL_POINT[I] = INPUT_POINT[I];\
    double MIN_X = LOCAL_POINT[0].X, MAX_X = MIN_X, MIN_Y = LOCAL_POINT[0].Y, MAX_Y = MIN_Y;\
    for (int I = 1; I < NUM_POINT; ++I)\
    {\
        if (LOCAL_POINT[I].X < MIN_X) MIN_X = LOCAL_POINT[I].X;\
        if (LOCAL_POINT[I].Y < MIN_Y) MIN_Y = LOCAL_POINT[I].Y;\
        if (LOCAL_POINT[I].X > MAX_X) MAX_X = LOCAL_POINT[I].X;\
        if (LOCAL_POINT[I].Y > MAX_Y) MAX_Y = LOCAL_POINT[I].Y;\
    }\
    double DX - MAX_X - MIN_X, DY = MAX_Y - MIN_Y;\
    double DELTA_MAX = (DX > DY) ? DX : DY;\
    double MID_X = (MIN_X + MAX_X) * 0.5, MID_Y = (MIN_Y + MAX_Y) * 0.5;\
    int ST_0 = NUM_POINT, ST_1 = NUM_POINT + 1, ST_2 = NUM_POINT + 2;\
    LOCAL_POINT[ST_0] = {\
        MID_X - 20.0 * DELTA_MAX,\
        MID_Y - DELTA_MAX\
    };\
    LOCAL_POINT[ST_1] = {\
        MID_X,\
        MID_Y + 20.0 * DELTA_MAX\
    };\
    LOCAL_POINT[ST_2] = {\
        MID_X + 20.0 * DELTA_MAX,\
        MID_Y - DELTA_MAX\
    };\
    TRIANGLE__ TRIANGLES[__R_VOR_DIA_MAX_TRIANGLE];\
    int TRI_COUNT = 0;\
    TRIANGLES[TRI_COUNT++] = {\
        ST_0,\
        ST_1,\
        ST_2,\
        true\
    };\
    for (int I = 0; I < NUM_POINT; ++I)\
    {\
        LOCAL_EDGE VOR_DIA_EDGE_BUFFER[__R_VOR_DIA_MAX_TRIANGLE * 3];\
        int EDGE_COUNT = 0;\
        for (int T = 0; T < TRI_COUNT; ++T)\
        {\
            if (TRIANGLES[T].IS_ACTIVE && __IN_CIRCUMCIRCLE(\
                LOCAL_POINT[I],\
                LOCAL_POINT[TRIANGLES[T].V_0],\
                LOCAL_POINT[TRIANGLES[T].V_1],\
                LOCAL_POINT[TRIANGLES[T].V_2]))\
            {\
                TRIANGLES[T].IS_ACTIVE = false;\
                EDGE_BUFFER[EDGE_COUNT++] = {\
                    TRIANGLES[T].V_0,\
                    TRIANGLES[T].V_1\
                };\
                EDGE_BUFFER[EDGE_COUNT++] = {\
                    TRIANGLES[T].V_1,\
                    TRIANGLES[T].V_2\
                };\
                EDGE_BUFFER[EDGE_COUNT++] = {\
                    TRIANGLES[T].V_2,\
                    TRIANGLES[T].V_0,\
                };\
            }\
        }\
        for (int E1 = 0; E1 < EDGE_COUNT; ++E1)\
        {\
            for (int E2 = E1 + 1; E2 < EDGE_COUNT; ++E2)\
            {\
                if (((EDGE_BUFFER[E1].U == EDGE_BUFFER[E2].U) && (EDGE_BUFFER[E1].V == EDGE_BUFFER[E2].V) || ((EDGE_BUFFER[E1].U == EDGE_BUFFER[E2].V) && (EDGE_BUFFER[E1].V) == EDGE_BUFFER[E2].U)))\
                {\
                    EDGE_BUFFER[E1].U = -1;\
                    EDGE_BUFFER[E1].V = -1;\
                    EDGE_BUFFER[E2].U = -1;\
                    EDGE_BUFFER[E2].V = -1;\
                }\
            }\
        }\
        for (int E = 0; E < EDGE_COUNT; ++E)\
        {\
            if (EDGE_BUFFER[E].U != -1 && EDGE_BUFFER[E].V != -1 && TRI_COUNT < __R_VOR_DIA_MAX_TRIANGLE)\
            {\
                TRIANGLES[TRI_COUNT++] = {\
                    EDGE_BUFFER[E].U,\
                    EDGE_BUFFER[E].V,\
                    I,\
                    true,\
                };\
            }\
        }\
    }\
    for (int T = 0; T < TRI_COUNT; ++T)\
    {\
        if (TRIANGLES[T].IS_ACTIVE)\
        {\
            if (TRIANGLES[T].V_0 < NUM_POINT && TRIANGLE[T].V_1 < NUM_POINT && TRIANGLE[T].V_2 < NUM_POINT)\
            {\
                TRIANGLE_OUTPUT[TRIANGLE_COUNT++] = TRIANGLES[T];\
            }\
        }\
    }\
    return TRI_COUNT; }()
#define __R_VORONOI_DIAGRAM_FUNCTION__(INPUT_POINT, NUM_POINT, EDGE_OUTPUT, EDGE_COUNT) [&]() {\
    EDGE_COUNT = 0;\
    if (NUM_POINT < 3) return;\
    TRIANGLE__ DT_MESH[__R_VOR_DIA_MAX_TRIANGLE];\
    int DT_COUNT = 0;\
    __RUN_INTERNAL_DELAUNARY(INPUT_POINT, NUM_POINT, DT_MESH, DT_COUNT);\
    for (int I = 0; I < DT_COUNT; ++I)\
    {\
        for (int J = I + 1; J < DT_COUNT; ++J)\
        {\
            int SHARED_COUNT = 0;\
            int SHARED_V1 = -1, SHARED_V2 = -1;\
            int V_I[3] = {\
                DT_MESH[I].V_0,\
                DT_MESH[I].V_1,\
                DT_MESH[I].V_2\
            };\
            int V_J[3] = {\
                DT_MESH[J].V_0,\
                DT_MESH[J].V_1,\
                DT_MESH[J].V_2\
            };\
            for (int K = 0; K < 3; ++K)\
            {\
                for (int M = 0; M < 3; ++M)\
                {\
                    if (V_I[K] == V_J[M])\
                    {\
                        SHARED_COUNT++;\
                        if (SHARED_V1 == -1)\
                        {\
                            SHARED_V1 = V_I[K];\
                        }\
                        else\
                        {\
                            SHARED_V2 = V_I[K];\
                        }\
                    }\
                }\
            }\
            if (SHARED_COUNT == 2 && EDGE_COUNT < __R_VOR_DIA_MAX_VOR_EDGE)\
            {\
                __VOR_DIA_POINT_2D CENTER_1 = __VOR_DIA_GET_CIRCUMCENTER(INPUT_POINT[DT_MESH[I].V_0], INPUT_POINT[DT_MESH].V_1, INPUT_POINT[DT_MESH[I].V_2]);\
                __VOR_DIA_POINT_2D CENTER_2 = __VOR_DIA_GET_CIRCUMCENTER(INPUT_POINT[DT_MESH[J].V_0], INPUT_POINT[DT_MESH].V_1, INPUT_POINT[DT_MESH[J].V_2]);\
                EDGE_OUTPUT[EDGE_COUNT++] = {\
                    CENTER_1,\
                    CENTER_2,\
                    SHARED_V1,\
                    SHARED_V2\
                };\
            }\
        }\
    }\
    return EDGE_COUNT; }()

#endif // VORONOIDIAGRAM_HPP