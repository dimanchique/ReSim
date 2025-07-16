#pragma once

#include "core/types.h"

enum I8086_OpCods_GRP1 : BYTE {
    GRP1_ADD = 0x00,
    GRP1_OR = 0x01,
    GRP1_ADC = 0x02,
    GRP1_SBB = 0x03,
    GRP1_AND = 0x04,
    GRP1_SUB = 0x05,
    GRP1_XOR = 0x06,
    GRP1_CMP = 0x07
};

enum I8086_OpCods_GRP2 : BYTE {
    GRP2_ROL = 0x00,
    GRP2_ROR = 0x01,
    GRP2_RCL = 0x02,
    GRP2_RCR = 0x03,
    GRP2_SHL = 0x04,
    GRP2_SHR = 0x05,
    GRP2_SAR = 0x07
};

enum I8086_OpCods_GRP3a : BYTE {
    GRP3a_TEST_Eb_Ib = 0x00,
    GRP3a_NOT        = 0x02,
    GRP3a_NEG        = 0x03,
    GRP3a_MUL        = 0x04,
    GRP3a_IMUL       = 0x05,
    GRP3a_DIV        = 0x06,
    GRP3a_IDIV       = 0x07
};

enum I8086_OpCods_GRP3b : BYTE {
    GRP3b_TEST_Ev_Iv = 0x00,
    GRP3b_NOT        = 0x02,
    GRP3b_NEG        = 0x03,
    GRP3b_MUL        = 0x04,
    GRP3b_IMUL       = 0x05,
    GRP3b_DIV        = 0x06,
    GRP3b_IDIV       = 0x07
};

enum I8086_OpCods_GRP4 : BYTE {
    GRP4_INC = 0x00,
    GRP4_DEC = 0x01
};

enum I8086_OpCods_GRP5 : BYTE {
    GRP5_INC     = 0x00,
    GRP5_DEC     = 0x01,
    GRP5_CALL    = 0x02,
    GRP5_CALL_Mp = 0x03,
    GRP5_JMP     = 0x04,
    GRP5_JMP_Mp  = 0x05,
    GRP5_PUSH    = 0x06
};
