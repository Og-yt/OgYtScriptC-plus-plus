#ifndef MATRIXPRODUCT_HPP
#define MATRIXPRODUCT_HPP

#include <cmath>

#define __R_MATRIX_PRODUCT_FUNCTION__(A, R1, C1, B, R2, C2, C) [&]() {\
    for (int I = 0; I < R1; ++I)\
    {\
        for (int J = 0; J < C2; ++J)\
        {\
            C[I][J] = 0;\
            for (int K = 0; K < C1; ++K)\
            {\
                C[I][J] += A[I][K] * B[K][J];\
            }\
        }\
    }\
    return false; }()

#endif // MATRIXPRODUCT_HPP