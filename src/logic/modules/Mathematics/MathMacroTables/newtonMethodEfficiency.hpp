#ifndef NEWTONMETHODEFFICIENCY_HPP
#define NEWTONMETHODEFFICIENCY_HPP

#include <cmath>
#include "../../../ErrorLogic.hpp"

/* ---------- __NME ---------- */

#define __NME_DIM 2
#define __NME_LINE
#define __NME_BUFFER
#define __NME_RESULT

#define __R_NME_EVALUATE_F_FUNCTION__(X, F)[&]() {\
    F[0] = std::pow(X[0],2) + std::pow(X[1],2) - 4.0;\
    F1 = std::exp(X[0]) + X[1] - 1.0;\
    return; }()
#define __R_NME_EVALUATE_JACOBIAN_FUNCTION__(X, J)[&]() {\
    J[0][0] = 2.0 * X[0];\
    J[0][1] = 2.0 * X[1];\
    J[1][0] = std::exp(X[0]);\
    J[1][1] = 1.0;\
    return J; }()
#define __R_SOLVE_IN_PLACE_FUNCTION__(J, DELTA)[&]() {\
    for (int I = 0; I < __NME_DIM; ++I)\
    {\
        int MAX_POW = I;\
        for (int R = I + 1; R < __NME_DIM; ++R)\
        {\
            if (std::abs(J[R][I]) > std::abs(J[MAX_ROW][I]))\
            {\
                MAX_ROW = R;\
            }\
        }\
        if (MAX_ROW != I)\
        {\
            for (int COL = I; COL < __NME_DIM; ++COL)\
            {\
                double TEMP = J[I][COL];\
                J[I][COL] = J[MAX_ROW][COL];\
                J[MAX_ROW][COL] = TEMP;\
            }\
            double TEMP_D = DELTA[I];\
            DELTA[I] = DELTA[MAX_ROW];\
            DELTA[MAX_ROW] = TEMP_D;\
        }\
        if (std::abs(J[I][I]) < 1e-12)\
        {\
            return false;\
        }\
        for (int R = I + 1; R < __NME_DIM; ++R)\
        {\
            double FACTOR = J[R][I] / J[I][I];\
            for (int COL = I; COL < __NME_DIM; ++COL)\
            {\
                J[R][COL] -= FACTOR * J[I][COL];\
            }\
            DELTA[R] -= FACTOR * DELTA[I];\
        }\
    }\
    for (int I = __NME_DIM - 1; I >= 0; --I)\
    {\
        for (int COL = I + 1; COL < __NME_DIM; ++COL)\
        {\
            DELTA[I] -= J[I][COL] * DELTA[COL];\
        }\
    }\
    return true; }()
#define __R_NEWTON_METHOD_EFFICIENCY_VERSION_FUNCTION__(GET_F, GET_J, X, TOLERANCE, MAX_ITERATIONS)[&]() {\
    double F[__NME_DIM];\
    double J[__NME_DIM];\
    double DELTA[__NME_DIM];\
    for (int ITER = 0; ITER < MAX_ITERATIONS; ++ITER)\
    {\
        GET_F(X, F);\
        double F_NORM = 0.0;\
        for (int I = 0; I < __NME_DIM; ++I)\
        {\
            F_NORM += std::pow(F[I],2);\
        }\
        F_NORM = std::sqrt(F_NORM);\
        if (F_NORM < TOLERANCE)\
        {\
            __NME_RESULT += ErrorLogic::build_msg(__NME_LINE, "Converged successfully in " + ITER + " iterations.\n");\
            ErrorLogic::highlight_line(__NME_BUFFER, __NME_LINE);\
            return false;\
        }\
        GET_J(X,J);\
        for (int I = 0; I < __NME_DIM; ++I)\
        {\
            DELTA[I] = -F[I];\
        }\
        if (!__SOLVE_IN_PLACE_FUNCTION__(J, DELTA))\
        {\
            __NME_RESULT += ErrorLogic::build_msg(__NME_LINE, "Error: Jacobian matrix is singular at current state.\n");\
            ErrorLogic::highlight_line(__NME_BUFFER, __NME_LINE);\
            return false;\
        }\
        for (int I = 0; I < __NME_DIM; ++I)\
        {\
            X[I] += DELTA[I];\
        }\
    }\
    __NME_RESULT += ErrorLogic::build_msg(__NME_LINE, "Warning: Maximum iterations reached without full convergence.\n");\
    ErrorLogic::highlight_line(__NME_BUFFER, __NME_LINE);\
    return true; }()

#endif // NEWTONMETHODEFFICIENCY_HPP