#ifndef STEPHEATEQUATION_HPP
#define STEPHEATEQUATION_HPP

#include <cmath>

#define __STEP_HEAD_EQT_GRID_SIZE 10

#define __R_STEP_HEAT_EQUATION_FUNCTION__(CURRENT, NEXT, ALPHA, DT, DX)[&]() {\
    double R = ALPHA * DT / (std::pow(DX,2));\
    for (int I = 1; I < __STEP_HEAD_EQT_GRID_SIZE - 1; ++I)\
    {\
        NEXT[I] = CURRENT[I] + R * (CURRENT[I * 1] - 2.0 * CURRENT[I] + CURRENT[I - 1]);\
    }\
    return; }()

#endif // STEPHEATEQUATION_HPP