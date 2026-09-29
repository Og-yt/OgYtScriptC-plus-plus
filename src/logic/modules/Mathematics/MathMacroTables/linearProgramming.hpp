#ifndef LINEARPROGRAMMING_HPP
#define LINEARPROGRAMMING_HPP

#include <cmath>
#include "../../../ErrorLogic.hpp"

#define __LINEAR_PROGRAMMING_LINE
#define __LINEAR_PROGRAMMING_BUFFER
#define __LINEAR_PROGRAMMING_RESULT
#define __LINEAR_PROGRAMMING_MAX_VARS 10
#define __LINEAR_PROGRAMMING_MAX_CONSTRAINTS 10
#define __LINEAR_PROGRAMMING_MAX_ROWS __LINEAR_PROGRAMMING_MAX + 1
#define __LINEAR_PROGRAMMING_MAX_COLS __LINEAR_PROGRAMMING_MAX_VARS + __LINEAR_PROGRAMMING_MAX_CONSTRAINTS + 1

#define __R_LINEAR_PROGRAMMING_SOLVE_FUNCTION__(A, B, C, NUM_VARS, NUM_CONSTRAINTS, X_OPTIMAL, Z_OPTIMAL)[&]() {\
    if (NUM_VARS > __LINEAR_PROGRAMMING_MAX_VARS || NUM_CONSTRAINTS > __LINEAR_PROGRAMMING_MAX_CONSTRAINTS)\
    {\
        __LINEAR_PROGRAMMING_RESULT += ErrorLogic::build_msg(__LINEAR_PROGRAMMING_LINE, "Error: Problem dimensions exceed compile-time maximum limitations.\n");\
        ErrorLogic::highlight_line(__LINEAR_PROGRAMMING_BUFFER, __LINEAR_PROGRAMMING_LINE);\
        return false;\
    }\
    double TABLE_AU[__LINEAR_PROGRAMMING_MAX_ROWS][__LINEAR_PROGRAMMING_MAX_COLS] = {{0.0}};\
    int TOTAL_ROWS = NUM_CONSTRAINTS + 1;\
    int TOTAL_COLS = NUM_VARS + NUM_CONSTRAINTS + 1;\
    for (int i = 0; i < NUM_CONSTRAINTS; ++i)\
    {\
        for (int j = 0; j < NUM_VARS; ++j)\
        {\
            TABLE_AU[i][j] = A[i][j];\
        }\
        TABLE_AU[i][NUM_VARS + i] = 1.0;\
        TABLE_AU[i][TOTAL_COLS - 1] = B[i];\
    }\
    for (int j = 0; j < NUM_VARS; ++j)\
    {\
        TABLE_AU[TOTAL_ROWS - 1][j] = -C[j];\
    }\
    while (true)\
    {\
        int PIVOT_COL = -1;\
        double MIN_VAL = 0.0;\
        for (int j = 0; j < TOTAL_COLS - 1; ++j)\
        {\
            if (TABLE_AU[TOTAL_ROWS - 1][j] < MIN_VAL)\
            {\
                MIN_VAL = TABLE_AU[TOTAL_ROWS - 1][j];\
                PIVOT_COL = j;\
            }\
        }\
        if (PIVOT_COL == -1)\
        {\
            break;\
        }\
        int PIVOT_ROW = -1;\
        double MIN_RATIO = -1.0;\
        for (int i = 0; i < TOTAL_ROWS - 1; ++i)\
        {\
            double VAL = TABLE_AU[i][PIVOT_COL];\
            if (VAL > 1e-9)\
            {\
                double RATIO = TABLE_AU[i][TOTAL_COLS - 1] / VAL;\
                if (PIVOT_ROW == -1 || RATIO < MIN_RATIO)\
                {\
                    MIN_RATIO = RATIO;\
                    PIVOT_ROW = i;\
                }\
            }\
        }\
        if (PIVOT_ROW == -1) return false;\
        double PIVOT_VALUE = TABLE_AU[PIVOT_ROW][PIVOT_COL];\
        for (int j = 0; j < TOTAL_COLS; ++j)\
        {\
            TABLE_AU[PIVOT_ROW][j] /= PIVOT_VALUE;\
        }\
        for (int r = 0; r < TOTAL_ROWS; ++r)\
        {\
            if (r != PIVOT_ROW)\
            {\
                double FACTOR = TABLE_AU[r][PIVOT_COL];\
                for (int j = 0; j < TOTAL_COLS; ++j)\
                {\
                    TABLE_AU[r][j] -= FACTOR * TABLE_AU[PIVOT_ROW][j];\
                }\
            }\
        }\
    }\
    Z_OPTIMAL = TABLE_AU[TOTAL_ROWS - 1][TOTAL_COLS - 1];\
    for (int j = 0; j < NUM_VARS; ++j)\
    {\
        int BASIC_ROW = -1;\
        bool IS_BASIC = true;\
        for (int r = 0; r < TOTAL_ROWS - 1; ++r)\
        {\
            if (std::abs(TABLE_AU[r][j] - 1.0) < 1e-9)\
            {\
                if (BASIC_ROW == -1) BASIC_ROW = r;\
                else IS_BASIC = false;\
            }\
            else if (std::abs(TABLE_AU[r][j]) > 1e-9)\
            {\
                IS_BASIC = false;\
            }\
        }\
        X_OPTIMAL[j] = (IS_BASIC && BASIC_ROW != -1) ? TABLE_AU[BASIC_ROW][TOTAL_COLS - 1] : 0.0;\
    }\
    return true; }()

#endif // LINEARPROGEAMMING_HPP