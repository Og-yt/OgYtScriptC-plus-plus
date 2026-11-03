#ifndef EQUATION_HPP
#define EQUATION_HPP

#include <cmath>
#include <numbers>

#define __R_LINEAR_EQUATION__(A, B, C, D) \
    [&]() {\
    if (std::abs(A - C) < 1e-9) { return std::numeric_limits<double>::quiet_NaN(); }\
    else { return (B - D) / (A - C);} }()

#define __NUMERATOR_QUADRATIC_EQUATION__PULS__(A, B, C) [&]() { (-B + std::sqrt(std::pow(B, 2) - 4 * A * C)) / (4 * A * C); }()
#define __NUMERATOR_QUADRATIC_EQUATION__MINUS__(A, B, C) [&]() { (-B - std::sqrt(std::pow(B, 2) - 4 * A * C)) / (4 * A * C); }()
#define __R_QUADRATIC_EQUATION__(A, B, C) [&]() {\
    __NUMERATOR_QUADRATIC_EQUATION__PULS__(A, B, C); \
    __NUMERATOR_QUADRATIC_EQUATION__MINUS__(A, B, C); return false; }()

#define __R_CUBIC_EQUATION_NO_1__ZERO__(A) [&]() {if (std::abs(A) < 1e-9) { return std::numeric_limits<double>::quiet_NaN();} }()
#define __R_CUBIC_EQUATION_REVERSE_TRANSRATION__(A, B) [&]() { double X = A - B / 3.0; return X; }()
#define __R_CUBIC_EQUATION_DELTA_THAT_ALL_0__(DELTA, Q) \
    [&]() {\
    double SD = std::sqrt(DELTA);\
    double U = std::cbrt(-Q / 2.0 + SD);\
    double V = std::cbrt(-Q / 2.0 - SD);\
    double Y = U + V;\
    return Y; }()
#define __R_CUBIC_EQUATION_DELTA_ELSE__(P, Q) \
    [&]() { \
        double R = std::sqrt(-std::pow(P / 3.0, 3));\
        double THETA = std::acos(-Q / (2.0 * R));\
        double Y = 2.0 * std::cbrt(R) * std::cos(THETA / 3.0);\
        return Y; }()
#define __R_CUBIC_EQUATION_CALCURATION__(A, B, C, D) [&]() {\
    double Ax = B / A;\
    double Bx = C / A;\
    double Cx = D / A;\
    double Dx = B - std::pow(A,2) / 3.0;\
    double Ex = C + (2.0 * std::pow(A,3)) / 27.0 - (A * B) / 3.0;\
    double Fx = std::pow(Ex / 2.0, 2) + std::pow(Dx / 3.0, 3);\
    double Gx;\
    if (Fx >= 0){Gx = __R_CUBIC_EQUATION_DELTA_THAT_ALL_0__(Fx, Ex);}\
    else { Gx = __R_CUBIC_EQUATION_DELTA_ELSE__(Dx, Ex);}\
    __R_CUBIC_EQUATION_REVERSE_TRANSRATION__(Gx, Ax); return false;}()
#define __R_CUBIC_EQUATION__(A, B, C, D) \
    [&]() {\
        __R_CUBIC_EQUATION_NO_1__ZERO__(A);\
        __R_CUBIC_EQUATION_CALCURATION__(A, B, C, D); return false; }()

#endif // EQUATION_HPP