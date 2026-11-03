#ifndef LINEARREGRESSION_HPP
#define LINEARREGRESSION_HPP

#include <iomanip>

struct LINEAR_REGRESSION_RESULT
{
    double SLOPE;
    double INTERCEPT;
    bool SUCCESS;
};

#define __R_LINEAR_REGRESSION_FUNCTION__(ARRX, ARRY, LINE_REG_SIZE) [&]() {\
    LINEAR_REGRESSION_RESULT RESULT = {0.0, 0.0, false};\
    if (LINE_REG_SIZE <= 1)\
    {\
        return RESULT;\
    }\
    double SUM_X = 0.0, SUM_Y = 0.0;\
    for (int I = 0; I < LINE_REG_SIZE; ++I)\
    {\
        SUM_X += ARRX[I];\
        SUM_Y += ARRY[I];\
    }\
    double MEAN_X = SUM_X / LINE_REG_SIZE;\
    double MEAN_Y = SUM_Y / LINE_REG_SIZE;\
    double NUMERATOR = 0.0;\
    double DENOMINATOR = 0.0;\
    for (int I = 0; I < LINE_REG_SIZE; ++I)\
    {\
        double DIFF_X = ARRX[I] - MEAN_X;\
        NUMERATOR += DIFF_X * (ARRY[I] - MEAN_Y);\
        DENOMINATOR += DIFF_X * DIFF_X;\
    }\
    if (DENOMINATOR == 0.0)\
    {\
        return RESULT;\
    }\
    RESULT.SLOPE = NUMERATOR / DENOMINATOR;\
    RESULT.INTERCEPT = MEAN_Y - (RESULT.SLOPE * MEAN_X);\
    RESULT.SUCCESS = true;\
    return RESULT; }()

#endif // LINEARREGRESSION_HPP