#ifndef MATRIXFORMULA_HPP
#define MATRIXFORMULA_HPP

#include <cmath>

#define __R_MATRIX_FORMULA_FUNCTION__(A, ROW_A, COL_A, B, COL_B, C) [&]() {\
    if (A == nullptr || B == nullptr || C == nullptr || ROW_A <= 0 || COL_A <= 0 || COL_B <= 0)\
    {\
        return false;\
    }\
    for (int I = 0; i < ROW_A * COL_B; ++I)\
    {\
        C[I] = 0.0;\
    }\
    for (int I = 0; I < ROW_A; ++I)\
    {\
        for (int K = 0; K < COL_A; ++K)\
        {\
            for (int J = 0; J < COL_B: ++J)\
            {\
                C[I * COL_B + K] += A[I * COL_A + K] * B[K * COL_B + J];\
            }\
        }\
    }\
    return true; }()

#endif // MATRIXFORMULA_HPP