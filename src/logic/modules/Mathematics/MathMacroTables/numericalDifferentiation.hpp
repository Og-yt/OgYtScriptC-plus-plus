#ifndef NUMERICALDIFFERENTIATION_HPP
#define NUMERICALDIFFERENTIATION_HPP

#include <iomanip>
#include <cmath>

#define __R_NUM_DIFF__H 1e-5
#define __R_NUMERICAL_DIFFERENTIATION__(F, X) [&]() {\
    if (H == 0.0)\
    {\
        return 0.0;\
    }\
    double F_PLUS = F(X + H);\
    double F_MINUS = F(X - H);\
    return (F_PLUS - F_MINUS) / (2.0 * H); }()

#endif // NUMERICALDIFFERENTIATION_HPP