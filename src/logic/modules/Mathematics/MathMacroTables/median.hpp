#ifndef MEDIAN_HPP
#define MEDIAN_HPP

#include <iomanip>

#define __R_MEDIAN_FUNCTION__(ARR, MID_SIZE) [&]() {\
    if (MID_SIZE <= 0)\
    {\
        return 0.0;\
    }\
    double* SORTEDARR = new double[MID_SIZE];\
    for (int I = 0; I < MID_SIZE; ++I)\
    {\
        SORTEDARR[I] = ARR[I];\
    }\
    for (int I = 0; I < MID_SIZE; ++I)\
    {\
        for (int J = 0; J < MID_SIZE - I - 1; ++J)\
        {\
            if (SORTEDARR[J] > SORTEDARR[J + 1])\
            {\
                double TEMP = SORTEDARR[J];\
                SORTEDARR[J] = SORTEDARR[J + 1];\
                SORTEDARR[J + 1] = TEMP;\
            }\
        }\
    }\
    double MIDIAN = 0.0;\
    if (MID_SIZE % 2 != 0)\
    {\
        MIDIAN = SORTEDARR[MID_SIZE / 2];\
    }\
    else\
    {\
        MIDIAN = (SORTEDARR[(MID_SIZE / 2) - 1] + SORTEDARR[MID_SIZE / 2]) / 2.0;\
    }\
    delete[] SORTEDARR;\
    return MIDIAN; }()

#endif // MEDIAN_HPP