#ifndef DWT_HPP
#define DWT_HPP

#include <iomanip>
#include <cmath>

#define __R_DWT_FUNCTION__(INPUT, OUTPUT, N) [&]() {\
    if (N <= 0 || N % 2 != 0)\
    {\
        return;\
    }\
    int HALF = N / 2;\
    const double SQRT_2_INV = 0.70710678118654752440;\
    for (int I = 0; I < HALF; ++I)\
    {\
        double X0 = INPUT[2 * I];\
        double X1 = INPUT[2 * I + 1];\
        OUTPUT[I] = (X0 + X1) * SQRT_2_INV;\
        OUTPUT[I + HALF] = (X0 - X1) * SQRT_2_INV;\
    }\
    return false; }()

#endif // DWT_HPP