#ifndef COVARIANCE_HPP
#define COVARIANCE_HPP

#include <iomanip>

#define __R_COVARIANCE_FUNCTION__(ARRX, ARRY, CON_SIZE) [&]() {\
    if (CON_SIZE <= 0)\
    {\
        return 0.0;\
    }\
    double SUMX = 0.0;\
    double SUMY = 0.0;\
    for (int I = 0; I < CON_SIZE; ++I)\
    {\
        SUMX += ARRX[I];\
        SUMY += ARRY[I];\
    }\
    double MEANX = SUMX / CON_SIZE;\
    double MEANY = SUMY / CON_SIZE;\
    double TOTAL_PRODUCT_DIFF = 0.0;\
    for (int I = 0; I < CON_SIZE; ++I)\
    {\
        TOTAL_PRODUCT_DIFF += (ARRX[I] - MEANX) * (ARRY[I] - MEANY);\
    }\
    return TOTAL_PRODUCT_DIFF / CON_SIZE; }()

#endif // COVARIANCE_HPP