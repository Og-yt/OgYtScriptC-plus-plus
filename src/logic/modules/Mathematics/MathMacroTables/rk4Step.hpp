#ifndef RK4STEP_HPP
#define RK4STEP_HPP

#define __R_RK4_STEP_FUNCTION__(F, T, Y, DT)[&]() {\
    double K1 = F(T, Y);\
    double K2 = F(T + 0.5 * DT, Y + 0.5 * DT * K1);\
    double K3 = F(T + 0.5 * DT, Y + 0.5 * DT * K2);\
    double K4 = F(T + DT, Y + DT * K3);\
    return Y + (DT / 6.0) * (K1 + 2.0 * K2 + 2.0 * K3 + K4); }()

#endif // RK4STEP_HPP