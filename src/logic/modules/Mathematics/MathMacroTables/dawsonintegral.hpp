#ifndef DAWSONINTEGRAL_HPP
#define DAWSONINTEGRAL_HPP

#define __R_DAWSON_INTEGRAL__(X) [&]() {                                                        \
    double AX = X < 0 ? -X : X;                                                                 \
    if (AX <= 2.25)                                                                             \
    {                                                                                           \
        double P = AX * (1.314424e-2 + AX * (1.050309e-3 + AX * (1.135249e-4)));                \
        double Q = 1.0 + AX * (2.951016e-1 + AX * (2.890977e-2 + AX * (1.439832e-3)));          \
        return (X >= 0) ? (X / Q + P) : -(X / Q + P);                                           \
    }                                                                                           \
    else if (AX > 2.25 && AX <= 4.0)                                                            \
    {                                                                                           \
        double P = 1.488619e-1 + AX * (6.331252e-2 + AX * (8.966952e-3 + AX * (4.721743e-4)));  \
        double Q = 1.0 + AX * (4.279624e-1 + AX * (6.495034e-2 + AX * (4.577241e-3)));          \
        double VAL = P / Q;                                                                     \
        return (X >= 0) ? VAL : -VAL;                                                           \
    }                                                                                           \
    else                                                                                        \
    {                                                                                           \
        double P = 1.488619e-1 + AX * (6.331252e-2 + AX * (8.966952e-3 + AX * (4.721743e-4)));  \
        double Q = 1.0 + AX * (4.279624e-1 + AX * (6.495034e-2 + AX * (4.577241e-3)));          \
        double VAL = P / Q;                                                                     \
        return (X >= 0) ? VAL : -VAL;                                                           \
    } }()

#endif // DAWSONINTEGRAL_HPP