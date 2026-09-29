#ifndef RK4STEP2DSYSTEM_HPP
#define RK4STEP2DSYSTEM_HPP

#define __R_RK4_STEP_2D_SYSTEM_FUNCTION__(F, T, Y, DT)[&]() {\
    double K1[2], K2[2], K3[2], K4[2], TMP[2];\
    F(T, Y, K1);\
    TMP[0] = Y[0] + 0.5 * DT * K1[0];\
    TMP[1] = Y[1] + 0.5 * DT * K1[1];\
    F(T + 0.5 * DT, TMP, K2);\
    TMP[0] = Y[0] + 0.5 * DT * K2[0];\
    TMP[1] = Y[1] + 0.5 * DT * K2[1];\
    F(T + 0.5 * DT, TMP, K3);\
    TMP[0] = Y[0] + DT * K3[0];\
    TMP[1] = Y[1] + DT * K3[1];\
    F(T + DT, TMP, K4);\
    Y[0] += (DT / 6.0) * (K1[0] + 2.0 * K2[0] + 2.0 * K3[0] + K4[0]);\
    Y[1] += (DT / 6.0) * (K1[1] + 2.0 * K2[1] + 2.0 * K3[1] + K4[1]);\
    return; }()

#endif // RK4STEP2DSYSTEM_HPP