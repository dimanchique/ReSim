#pragma once

#define DECLARE_PAIRED_REG_UNIQUE_NAME(SUB_SIZE, RESULT_SIZE, NAME1, NAME2, NAME_PAIRED)    \
union{                                                                          \
    struct{                                                                     \
        SUB_SIZE NAME1;                                                         \
        SUB_SIZE NAME2;                                                         \
    };                                                                          \
    RESULT_SIZE NAME_PAIRED;                                                    \
}

#define DECLARE_PAIRED_REG(SUB_SIZE, RESULT_SIZE, NAME1, NAME2) DECLARE_PAIRED_REG_UNIQUE_NAME(SUB_SIZE, RESULT_SIZE, NAME1, NAME2, NAME1##NAME2)
