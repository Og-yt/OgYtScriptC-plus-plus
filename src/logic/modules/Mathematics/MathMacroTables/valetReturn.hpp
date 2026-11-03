#ifndef VALETRETURN_HPP
#define VALETRETURN_HPP

struct MATH_RESULT
{
    double VALUES[4];
    double DETERMINANT;
    bool SUCCESS;
};

#define __R_VALET_RETURN_FUNCTION__(SCALE_FACTOR)[&]() {\
    MATH_RESULT RES = {};\
    if (SCALE_FACTOR <= 0.0) {\
        RES.SUCCESS = false;\
        return RES;\
    }\
    RES.VALUES[0] = 1.0 * SCALE_FACTOR;\
    RES.VALUES[1] = 2.0 * SCALE_FACTOR;\
    RES.VALUES[2] = 3.0 * SCALE_FACTOR;\
    RES.VALUES[3] = 4.0 * SCALE_FACTOR;\
    RES.DETERMINANT = (RES.VALUES[0] * RES.VALUES[3]) - (RES.VALUES[1] * RES.VALUES[2]);\
    RES.SUCCESS = true;\
    return RES; }()

#endif // VALETRETURN_HPP