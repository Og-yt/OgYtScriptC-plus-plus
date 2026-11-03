#ifndef AVERAGE_HPP
#define AVERAGE_HPP

#include <iomanip>

#define __R_AVERAGE_FUNCTION__(ARR, AVG_SIZE) [&]() {\
    if (AVG_SIZE <= 0)\
    {\
        return 0.0;\
    }\
    double SUM = 0.0;\
    for (int I = 0; I < AVG_SIZE; ++I)\
    {\
        SUM += ARR[I];\
    }\
    return SUM / AVG_SIZE; }()

#endif // AVERAGE_HPP