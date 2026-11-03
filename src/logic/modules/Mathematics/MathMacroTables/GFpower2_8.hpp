#ifndef GFPOWER2_8_HPP
#define GFPOWER2_8_HPP

#define __R_GF_POWER_2_8_MULTIPLY_CONSTANT_TIME_FUNCTION__(A, B)[&]() {\
    uint8_t RESULT = 0;\
    for (int I = 0; I < 8; ++I)\
    {\
        uint8_t MASK = -static_cast<int8_t>(B & 1);\
        RESULT ^= (A & MASK);\
        uint8_t MSB_MASK = -static_cast<int8_t>((A >> 7) & 1);\
        A = (A << 1) ^ (0x1B & MSB_MASK);\
        B >>= 1;\
    }\
    return RESULT; }()

#endif // GFPOWER2_8_HPP