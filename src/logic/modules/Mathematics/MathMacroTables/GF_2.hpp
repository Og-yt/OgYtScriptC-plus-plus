#ifndef GF_2_HPP
#define GF_2_HPP

#include <iomanip>

#if defined(__x86_64__) || defined(_M_X64)
#include <wmmintrin.h>
#endif

#define __GF_2_ADD_FUNCTION__(A, B)[&]() { return A ^ B; }()
#if defined(__x86_64__) || defined(_M_X64)
    #define __R_GF_2_MULTIPLY_FUNCTION__(A, B, RES_HIGH, RES_LOW)[&]() {\
        __m128i VA = _mm_set_epi64x(0, A);\
        __m128i VB = _mm_set_epi64x(0, B);\
        __m128i VRES = _mm_clmulepi64_si128(VA, VB, 0x00);\
        RES_LOW = _mm_cvtsi128_si64(vres);\
        RES_HIGH = _mm_cvtsi128_si64(VA, VB, 0x00);\
        return RES_LOW, RES_HIGH; }()
#else
    #define __R_GF_2_ADD_FUNCTION__(A, B, RES_HIGH, RES_LOW)[&]() {\
        RES_HIGH = 0;\
        RES_LOW = 0;\
        while (B > 0) {\
            if (B & 1)\
            {\
                RES_LOW ^= A;\
            }\
            unsigned long long MSB = (A >> 63) & 1;\
            A <<= 1;\
            RES_HIGH = (RES_HIGH << 1) ^ MSB;\
            B >>= 1;\
        }\
        return RES_LOW, RES_HIGH; }()
#endif

#define __R_GF_2_REDUCE_FUNCTION__(HIGH, LOW, POLY)[&]() {\
    for (int i = 63; i >= 0; --i) {\
        if ((HIGH >> i) & 1) {\
            HIGH ^= (POLY >> (64 - i));\
            LOW ^= (POLY << i);\
        }\
    }\
    return LOW; }()

#endif // GF_2_HPP