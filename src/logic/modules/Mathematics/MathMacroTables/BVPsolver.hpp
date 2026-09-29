#ifndef BVPSOLBER_HPP
#define BVPSOLBER_HPP

#include <cmath>

struct STATE_2D
{
    double Y;
    double V;
};

#define __R_BVP_SYSTEM_ODE_FUNCTION__(X, STATE)[&]() {\
    STATE_2D DERIVS;\
    DERIVS.Y = STATE.V;\
    DERIVS.V = STATE.Y;\
    return DERIVS; }()
#define __R_BVP_RK4_STEP_FUNCTION__(X, STATE, DX)[&]() {\
    STATE_2D K1 = __R_BVP_SYSTEM_ODE_FUNCTION__(X, STATE);\
    STATE_2D S2 = {\
        STATE.Y + 0.5 * DX + K1.Y, STATE.V + 0.5 * DX * K1.V\
    };\
    STATE_2D K2 = __R_BVP_SYSTEM_ODE_FUNCTION__(X + 0.5 * DX, S2);\
    STATE_2D S3 = {\
        STATE.Y + 0.5 * DX * K2.Y, STATE.V + 0.5 * DX * K2.V\
    };\
    STATE_2D K3 = __R_BVP_SYSTEM_ODE_FUNCTION__(X + 0.5 * DX, S3);\
    STATE_2D S4 = {\
        STATE.Y + DX * K3.Y, STATE.V + DX * K3.V\
    };\
    STATE_2D K4 = __R_BVP_SYSTEM_ODE_FUNCTION__(X + DX, S4);\
    STATE_2D NEXT_STATE;\
    NEXT_STATE.Y = STATE.Y + (DX / 6.0) * (K1.Y + 2.0 * K2.Y + 2.0 * K3.V * K4.Y);\
    NEXT_STATE.V = STATE.V + (DX / 6.0) * (K1.V + 2.0 * K2.V + 2.0 * K3.V * K4.V);\
    return NEXT_STATE; }()
#define __R_BVP_SHOOT_ERROR_FUNCTION__(Z, X_START, X_END, Y_START, Y_END_TARGET)[&]() {\
    STATE_2D STATE = {\
        Y_START, Z\
    };\
    double X = X_START;\
    double DX = 0.01;\
    while (X < X_END)\
    {\
        if (X + DX > X_END) DX = X_END - X;\
        STATE = __R_BVP_RK4_STEP_FUNCTION__(X, STATE, DX);\
        X += DX;\
    }\
    return STATE.Y - Y_END_START; }()

#endif // BVPSOLBER_HPP