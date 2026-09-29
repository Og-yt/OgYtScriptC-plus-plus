#ifndef CARMICHAEL_HPP
#define CARMICHAEL_HPP

#define __CARMICHAEL_GDC_FUNCTION__(A, B)[&](){\
    while (B != 0)\
    {\
        long long TEMP = B;\
        B = A % B;\
        A = TEMP;\
    }\
    return A; }()
#define __CARMICHAEL_LCM_FUNCTION__(A, B)[&](){\
    if (A == 0 || B == 0) return 0;\
    return (A / __CARMICHAEL_GDC_FUNCTION__(A, B)) * B; }()
#define __R_CARMICHAEL_FUNCTION__(N)[&](){\
    if (N <= 0) return 0;\
    if (N == 1) return 1;\
    long long RESULT = 1;\
    long long TEMP_N = N;\
    if (TEMP_N % 2 == 0)\
    {\
        long long P_POWER = 1;\
        int K = 0;\
        while (TEMP_N % 2 == 0)\
        {\
            P_POWER *= 2;\
            K++;\
            TEMP_N /= 2;\
        }\
        long long LAMBDA_2;\
        if (K <= 2)\
        {\
            LAMBDA_2 = P_POWER / 2;\
        }\
        else\
        {\
            LAMBDA_2 = P_POWER / 4;\
        }\
        RESULT = __CARMICHAEL_LCM_FUNCTION__(RESULT, LAMBDA_2);\
    }\
    for (long long P = 3; P * P <= TEMP_N; P += 2)\
    {\
        if (TEMP_N % P == 0)\
        {\
            long long P_POWER = 1;\
            int K = 0;\
            while (TEMP_N % P == 0)\
            {\
                P_POWER *= P;\
                K++;\
                TEMP_N /= P;\
            }\
            long long LAMBDA_P;\
            if (K <= 2)\
            {\
                LAMBDA_P = (P_POWER / P) * (P - 1);\
            }\
            else\
            {\
                LAMBDA_P = (P_POWER / 4) * (P - 1);\
            }\
            RESULT = __CARMICHAEL_LCM_FUNCTION__(RESULT, LAMBDA_P);\
        }\
    }\
    if (TEMP_N > 1)\
    {\
        long long LAMBDA_P = TEMP_N - 1;\
        RESULT = __CARMICHAEL_LCM_FUNCTION__(RESULT, LAMBDA_P);\
    }\
    return RESULT; }()

#endif // CARMICHAEL_HPP