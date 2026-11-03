#ifndef AIRY_HPP
#define AIRY_HPP

#include <cmath>

namespace AiryConstants {
    constexpr double PI = 3.1415926535897932384626433832795;
}

inline double __airy_l_gamma_lanczos_function(double Z) {
    using namespace AiryConstants;
    static const double P[] = {
        676.5203681218851, -1259.1392167224028, 771.32342877765313,                                            \
        -176.61502916214059, 12.507343278686905, -0.13857109526572012,                                         \
        9.9843695780195716e-6, 1.5056327351493116e-7                                                           \
    };
    if (Z < 0.5) return std::log(PI) - std::log(std::sin(PI * Z)) - __airy_l_gamma_lanczos_function(1.0 - Z);
    double X = 0.99999999999980993;
    for (int I = 0; I < 8; ++I) X += P[I] / (Z + I + 1);
    double T = Z + 7.5;
    return std::log(2.5066282746310005) + (Z + 0.5) * std::log(T) - T + std::log(X);
}

#define __AIRY_L_T_GAMMA_FUNCTION(X) (std::exp(__airy_l_gamma_lanczos_function(X)))
#define __R_AIRY_FUNCTION_A__(X) [&]() {                                                                       \
    if (X > 15.0)                                                                                              \
    {                                                                                                          \
        double Z = std::pow(X, 1.5);                                                                           \
        return std::exp(-2.0 * Z / 3.0) / (2.0 * std::sqrt(PI) * std::pow(X, 0.25));                           \
    }                                                                                                          \
    if (X < -15.0)                                                                                             \
    {                                                                                                          \
        double Z = std::pow(-X, 1.5);                                                                          \
        return std::sin(2.0 * Z / 3.0 + PI / 4.0) / (std::sqrt(PI) * std::pow(-X, 0.25));                      \
    }                                                                                                          \
    double SUM_AI = 0.0;                                                                                       \
    double TERM = 1.0;                                                                                         \
    for (int K = 0; K < 20; ++K)                                                                               \
    {                                                                                                          \
        SUM_AI += TERM;                                                                                        \
        TERM *= std::pow(X,3) / ((3.0 * K + 2.0) * (3.0 * K + 3.0));                                           \
    }                                                                                                          \
    return (1.0 / (3.0 * std::cbrt(3.0) * __AIRY_L_T_GAMMA_FUNCTION(2.0 / 3.0))) * SUM_AI; }()
#define __R_AIRY_FUNCTION_B__(X) [&]() {                                                                       \
    if (X > 10.0)                                                                                              \
    {                                                                                                          \
        double Z = std::pow(X, 1.5);                                                                           \
        return std::exp(2.0 * Z / 3.0) / (std::sqrt(PI) * std::pow(X, 0.25));                                  \
    }                                                                                                          \
    if (X < -15.0)                                                                                             \
    {                                                                                                          \
        double Z = std::pow(-X, 1.5);                                                                          \
        return std::cos(2.0 * Z / 3.0 + PI / 4.0) / (std::sqrt(PI) * std::pow(-X, 0.25));                      \
    }                                                                                                          \
    double SUM_BI = 0.0;                                                                                       \
    double TERM = 1.0;                                                                                         \
    for (int K = 0; K < 20; ++K)                                                                               \
    {                                                                                                          \
        SUM_BI += TERM;                                                                                        \
        TERM *= std::pow(X,3) / ((3.0 * K + 2.0) * (3.0 * K + 3.0));                                           \
    }                                                                                                          \
    return (std::sqrt(3.0) / (3.0 * std::cbrt(3.0) * __AIRY_L_T_GAMMA_FUNCTION(2.0 / 3.0))) * SUM_BI; }()

#endif // AIRY_HPP