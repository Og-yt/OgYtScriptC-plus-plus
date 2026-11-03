#ifndef STANDARDDEVIATION_HPP
#define STANDARDDEVIATION_HPP

#include <iomanip>
#include <cmath>

#define __R_STANDARD_DEVIATION_FUNCTION__(ARR, STD_SIZE) [&]() {\
    if (STD_SIZE <= 0)\
    {\
        return 0.0;\
    }\
    double SUM = 0.0;\
    for (int I = 0; I < STD_SIZE; ++I)\
    {\
        SUM += ARR[I];\
    }\
    double MEAN = SUM / STD_SIZE;\
    double SQUAREDDIFFSUM = 0.0;\
    for (int I = 0; I < STD_SIZE; ++I)\
    {\
        double DIFF = ARR[I] - MEAN;\
        SQUAREDDIFFSUM += DIFF * DIFF;\
    }\
    double VARIANCE = SQUAREDDIFFSUM / STD_SIZE;\
    return std::sqrt(VARIANCE); }()

#endif // STANDARDDEVIATION_HPP