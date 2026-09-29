#ifndef IFFT_HPP
#define IFFT_HPP

#include <iomanip>
#include <cmath>

struct __IFFT_COMPLEXSCALAR
{
    double REAL;
    double IMAG;
};

#define __BIT_REVERSE_PERMUTE__(DATA, N) [&]() {\
    int J = 0;\
    for (int I = 0; I < N; ++I)\
    {\
        if (I < J)\
        {\
            __IFFT_COMPLEXSCALAR TEMP = DATA[I];\
            DATA[I] = DATA[J];\
            DATA[J] = TEMP;\
        }\
        int BIT = N >> 1;\
        while (J & BIT)\
        {\
            J ^= BIT;\
            BIT >>= 1;\
        }\
        J |= BIT;\
    }\
    return false; }()
#define __R_IFFT_FUNCTION__(DATA, N) [&]() {\
    if (N < 2) return false;\
    __BIT_REVERSE_PERMUTE__(DATA, N);\
    const double M_PI = 3.14159265358979323846;\
    for (int LEN = 2; LEN <= N; LEN <<= 1)\
    {\
        double ANGLE = 2.0 * M_PI / LEN;\
        __IFFT_COMPLEXSCALAR WLEN;\
        WLEN.REAL = std::cos(ANGLE);\
        WLEN.IMAG = std::sin(ANGLE);\
        for (int I = 0; I < N; I += LEN)\
        {\
            __IFFT_COMPLEXSCALAR W;\
            W.REAL = 1.0;\
            W.IMAG = 0.0;\
            int HALF_LEN = LEN >> 1;\
            for (int J = 0; J < HALF_LEN; ++J)\
            {\
                __IFFT_COMPLEXSCALAR U = DATA[I + J];\
                __IFFT_COMPLEXSCALAR V = DATA[I + J + HALF_LEN];\
                double V_REAL_WEIGHTED = V.REAL * W.REAL - V.IMAG * W.IMAG;\
                double V_IMAG_WEIGHTED = V.REAL * W.IMAG + V.IMAG * W.REAL;\
                DATA[I + J].REAL = U.REAL + V_REAL_WEIGHTED;\
                DATA[I + J].IMAG = U.IMAG + V_IMAG_WEIGHTED;\
                DATA[I + J + HALF_LEN].REAL = U.REAL - V_REAL_WEIGHTED;\
                DATA[I + J + HALF_LEN].IMAG = U.IMAG - V_IMAG_WEIGHTED;\
                double NEXT_W_REAL = W.REAL * WLEN.REAL - W.IMAG * WLEN.IMAG;\
                double NEXT_W_IMAG = W.REAL * WLEN.IMAG + W.IMAG * WLEN.REAL;\
                W.REAL = NEXT_W_REAL;\
                W.IMAG = NEXT_W_IMAG;\
            }\
        }\
    }\
    for (int I = 0; I < N; ++I)\
    {\
        DATA[I].REAL /= N;\
        DATA[I].IMAG /= N;\
    }\
    return false; }()

#endif // IFFT_HPP