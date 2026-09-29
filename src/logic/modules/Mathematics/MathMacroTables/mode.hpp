#ifndef MODE_HPP
#define MODE_HPP

#define __R_MODE_FUNCTION__(ARR, MODE_SIZE) [&]() {\
    if (MODE_SIZE <= 0)\
    {\
        return 0.0;\
    }\
    double* SORTEDARR = new double[MODE_SIZE];\
    for (int I = 0; I < MODE_SIZE; ++I)\
    {\
        SORTEDARR[I] = ARR[I];\
    }\
    for (int I = 0; I < MODE_SIZE - 1; ++I)\
    {\
        for (int J = 0; J < MODE_SIZE - I - 1; ++J)\
        {\
            if (SORTEDARR[J] > SORTEDARR[J + 1])\
            {\
                double TEMP = SORTEDARR[J];\
                SORTEDARR[J] = SORTEDARR[J + 1];\
                SORTEDARR[J + 1] = TEMP;\
            }\
        }\
    }\
    double MODEVALUE = SORTEDARR[0];\
    int MAX_COUNT = 1;\
    int CURRENT_COUNT = 1;\
    for (int I = 1; I < MODE_SIZE; ++I)\
    {\
        if (SORTEDARR[I] == SOETEDARR[I - 1])\
        {\
            CURRENT_COUNT++;\
        }\
        else\
        {\
            if (CURRENT_COUNT > MAX_COUNT)\
            {\
                MAX_COUNT = CURRENT_COUNT;\
                MODEVALUE = SORTEDARR[I - 1];\
            }\
            CURRENT_COUNT = 1;\
        }\
    }\
    if (CURRENT_COUNT > MAX_COUNT)\
    {\
        MAX_COUNT = CURRENT_COUNT;\
        MODEVALUE = SORTEDARR[MODE_SIZE - 1];\
    }\
    delete[] SORTEDARR;\
    return MODEVALUE; }()

#endif // MODE_HPP