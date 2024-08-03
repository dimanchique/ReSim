#pragma once

#define DECLARE_PAIRED_REG(SUB_SIZE, RESULT_SIZE, NAME1, NAME2)     \
union{                                                              \
    struct{                                                         \
        SUB_SIZE NAME1;                                             \
        SUB_SIZE NAME2;                                             \
    };                                                              \
    RESULT_SIZE NAME1##NAME2;                                       \
}
