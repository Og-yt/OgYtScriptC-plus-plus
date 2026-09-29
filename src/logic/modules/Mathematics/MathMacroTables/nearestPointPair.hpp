#ifndef NEARESTPOINTPAIR_HPP
#define NEARESTPOINTPAIR_HPP

#include <iomanip>
#include <cmath>

struct __NEA_PP_POINT_2D
{
    double X;
    double Y;
};

struct POINT_PAIR_RESULT
{
    __NEA_PP_POINT_2D P1;
    __NEA_PP_POINT_2D P2;
    double DISTANCE;
};

#define __R_NEAREST_POINT_PAIR_FUNCTION__(INPUT, N) [&]() {\
    POINT_PAIR_RESULT RESULT = {\
        {0.0, 0.0},\
        {0.0, 0.0},\
        -1.0\
    };\
    if (N < 2) return RESULT;\
    RESULT.P1 = INPUT[0];\
    RESULT.P2 = INPUT[1];\
    double DX = INPUT[1].X - INPUT[0].X;\
    double DY = INPUT[1].Y - INPUT[0].Y;\
    double MIN_DISTANCE_SQ = (DX * DX) + (DY * DY);\
    for (int I = 0; I < N - 1; ++I)\
    {\
        for (int J = I + 1; J < N; ++J)\
        {\
            double CURRENT_DX = INPUT[J].X - INPUT[I].X;\
            double CURRENT_DY = INPUT[J].Y - INPUT[I].Y;\
            double CURRENT_DISTANCE_SQ = (std::pow(CURRENT_DX,2) + std::pow(CURRENT_DY,2));\
            if (CURRENT_DISTANCE_SQ < MIN_DISTANCE_SQ)\
            {\
                MIN_DISTANCE_SQ = CURRENT_DISTANCE_SQ;\
                RESULT.P1 = INPUT[I];\
                RESULT.P2 = INPUT[J];\
            }\
        }\
    }\
    RESULT.DISTANCE = std::sqrt(MIN_DISTANCE_SQ);\
    return RESULT; }()

#endif // NEARESTPOINTPAIR_HPP