#ifndef SIMPLEXMETHOD_HPP
#define SIMPLEXMETHOD_HPP

#include <cmath>
#include "../../../ErrorLogic.hpp"

#define __SIMPLEX_METHOD_LINE
#define __SIMPLEX_METHOD_BUFFER
#define __SIMPLEX_METHOD_RESULT
#define __SIMPLEX_METHOD_DEC_VARS 2
#define __SIMPLEX_METHOD_CONSTRAINTS 3
#define __SIMPLEX_METHOD_COLS __SIMPLEX_METHOD_DEC_VARS + __SIMPLEX_METHOD_CONSTRAINTS + 1
#define __SIMPLEX_METHOD_ROWS __SIMPLEX_METHOD_CONSTRAINTS + 1

#define __R_SIMPLEX_METHOD_SOLVE_FUNCTION__(TABLE_AU)[&]() {\
    while (true) {\
        int PIVOT_COL = -1;\
        double MIN_VAL = 0.0;\
        for (int j = 0; j < __SIMPLEX_METHOD_COLS - 1; ++j)\
        {\
            if (TABLE_AU[__SIMPLEX_METHOD_ROWS - 1][j] < MIN_VAL)\
            {\
                MIN_VAL = TABLE_AU[__SIMPLEX_METHOD_ROWS - 1][j];\
                PIVOT_COL = j;\
            }\
        }\
        if (PIVOT_COL == -1)\
        {\
            return true;\
        }\
        int PIVOT_ROW = -1;\
        double MIN_RATIO = -1.0;\
        for (int i = 0; i < __SIMPLEX_METHOD_ROWS - 1; ++i)\
        {\
            double val = TABLE_AU[i][PIVOT_COL];\
            if (val > 1e-9)\
            {\
                double ratio = TABLE_AU[i][__SIMPLEX_METHOD_COLS - 1] / val;\
                if (PIVOT_ROW == -1 || ratio < MIN_RATIO)\
                {\
                    MIN_RATIO = ratio;\
                    PIVOT_ROW = i;\
                }\
            }\
        }\
        if (PIVOT_ROW == -1)\
        {\
            __SIMPLEX_METHOD_RESULT += ErrorLogic::build_msg(__SIMPLEX_METHOD_LINE, "Error: The problem is unbounded.\n");\
            ErrorLogic::highlight_line(__SIMPLEX_METHOD_BUFFER, __SIMPLEX_METHOD_LINE);\
            return false;\
        }\
        double PIVOT_VALUE = TABLE_AU[PIVOT_ROW][PIVOT_COL];\
        for (int j = 0; j < __SIMPLEX_METHOD_COLS; ++j)\
        {\
            TABLE_AU[PIVOT_ROW][j] /= PIVOT_VALUE;\
        }\
        for (int i = 0; i < __SIMPLEX_METHOD_ROWS; ++i)\
        {\
            if (i != PIVOT_ROW)\
            {\
                double FACTOR = TABLE_AU[i][PIVOT_COL];\
                for (int j = 0; j < __SIMPLEX_METHOD_COLS; ++j)\
                {\
                    TABLE_AU[i][j] -= FACTOR * TABLE_AU[PIVOT_ROW][j];\
                }\
            }\
        }\
    }\
    return true; }()
#define __R_SIMPLEX_METHOD_FUNCTION__(TABLE)[&]() {\
    for (int COL = 0; COL < __SIMPLEX_METHOD_COLS - 1; ++COL)\
    {\
        int BASIC_ROW = -1;\
        bool IS_BASIC = true;\
        for (int ROW = 0; ROW < __SIMPLEX_METHOD_ROWS - 1; ++ROW)\
        {\
            if (std::abs(TABLE[__SIMPLEX_METHOD_ROWS - 1][COL] - 1.0) < 1e-9)\
            {\
                if (BASIC_ROW == -1)\
                {\
                    BASIC_ROW = ROW;\
                }\
                else\
                {\
                    IS_BASIC = false;\
                }\
            }\
            else if (std::abs(TABLE[__SIMPLEX_METHOD_ROWS - 1][COL]) > 1e-9)\
            {\
                IS_BASIC = false;\
            }\
        }\
        double VAL = (IS_BASIC && BASIC_ROW != -1) ? TABLE[__SIMPLEX_METHOD_ROWS - 1][__SIMPLEX_METHOD_COLS - 1] : 0.0;\
    }\
    return true; }()

#endif // SIMPLEXMETHOD_HPP