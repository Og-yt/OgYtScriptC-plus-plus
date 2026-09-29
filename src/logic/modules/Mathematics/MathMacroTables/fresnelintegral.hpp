#ifndef FRESNELINTEGRAL_HPP
#define FRESNELINTEGRAL_HPP

#include <cmath>
#include <utility>

#define PI 3.1415926535897932384626433832795
#define MAX_ITER 100
#define __R_FRESNEL_INTEGRAL_FACTOR__(A, B, C, D, E) [&]() {(2.0 * A) * (2.0 * A + 1.0);B *= std::pow(C,2) / E;B *= (2.0 * A - 1.0) / (2.0 * A + 1.0);C = (2.0 * A + 1.0) * (2.0 * A + 2.0);D *= std::pow(C,2) / E;D *= (2.0 * A - 1.0) / (2.0 * A + 3.0); }()
// A = BR, B = N, C = BI, D = AX, E = AR, F = AI, G = CR, H = CI, I = DR, J = DI, K = FR, L = FI, M = DENOM, N = DELTA_R, O = DELTA_I, P = NEXT_FR
#define __R_FRESNEL_INTEGRAL_UPDATER__(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q) [&]() {\
    A = (B % 2 == 1) ? 1.0 : 0.0;\
    C = (B % 2 == 1) ? 0.0 : D;\
    M = (A + E * I - F * J) * (A + E * I - F * J) + (C + E * J + F * I) * (C + E * J + F * I);\
    I = (A + E * I - F * J) / M;\
    J = -(C + E * J + F * I) / M;\
    G = A + E * G - F * H;\
    H = C + E * H + F * G;\
    if (G == 0.0 && H == 0.0) G = 1e-30;\
    N = G * I - H * J;\
    O = G * J + H * I;\
    P = K * N - L * O;\
    L = K * O + L * N;\
    K = P;\
}()
#define __R_FRESNEL_INTEGRAL__(X) [&]() {\
    long double EPSILON = 1e-15;\
    bool IS_NEGATIVE = false;\
    if (X < 0.0)\
    {\
        X = -X;\
        IS_NEGATIVE = true;\
    }\
    if (X == 0.0)\
    {\
        return\
        {\
            0.0, 0.0\
        }\
    }\
    double C, S = 0.0;\
    if (X <= 2.5)\
    {\
        double AX = 0.5 * PI * X * X;\
        double TERM_C = X;\
        double TERM_S = (X * AX) / 3.0;\
        C = TERM_C;\
        S = TERM_S;\
        int N = 1;\
        bool SIGN = false;\
        while (N < MAX_ITER)\
        {\
            __R_FRESNEL_INTEGRAL_FACTOR__(N, TERM_C, TERM_S, C, FACTOR);\
            if (!SIGN)\
            {\
                C -= TERM_C;\
                S -= TERM_S;\
            }\
            else\
            {\
                C += TERM_C;\
                S += TERM_S;\
            }\
            if (std::abs(TERM_C) < EPSILON && std::abs(TERM_S) < EPSILON) break;\
            SIGN = !SIGN;\
            N++;\
        }\
    }\
    else\
    {\
        double AX = 0.5 * PI * X * X;\
        double XR = 0.0;\
        double XI = AX;\
        double BR = XR;\
        double BI = XI;\
        if (BR == 0.0 && BI == 0.0) BR = 1e-30;\
        double CR = BR;\
        double CI = BI;\
        double DR = 0.0;\
        double DI = 0.0;\
        double FR = BR;\
        double FI = BI;\
        int N = 1;\
        while (N < MAX_ITER)\
        {\
            double AR, AI;\
            if (N % 2 == 1)\
            {\
                AR = 0.5 * (N + 1.0);\
                AI = 0.0;\
            }\
            else\
            {\
                AR = 0.0;\
                AI = 0.5 * N;\
            }\
            __R_FRESNEL_INTEGRAL_UPDATER__(BR, N, BI, XI, AR, AI, CR, CI, DR, DI, FR, FI, DENOM, DELTA_R, DELTA_I, NEXT_FR, NEXT_FI);\
            if (std::abs(DELTA_R - 1.0) < EPSILON && std::abs(DELTA_I) < EPSILON)\
            {\
                break;\
            }\
            N++;\
        }\
        double FX = FR;\
        double GX = FI;\
        C = 0.5 + (FX * std::sin(AX) - GX * std::cos(AX)) / (PI * X);\
        S = 0.5 - (FX * std::cos(AX) + GX * std::sin(AX)) / (PI * X);\
    }\
    if (IS_NEGATIVE)\
    {\
        C = -C;\
        S = -S;\
    }\
    return\
    {\
        C, S\
    } }()

#endif // FRESNELINTEGRAL_HPP