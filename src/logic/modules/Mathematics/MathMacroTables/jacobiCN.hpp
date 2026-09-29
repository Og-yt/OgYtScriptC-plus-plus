#ifndef JACOBICN_HPP
#define JACOBICN_HPP

#include "../../../ErrorLogic.hpp"
#include <cmath>

#define __R_JACOBI_CN__(U, M, SN, CN, DN) [&]() {\
    double A, B, C;\
    double EM[13], EN[13];\
    int I, L, M_IDX = 0;\
    A = 1.0;\
    DN = std::sqrt(1.0 - M);\
    B = DN;\
    C = std::sqrt(M);\
    for (I = 0; I < 12; I++)\
    {\
        if (std::abs(C / A) < 1e-15)\
        {\
            M_IDX = I;\
            break;\
        }\
        EM[I] = A;\
        EN[I] = B;\
        double F = A;\
        A = (A + B) / 2.0;\
        B = std::sqrt(F * B);\
        C = (F - B) / 2.0;\
    }\
    double PHI = A * U;\
    for (L = M_IDX - 1; L >= 0; L--)\
    {\
        PHI = (PHI + std::asin(EN[L] * std::sin(PHI) / EM[L])) / 2.0;\
    }\
    SN = std::sin(PHI);\
    CN = std::cos(PHI);\
    DN = std::sqrt(1.0 - M * SN * SN);\
    return true; }()

#endif // JACOBICN_HPP