#ifndef EULERMETHOD_HPP
#define EULERMETHOD_HPP

#include <iomanip>
#include <cmath>

#define __R_EULER_METHOD_FUNCTION__(F, T, Y, H) [&]() { return Y + H * F(T, Y); }()

#endif // EULERMETHOD_HPP