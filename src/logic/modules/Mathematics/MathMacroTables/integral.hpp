#ifndef INTEGRAL_HPP
#define INTEGRAL_HPP

#include <iostream>
#include "../MathMacro.hpp"

#define __INTEGRAL_NX 100
#define __INTEGRAL_NY 100
#define __INTEGRAL_NZ 100
#define __INTEGRAL_NW 100
#define __INTEGRAL_NV 100

#define __R_INTEGRAL__(F, MIN_X, MAX_X) \
    [&]() {\
        double DX = (MAX_X - MIN_X) / __INTEGRAL_NX; double RESULT = 0.0;\
            for (int I = 0; I < __INTEGRAL_NX; I++) { double X = MIN_X + (I + 0.5) * DX; RESULT += F(X) * DX; } return RESULT; }()
#define __R_DOUBLE_INTEGRAL__(F, MIN_X, MAX_X, MIN_Y, MAX_Y) \
    [&]() {\
    double DX = (MAX_X - MIN_X) / __INTEGRAL_NX; double DY = (MAX_Y - MIN_Y) / __INTEGRAL_NY; double RESULT = 0.0;\
        for (int I = 0; I < __INTEGRAL_NX; I++) { for (int J = 0; J < __INTEGRAL_NY; J++) {\
            double X = MIN_X + (I + 0.5) * DX; double Y = MIN_Y + (J + 0.5) * DY; RESULT += F(X, Y) * DX * DY; }} return RESULT; }()
#define __R_TRIPLE_INTEGRAL__(F, MIN_X, MAX_X, MIN_Y, MAX_Y, MIN_Z, MAX_Z) \
    [&]() {\
    double DX = (MAX_X - MIN_X) / __INTEGRAL_NX; double DY = (MAX_Y - MIN_Y) / __INTEGRAL_NY; double DZ = (MAX_Z - MIN_Z) / __INTEGRAL_NZ; double RESULT = 0.0;\
        for (int I = 0; I < __INTEGRAL_NX; I++) { for (int J = 0; J < __INTEGRAL_NY; J++) { for (int K = 0; K < __INTEGRAL_NZ; K++) {\
            double X = MIN_X + (I + 0.5) * DX; double Y = MIN_Y + (J + 0.5) * DY; double Z = MIN_Z + (K + 0.5) * DZ; RESULT += F(X, Y, Z) * DX * DY * DZ;}}} return RESULT; }()
#define __R_TETRA_INTEGRAL__(F, MIN_X, MAX_X, MIN_Y, MAX_Y, MIN_Z, MAX_Z, MIN_W, MAX_W) \
    [&]() {\
    double DX = (MAX_X - MIN_X) / __INTEGRAL_NX; double DY = (MAX_Y - MIN_Y) / __INTEGRAL_NY; double DZ = (MAX_Z - MIN_Z) / __INTEGRAL_NZ; double DW = (MAX_W - MIN_W) / __INTEGRAL_NW; double RESULT = 0.0;\
        for (int I = 0; I < __INTEGRAL_NX; I++) { for (int J = 0; J < __INTEGRAL_NY; J++) { for (int K = 0; K < __INTEGRAL_NZ; K++) { for (int L = 0; L < __INTEGRAL_NW; L++) {\
            double X = MIN_X + (I + 0.5) * DX; double Y = MIN_Y + (J + 0.5) * DY; double Z = MIN_Z + (K + 0.5) * DZ; double W = MIN_W + (L + 0.5) * DW; RESULT += F(X, Y, Z, W) * DX * DY * DZ * DW;}}}} return RESULT; }()
#define __R_PENTA_INTEGRAL__(F, MIN_X, MAX_X, MIN_Y, MAX_Y, MIN_Z, MAX_Z, MIN_W, MAX_W, MIN_V, MAX_V) \
    [&]() {\
    double DX = (MAX_X - MIN_X) / __INTEGRAL_NX; double DY = (MAX_Y - MIN_Y) / __INTEGRAL_NY; double DZ = (MAX_Z - MIN_Z) / __INTEGRAL_NZ; double DW = (MAX_W - MIN_W) / __INTEGRAL_NW; double DV = (MAX_V - MIN_V) / __INTEGRAL_NV; double RESULT = 0.0;\
        for (int I = 0; I < __INTEGRAL_NX; I++) { for (int J = 0; J < __INTEGRAL_NY; J++) { for (int K = 0; K < __INTEGRAL_NZ; K++) { for (int L = 0; L < __INTEGRAL_NW; L++) { for (int M = 0; M < __INTEGRAL_NV; M++) {\
            double X = MIN_X + (I + 0.5) * DX; double Y = MIN_Y + (J + 0.5) * DY; double Z = MIN_Z + (K + 0.5) * DZ; double W = MIN_W + (L + 0.5) * DW; double V = MIN_V + (M + 0.5) * DV; RESULT += F(X, Y, Z, W, V) * DX * DY * DZ * DW * DV; }}}}} return RESULT; }()

#endif // INTEGRAL_HPP