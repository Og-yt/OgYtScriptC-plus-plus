#ifndef COMFORMALMAPPING_HPP
#define COMFORMALMAPPING_HPP

#include <complex>

using COMPLEX_COM_MAP = std::complex<double>;

#define __R_COMFORMAL_MAPPING_FUNCTION__(A, B, C, D)[&]() { if (A * D - B * C == 0.0) { return COMPLEX_COM_MAP(0.0, 0.0); } return (A * Z + B) / (C * Z + D); }()

#endif // COMFORMALMAPPING_HPP