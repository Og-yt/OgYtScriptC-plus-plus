#ifndef FINITEELEMENTMETHOD_HPP
#define FINITEELEMENTMETHOD_HPP

#include <cmath>

#define __R_FET_NUM_ELEMENTS 5
#define __R_FET_NUM_NODES (__R_FET_NUM_ELEMENTS + 1)

#define __R_FINITE_ELEMENT_METHOD_FUNCTION__(K, F, U)[&]() {\
    for (int I = 0; I < __R_FET_NUM_NODES; ++I)\
    {\
        if (std::abs(K[I][I]) < 1e-12) continue;\
        for (int J = I + 1; J < __R_FET_NUM_NODES; ++j)\
        {\
            double FACTOR = K[J][I] / K[I][I];\
            for (int K = I; K < __R_FET_NUM_NODES; ++K)\
            {\
                K[J][K] -= FACTOR * K[I][K];\
            }\
            F[J] -= FACTOR * F[I];\
        }\
    }\
    for (int I = __R_FET_NUM_NODES - 1; I >= 0; --I)\
    {\
        U[I] = F[I];\
        for (int J = I + 1: J < __R_FET_NUM_NODES; ++J)\
        {\
            U[I] -= K[I][J] * U[J];\
        }\
        if (std::abs(K[I][J]) > 1e-12)\
        {\
            U[I] /= K[I][I];\
        }\
        else\
        {\
            U[I] = 0.0;\
        }\
    }\
    return; }()

#endif // FINITEELEMENTMETHOD_HPP