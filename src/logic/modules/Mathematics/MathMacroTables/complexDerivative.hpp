#ifndef COMPLEXDERIVATIVE_HPP
#define COMPLEXDERIVATIVE_HPP

#include <complex>

using COMPLEX_DERIVATIVE = std::complex<double>;

#define __R_COMPLEX_DERIVATIVE_FUNCTION__(F, Z)[&]() { const COMPLEX_DERIVATIVE H(1e-5, 1e-5); return (F(Z + H) - F(Z - H)) / (2.0 * H); }()

#endif // COMPLEXDERIVATIVE_HPP