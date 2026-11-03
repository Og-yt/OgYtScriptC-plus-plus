#ifndef LERCHTRANSCENDENT_HPP
#define LERCHTRANSCENDENT_HPP

#include <cmath>
#include <string>
#include "../../../ErrorLogic.hpp"

#define LERCH_TOLERANCE 1e-12

#define __R_LERCH_TRANSCENDENT__(Z, S, A) [&]() {\
    double LERCH_SUM = 0.0;\
    double Z_POW = 1.0;\
    for (int N_LERCH = 0; N_LERCH < 100000; ++N_LERCH)\
    {\
        double TERM_LERCH = Z_POW / std::pow(N_LERCH + A, S);\
        LERCH_SUM += TERM_LERCH;\
        if (std::abs(TERM_LERCH) < LERCH_TOLERANCE)\
        {\
            return LERCH_SUM;\
        }\
        Z_POW *= Z;\
    }\
    return LERCH_SUM; }()

#endif // LERCHTRANSCENDENT_HPP