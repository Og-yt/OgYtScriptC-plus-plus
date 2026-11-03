#ifndef QUARTILE_HPP
#define QUARTILE_HPP

#include <iomanip>

struct QUARTILES
{
    double Q1;
    double Q2;
    double Q3;
};

#define __R_QUARTILE_FUNCTION_FIND_SEGMENT_MEDIAN__(ARR, START, END) [&]() {\
    int SEGMENT_SIZE = END - START + 1;\
    if (SEGMENT_SIZE % 2 != 0)\
    {\
        return ARR[START + SEGMENT_SIZE / 2];\
    }\
    else\
    {\
        return (ARR[START + (SEGMENT_SIZE / 2) - 1] + ARR[START + SEGMENT_SIZE / 2]) / 2.0;\
    }\
    return SEGMENT_SIZE; }()
#define __R_QUARTILE_FUNCTION__(ARR, QU_SIZE) [&]() {\
    QUARTILES RESULT = {0.0, 0.0, 0.0};\
    if (QU_SIZE <= 0) return RESULT;\
    double* SORTEDARR = new double[QU_SIZE];\
    for (int I = 0; I < QU_SIZE; ++I)\
    {\
        SORTEDARR[I] = ARR[I];\
    }\
    for (int I = 0; I < QU_SIZE - 1; ++I)\
    {\
        for (int J = 0; J < QU_SIZE - I - 1; ++J)\
        {\
            if (SORTEDARR[J] > SORTEDARR[J + 1])\
            {\
                double TEMP = SORTEDARR[J];\
                SORTEDARR[J] = SORTEDARR[J + 1];\
                SORTEDARR[J + 1] = TEMP;\
            }\
        }\
    }\
    RESULT.Q2 = __R_QUARTILE_FUNCTION_FIND_SEGMENT_MEDIAN__(SORTEDARR, 0, QU_SIZE - 1);\
    if (QU_SIZE % 2 == 0)\
    {\
        int MID = QU_SIZE / 2;\
        RESULT.Q1 = __R_QUARTILE_FUNCTION_FIND_SEGMENT_MEDIAN__(SORTEDARR, 0, MID - 1);\
        RESULT.Q3 = __R_QUARTILE_FUNCTION_FIND_SEGMENT_MEDIAN__(SORTEDARR, MID, QU_SIZE - 1);\
    }\
    else\
    {\
        int MID = QU_SIZE / 2;\
        RESULT.Q1 = __R_QUARTILE_FUNCTION_FIND_SEGMENT_MEDIAN__(SORTEDARR, 0, MID - 1);\
        RESULT.Q3 = __R_QUARTILE_FUNCTION_FIND_SEGMENT_MEDIAN__(SORTEDARR, MID + 1, QU_SIZE - 1);\
    }\
    delete[] SORTEDARR;\
    return RESULT; }()

#endif // QUARTILE_HPP