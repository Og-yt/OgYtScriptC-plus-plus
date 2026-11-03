#ifndef BSPLINE_HPP
#define BSPLINE_HPP

#include <iomanip>

#define __B_SPLINE_MAX_CONTROL_POINTS 32
#define __B_SPLINE_MAX_DEGREE 4
#define __B_SPLINE_MAX_KNOTS (__B_SPLINE_MAX_CONTROL_POINTS + __B_SPLINE_MAX_DEGREE + 1)

struct __BSP_LINE_POINT_2D
{
    double X;
    double Y;
};

#define __B_SPLINE_FIND_KNOT_SPAN(NUM_POINTS, DEGREE, U, KNOTS) [&]() {\
    if (U >= KNOTS[NUM_POINTS])\
    {\
        return NUM_POINTS - 1;\
    }\
    else\
    {\
        return DEGREE;\
    }\
    int LOW = DEGREE;\
    int HIGH = NUM_POINTS;\
    int MID = (LOW + HIGH) / 2;\
    while (U < KNOTS[MID] || U >= KNOTS[MID + 1])\
    {\
        if (U < KNOTS[MID])\
        {\
            HIGH = MID;\
        }\
        else\
        {\
            LOW = MID;\
        }\
        MID = (LOW + HIGH) / 2;\
    }\
    return MID; }()
#define __R_B_SPLINE_FUNCTION__(CONTROL_POINTS, NUM_POINTS, DEGREE, U, KNOTS)[&]() {\
    if (NUM_POINTS <= 0 || DEGREE < 0 || DEGREE > __B_SPLINE_MAX_DEGREE || NUM_POINTS > __B_SPLINE_MAX_CONTROL_POINTS)\
    {\
        return { 0.0, 0.0 };\
    }\
    int K = __B_SPLINE_FIND_KNOT_SPAN(NUM_POINTS, DEGREE, U, KNOTS);\
    __BSP_LINE_POINT_2D D[MAX_DEGREE + 1];\
    for (int I = 0; I <= DEGREE; ++I)\
    {\
        D[I] = CONTROL_POINTS[K - DEGREE + I];\
    }\
    for (int J = 1; J <= DEGREE; ++J)\
    {\
        for (int I = DEGREE; I >= J; --I)\
        {\
            int KNOT_INDEX = K - DEGREE + I;\
            double DENOMINATOR = KNOTS[KNOT_INDEX + DEGREE + 1 - J] - KNOTS[KNOT_INDEX];\
            double ALPHA = 0.0;\
            if (DENOMINATOR > 1e-9)\
            {\
                ALPHA = (U - KNOT[KNOT_INDEX]) / DENOMINATOR;\
            }\
            D[I].X = (1.0 - ALPHA) * D[I - 1].X + ALPHA * D[I].X;\
            D[I].Y = (1.0 - ALPHA) * D[I - 1].Y + ALPHA * D[I].Y;\
        }\
    }\
    return D[DEGREE]; }()

#endif // BSPLINE_HPP