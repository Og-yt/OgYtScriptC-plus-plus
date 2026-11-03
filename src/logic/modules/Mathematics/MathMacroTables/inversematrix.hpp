#ifndef INVERSEMATRIX_HPP
#define INVERSEMATRIX_HPP

#include <iomanip>
#include <cmath>

#define __R_INVERSE_MATRIX_FUNCTION__(N, A, INVERSE) [&]() {\
    int AUGCOLS = 2 * N;\
    double* AUG = new double[N * AUGCOLS];\
    for (int I = 0; I < N; I++)\
    {\
        for (int J = 0; J < N; J++)\
        {\
            AUG[I * AUGCOLS + J] = A[I * N + J];\
            AUG[I * AUGCOLS + (J + N)] = (I == J) ? 1.0 : 0.0;\
        }\
    }\
    for (int I = 0; I < N; I++)\
    {\
        int PIVOTROW = I;\
        double MAXVAL = std::abs(AUG[I * AUGCOLS + I]);\
        for (int K = I + 1; K < N; K++)\
        {\
            double VAL = std::abs(AUG[K * AUGCOLS + I]);\
            if (VAL > MAXVAL)\
            {\
                MAXVAL = VAL;\
                PIVOTROW = K;\
            }\
        }\
        if (std::abs(AUG[PIVOTROW * AUGCOLS + I]) < 1e-12)\
        {\
            delete[] AUG;\
            return false;\
        }\
        if (PIVOTROW != I)\
        {\
            for (int J = 0; J < AUGCOLS; J++)\
            {\
                double TEMP = AUG[I * AUGCOLS + J];\
                AUG[I * AUGCOLS + J] = AUG[PIVOTROW * AUGCOLS + J];\
                AUG[PIVOTROW * AUGCOLS + J] = TEMP;\
            }\
        }\
        double PIVOTVAL = AUG[I * AUGCOLS + I];\
        for (int J = I; J < AUGCOLS; J++)\
        {\
            AUG[I * AUGCOLS + J] /= PIVOTVAL;\
        }\
        for (int K = 0; K < N; K++)\
        {\
            if (K != I)\
            {\
                double FACTOR = AUG[K * AUGCOLS + I];\
                for (int J = I; J < AUGCOLS; J++)\
                {\
                    AUG[K * AUGCOLS + J] -= FACTOR * AUG[I * AUGCOLS + J];\
                }\
            }\
        }\
    }\
    for (int I = 0; I < N; I++)\
    {\
        for (int J = 0; J < N; J++)\
        {\
            INVERSE[I * N + J] = AUG[I * AUGCOLS + (J + N)];\
        }\
    }\
    delete[] AUG;\
    return true; }()

#endif // INVERSEMATRIX_HPP