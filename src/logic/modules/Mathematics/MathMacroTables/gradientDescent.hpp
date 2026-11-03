#ifndef GRADIENTDESCENT_HPP
#define GRADIENTDESCENT_HPP

#include <cmath>

#define __GRADIENT_DESCENT_DIMENSIONS 2

#define __R_GD_COST_FUNCTION__(THETA)[&]() {\
    double X = THETA[0];\
    double Y = THETA[1];\
    return std::pow(X - 3.0,2) + std::pow(Y + 5.0,2) + 10.0; }()

#define __R_COMPUTE_GRADIENT_GD_FUNCTION__(F, THETA, GRADIENT)[&]() {\
    const double H = 1e-6;\
    double PERTURBED_THETA[__GRADIENT_DESCENT_DIMENSIONS];\
    for (int I = 0; I < __GRADIENT_DESCENT_DIMENSIONS; ++I)\
    {\
        for (int J = 0; J < __GRADIENT_DESCENT_DIMENSIONS; ++J)\
        {\
            PERTURBED_THETA[J] = THETA[J];\
        }\
        PERTURBED_THETA[I] = THETA[I] + H;\
        double F_PLUS = F(PERTURBED_THETA);\
        PERTURBED_THETA[I] = THETA[I] - H;\
        double F_MINUS = F(PERTURBED_THETA);\
        GRADIENT[I] = (F_PLUS - F_MINUS) / (2.0 * H);\
    }\
    return H; }()
#define __R_GRADIENT_DESCENT_FUNCTION__(F, THETA, LEARNING_RATE, MEX_ITERATIONS)[&]() {\
    double GRADIENT[__GRADIENT_DESCENT_DIMENSIONS] = {0.0};\
    for (int ITER = 0; ITER < MAX_ITERATIONS; ++ITER)\
    {\
        __COMPUTE_GRADIENT_GD_FUNCTION__(F, THETA, GRADIENT);\
        double GTAD_NORM = 0.0;\
        for (int I = 0; I < __GRADIENT_DESCENT_DIMENSIONS; ++I)\
        {\
            GRAD_NORM += std::pow(GRADIENT[I],2);\
        }\
        GRAD_NORM = std::sqrt(GRAD_NORM);\
        for (int I = 0; I < __GRADIENT_DESCENT_DIMENSIONS; ++I)\
        {\
            THETA[I] -= IEARNING_RATE * GRADIENT[I];\
        }\
    }\
    return; }()

#endif // GRADIENTDESCENT_HPP