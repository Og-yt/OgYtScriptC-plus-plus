#ifndef SHA256_HPP
#define SHA256_HPP

#include <iomanip>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdint>

struct SHA256_CONTEXT
{
    uint32_t STATE[8];
    uint8_t BUFFER[64];
    uint32_t BUFFER_LEN;
    uint64_t BIN_LEN;
};

const uint32_t SHA_K[64] = {
    0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5, 0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
    0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3, 0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
    0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC, 0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
    0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7, 0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
    0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13, 0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
    0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3, 0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
    0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5, 0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
    0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208, 0x90BEFFFA, 0xA4506CEB, 0xBEFBF47F, 0xC67178F2};

#define __R_SHA_256_ROTR_FUNCTION__(X, N) [&]() { return (X >> N) | (X << (32 - N)); }()
#define __R_SHA_256_CHOOSE_FUNCTION__(X, Y, Z) [&]() { return (X & Y) ^ (~X & Z); }()
#define __R_SHA_256_MAJORITY_FUNCTION__(X, Y, Z) [&]() { return (X & Y) ^ (X & Z) ^ (Y & Z); }
#define __R_SHA_256_SIGMA0_FUNCTION__(X) [&]() { return __R_SHA_256_ROTR_FUNCTION__(X, 2) ^ __R_SHA_256_ROTR_FUNCTION__(X, 13) ^ __R_SHA_256_ROTR_FUNCTION__(X, 22); }()
#define __R_SHA_256_SIGMA1_FUNCTION__(X) [&]() { return __R_SHA_256_ROTR_FUNCTION__(X, 6) ^ __R_SHA_256_ROTR_FUNCTION__(X, 11) ^ __R_SHA_256_ROTR_FUNCTION__(X, 25); }()
#define __R_SHA_256_GAMMA0_FUNCTION__(X) [&]() { return __R_SHA_256_ROTR_FUNCTION__(X, 7) ^ __R_SHA_256_ROTR_FUNCTION__(X, 18) ^ (X >> 3); }()
#define __R_SHA_256_GAMMA1_FUNCTION__(X) [&]() { return __R_SHA_256_ROTR_FUNCTION__(X, 17) ^ __R_SHA_256_ROTR_FUNCTION__(X, 19) ^ (X >> 10); }()

#define __R_SHA_256_TRANSFORM_FUNCTION__(CTX, DATA) [&]() {\
    uint32_t A, B, C, D, E, F, G, H, T1, T2;\
    uint32_t W[64];\
    for (int I = 0; I < 16; ++I) {\
        W[I] = (DATA[I * 4] << 24) | (DATA[I * 4 + 1] << 16) | (DATA[I * 4 + 2] << 8) | (DATA[I * 4 + 3]);\
    }\
    for (int I = 16; I < 64; ++I)\
    {\
        W[I] = __R_SHA_256_GAMMA1_FUNCTION__(W[I - 2]) + W[I - 7] + __R_SHA_256_GAMMA0_FUNCTION__(W[I - 15]) + W[I - 16];\
    }\
    A = CTX->STATE[0]; B = CTX->STATE[1]; C = CTX->STATE[2]; D = CTX->STATE[3];\
    E = CTX->STATE[4]; F = CTX->STATE[5]; G = CTX->STATE[6]; H = CTX->STATE[7];\
    for (int I = 0; I < 64; ++I)\
    {\
        T1 = H + __R_SHA_256_SIGMA1_FUNCTION__(E) + __R_SHA_256_CHOOSE_FUNCTION__(E, F, G) + SHA_K[I] + W[I];\
        T2 = __R_SHA_256_SIGMA0_FUNCTION__(A) + __R_SHA_256_MAJORITY_FUNCTION__(A, B, C);\
        H = G; G = F; F = E; E = D + T1; D = C; C = B; B = A; A = T1 + T2;\
    }\
    CTX->STATE[0] += A; CTX->STATE[1] += B; CTX->STATE[2] += C; CTX->STATE[3] += D;\
    CTX->STATE[4] += E; CTX->STATE[5] += F; CTX->STATE[6] += G; CTX->STATE[7] += H;\
    return; }()

#define __R_SHA_256_INIT_FUNCTION__(CTX) [&]() {\
    CTX->STATE[0] = 0x6A09E667; CTX->STATE[1] = 0xBB67AE85; CTX->STATE[2] = 0x3C6EF372; CTX->STATE[3] = 0xA54FF53A;\
    CTX->STATE[4] = 0x510E527F; CTX->STATE[5] = 0x9B05688C; CTX->STATE[6] = 0x1F83D9AB; CTX->STATE[7] = 0x5BE0CD19;\
    CTX->BUFFER_LEN = 0; CTX->BIN_LEN = 0; return; }()

#define __R_SHA_256_UPDATE_FUNCTION__(CTX, DATA, LEN) [&]() {\
    for (size_t I = 0; I < LEN; ++I) {\
        CTX->BUFFER[CTX->BUFFER_LEN++] = DATA[I];\
        if (CTX->BUFFER_LEN == 64) {\
            __R_SHA_256_TRANSFORM_FUNCTION__(CTX, CTX->BUFFER);\
            CTX->BIN_LEN += 512;\
            CTX->BUFFER_LEN = 0;\
        }\
    }\
    return; }()

#define __R_SHA_256_FINALIZE_FUNCTION__(CTX, DIGEST) [&]() {\
    uint32_t I = CTX->BUFFER_LEN;\
    CTX->BIT_LEN += CTX->BUFFER_LEN * 8;\
    CTX->BUFFER[I++] = 0x80;\
    if (I > 56)\
    {\
        while (I < 64) CTX->BUFFER[I++] = 0x00;\
        __R_SHA_256_TRANSFORM_FUNCTION__(CTX, CTX->BUFFER);\
        I = 0;\
    }\
    while (I < 56) CTX->BUFFER[I++] = 0x00;\
    for (int N = 0; N < 8; ++N) {\
        CTX->BUFFER[63 - N] = (CTX->BIT_LEN >> (N * 8)) & 0xFF;\
        __R_SHA_256_TRANSFORM_FUNCTION__(CTX, CTX->BUFFER);\
    }\
    __R_SHA_256_TRANSFORM_FUNCTION__(CTX, CTX->BUFFER);\
    for (I = 0; I < 8; ++I) {\
        DIGEST[I * 4]     = (CTX->STATE[I] >> 24) & 0xFF;\
        DIGEST[I * 4 + 1] = (CTX->STATE[I] >> 16) & 0xFF;\
        DIGEST[I * 4 + 2] = (CTX->STATE[I] >> 8)  & 0xFF;\
        DIGEST[I * 4 + 3] = (CTX->STATE[I])\
    }\
    return; }()

#define __R_SHA_256_GET_HEX_FUNCTION__(INPUT) [&]() {\
    SHA256_CONTEXT CTX;\
    __R_SHA_256_INIT(&CTX);\
    __R_SHA_256_UPDATE(&CTX, reinterpret_cast<const uint8_t*>(INPUT.c_str()), INPUT.length());\
    uint8_t DIGEST[32];\
    __R_SHA_256_FINALIZE(&CTX, DIGEST);\
    std::stringstream SS;\
    for (int I = 0; I < 32; ++I)\
    {\
        SS << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(DIGEST[I]);\
    }\
    return SS.str(); }()

#endif // SHA256_HPP