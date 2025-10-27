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

#define RESIM_THROW throw std::runtime_error(std::string("Unexpected behaviour in ") + __FILE__ + ":" + std::to_string(__LINE__))
