#ifndef RK4STEPCOMPLEX_HPP
#define RK4STEMCOMPLEX_HPP

#include <complex>

using __RK4_STEP_COMPLEX = std::complex<double>;

#define __R_RK4_STEP_COMPLEX_VER_FUNCTION__(F, T, Y, DT) [&]() {\
    __RK4_STEP_COMPLEX K1 = F(T, Y);\
    __RK4_STEP_COMPLEX K2 = F(T + 0.5 * DT, Y + 0.5 * DT * K1);\
    __RK4_STEP_COMPLEX K3 = F(T + 0.5 * DT, Y + 0.5 * DT * K2);\
    __RK4_STEP_COMPLEX K4 = F(T + DT, Y + DT * K3);\
    return Y + (DT / 6.0) * (K1 + 2.0 * K2 + 2.0 * K3 + K4); }()

#endif // RK4STEPCOMPLEX_HPP