#ifndef DISPERSION_HPP
#define DISPERSION_HPP

#include <iomanip>
#include <cmath>

struct DISPERSIONRESULT
{
    double VARIANCE;
    double STDDEVIATION;
};

#define __R_DISPERSION_FUNCTION(ARR, DIS_SIZE) [&]() {\
    DISPERSIONRESULT RESULT = {0.0, 0.0};\
    if (DIS_SIZE <= 1)\
    {\
        return RESULT;\
    }\
    double SUM = 0.0;\
    for (int I = 0; I < DIS_SIZE; ++I)\
    {\
        SUM += ARR[I];\
    }\
    double MEAN = SUM / DIS_SIZE;\
    double SQUAREDDIFFSUM = 0.0;\
    for (int I = 0; I < DIS_SIZE; ++I)\
    {\
        double DIFF = ARR[I] - MEAN;\
        SQUAREDDIFFSUM += std::pow(DIFF,2);\
    }\
    RESULT.VARIANCE = SQUAREDDIFFSUM / DIS_SIZE;\
    RESULT.STDDEVIATION = std::sqrt(RESULT.VARIANCE);\
    return RESULT; }()

#endif // DISPERSION_HPP