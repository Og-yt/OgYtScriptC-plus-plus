#ifndef BEZIERCURVE_HPP
#define BEZIERCURVE_HPP

#include <iomanip>

#define __BEZIER_MAX_CONTROL_POINT 16

struct __BEZ_CURVE_POINT_2D
{
    double X;
    double Y;
};

#define __R_BEZIER_CURVE_FUNCTION__(CONTROL_POINTS, NUM_POINT, T) [&]() {\
    if (NUM_POINT <= 0) return { 0.0, 0.0 };\
    if (NUM_POINT == 1) return CONTROL_POINTS[0];\
    if (NUM_POINT > __BEZIER_MAX_CONTROL_POINT)\
    {\
        NUM_POINT = __BEZIER_MAX_CONTROL_POINT;\
    }\
    __BEZ_CURVE_POINT_2D LOCAL_POINTS[__BEZIER_MAX_CONTROL_POINT];\
    for (int I = 0; I < NUM_POINTS; ++I)\
    {\
        LOCAL_POINTS[I] = CONTROL_POINTS[I];\
    }\
    for (int STEP = 1; STEP < NUM_POINT; ++STEP)\
    {\
        int CURREMT_LIMIT = NUM_POINT - STEP;\
        for (int I = 0; I < CURRENT_LIMIT; ++I)\
        {\
            LOCAL_POINTS[I].X = (1.0 - T) * LOCAL_POINTS[I].X + T * LOCAL_POINTS[I + 1].X;\
            LOCAL_POINTS[I].Y = (1.0 - T) * LOCAL_POINTS[I].Y + T * LOCAL_POINTS[I + 1].Y;\
        }\
    }\
    return LOCAL_POINTS[0]; }()

#endif // BEZIERCURVE_HPP