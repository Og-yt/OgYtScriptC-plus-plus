#ifndef INTEGERPROGRAMMING_HPP
#define INTEGERPROGRAMMING_HPP

#include <cmath>

#define __INTEGER_PROGRAMMING_MAX_VARS 10
#define __INTEGER_PROGRAMMING_MAX_CONSTRAINTS 15
#define __INTEGER_PROGRAMMING_MAX_ROWS (__INTEGER_PROGRAMMING_MAX_CONSTRAINTS + 1)
#define __INTEGER_PROGRAMMING_MAX_COLS (__INTEGER_PROGRAMMING_MAX_VARS + __INTEGER_PROGRAMMING_MAX_CONSTRAINTS + 1)

#define __R_INTEGER_PROGRAMMING_SOLVE_LINEAR_PROGRAM_FUNCTION__(A, B, C, NUM_VARS, NUM_CONSTRAINTS, X_OPTIMAL, Z_OPTIMAL) [&]() {\
    double TABLE_AU[__INTEGER_PROGRAMMING_MAX_ROWS][__INTEGER_PROGRAMMING_MAX_COLS] = {\
        {\
            0.0\
        }\
    };\
    int TOTAL_ROWS = NUM_CONSTRAINTS + 1;\
    int TOTAL_COLS = NUM_VARS + NUM_CONSTRAINTS + 1;\
    for (int i = 0; i < NUM_CONSTRAINTS; ++i)\
    {\
        for (int j = 0; j < NUM_VARS; ++j) TABLE_AU[i][j] = A[i][j];\
        TABLE_AU[i][NUM_VARS + i] = 1.0;\
        TABLE_AU[i][TOTAL_COLS - 1] = B[i];\
    }\
    for (int j = 0; j < NUM_VARS; ++j) TABLE_AU[TOTAL_ROWS - 1][j] = -C[j];\
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
        if (PIVOT_COL == -1) break;\
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
        for (int j = 0; j < TOTAL_COLS; ++j) TABLE_AU[PIVOT_ROW][j] /= PIVOT_VALUE;\
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
    for (int col = 0; col < NUM_VARS; ++col)\
    {\
        int BASIC_ROW = -1;\
        bool IS_BASIC = true;\
        for (int row = 0; row < TOTAL_ROWS - 1; ++row)\
        {\
            if (std::abs(TABLE_AU[row][col] - 1.0) < 1e-9)\
            {\
                if (BASIC_ROW == -1) BASIC_ROW = row;\
                else IS_BASIC = false;\
            }\
            else if (std::abs(TABLE_AU[row][col]) > 1e-9)\
            {\
                IS_BASIC = false;\
            }\
        }\
        X_OPTIMAL[col] = (IS_BASIC && BASIC_ROW != -1) ? TABLE_AU[BASIC_ROW][TOTAL_COLS - 1] : 0.0;\
    }\
    return true; }()
#define __R_INTEGER_PROGRAMMING_BRANCH_AND_BOUND_FUNCTION__(A, B, C, NUM_VARS, NUM_CONSTRAINTS, BEST_X, BEST_Z, FOUND_INTEGER_SOLUTION) [&]() {\
    double CURRENT_X[__INTEGER_PROGRAMMING_MAX_VARS] = {0.0};\
    double CURRENT_Z = 0.0;\
    if (!__R_INTEGER_PROGRAMMING_SOLVE_LINEAR_PROGRAM_FUNCTION__(A, B, C, NUM_VARS, NUM_CONSTRAINTS, CURRENT_X, CURRENT_Z))\
    {\
        return;\
    }\
    if (FOUND_INTEGER_SOLUTION && CURRENT_Z <= BEST_Z)\
    {\
        return;\
    }\
    int BRANCH_VAR_IDX = -1;\
    for (int i = 0; i < NUM_VARS; ++i)\
    {\
        double FRACTIONAL_PART = CURRENT_X[i] - std::floor(CURRENT_X[i]);\
        if (FRACTIONAL_PART > 1e-5 && FRACTIONAL_PART < (1.0 - 1e-5))\
        {\
            BRANCH_VAR_IDX = i;\
            break;\
        }\
    }\
    if (BRANCH_VAR_IDX == -1)\
    {\
        FOUND_INTEGER_SOLUTION = true;\
        BEST_Z = CURRENT_Z;\
        for (int i = 0; i < NUM_VARS; ++i)\
        {\
            BEST_X[i] = std::round(CURRENT_X[i]);\
        }\
        return;\
    }\
    double VAL = CURRENT_X[BRANCH_VAR_IDX];\
    if (NUM_CONSTRAINTS < __INTEGER_PROGRAMMING_MAX_CONSTRAINTS)\
    {\
        for (int j = 0; j < NUM_VARS; ++j)\
        {\
            A[NUM_CONSTRAINTS][j] = (j == BRANCH_VAR_IDX) ? 1.0 : 0.0;\
        }\
        B[NUM_CONSTRAINTS] = std::floor(VAL);\
        __R_INTEGER_PROGRAMMING_BRANCH_AND_BOUND_FUNCTION__(A, B, C, NUM_VARS, NUM_CONSTRAINTS + 1, BEST_X, BEST_Z, FOUND_INTEGER_SOLUTION);\
    }\
    if (NUM_CONSTRAINTS < __INTEGER_PROGRAMMING_MAX_CONSTRAINTS)\
    {\
        for (int j = 0; j < NUM_VARS; ++j)\
        {\
            A[NUM_CONSTRAINTS][j] = (j == BRANCH_VAR_IDX) ? -1.0 : 0.0;\
        }\
        B[NUM_CONSTRAINTS] = -std::ceil(VAL);\
        __R_INTEGER_PROGRAMMING_BRANCH_AND_BOUND_FUNCTION__(A, B, C, NUM_VARS, NUM_CONSTRAINTS + 1, BEST_X, BEST_Z, FOUND_INTEGER_SOLUTION);\
    }\
    return; }()

#endif // INTEGERPROGRAMMING_HPP