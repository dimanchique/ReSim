#pragma once

#include "core/types.h"

enum Z80_OpCodes_Main : BYTE {

//  Add
    ADD_A_B = 0x80,
    ADD_A_C = 0x81,
    ADD_A_D = 0x82,
    ADD_A_E = 0x83,
    ADD_A_H = 0x84,
    ADD_A_L = 0x85,
    ADD_A = 0x86,
    ADD_A_A = 0x87,
    ADD_A_N = 0xC6,

    ADD_HL_BC = 0x09,
    ADD_HL_DE = 0x19,
    ADD_HL_HL = 0x29,
    ADD_HL_SP = 0x39,

//  Add with Carry
    ADC_A_B = 0x88,
    ADC_A_C = 0x89,
    ADC_A_D = 0x8A,
    ADC_A_E = 0x8B,
    ADC_A_H = 0x8C,
    ADC_A_L = 0x8D,
    ADC_A = 0x8E,
    ADC_A_A = 0x8F,
    ADC_A_N = 0xCE,

    // Subtract
    SUB_B = 0x90,
    SUB_C = 0x91,
    SUB_D = 0x92,
    SUB_E = 0x93,
    SUB_H = 0x94,
    SUB_L = 0x95,
    SUB_HL_ADDR = 0x96,
    SUB_A = 0x97,
    SUB_N = 0xD6,

//  Subtract with Borrow
    SBC_A_B = 0x98,
    SBC_A_C = 0x99,
    SBC_A_D = 0x9A,
    SBC_A_E = 0x9B,
    SBC_A_H = 0x9C,
    SBC_A_L = 0x9D,
    SBC_A_HL_ADDR = 0x9E,
    SBC_A_A = 0x9F,
    SBC_A_N = 0xDE,

//  Logical AND
    AND_B = 0xA0,
    AND_C = 0xA1,
    AND_D = 0xA2,
    AND_E = 0xA3,
    AND_H = 0xA4,
    AND_L = 0xA5,
    AND_HL = 0xA6,
    AND_A = 0xA7,
    AND_N = 0xE6,

//  Call...
    CALL_NZ_NN = 0xC4,      // ...if Z=0
    CALL_Z_NN = 0xCC,       // ...if Z=1
    CALL_NN = 0xCD,         // ...no condition
    CALL_NC_NN = 0xD4,      // ...if C=0
    CALL_C_NN = 0xDC,       // ...if C=1
    CALL_PO_NN = 0xE4,      // ...if P=0
    CALL_PE_NN = 0xEC,      // ...if P=1
    CALL_P_NN = 0xF4,       // ...if S=0
    CALL_M_NN = 0xFC,       // ...if S=1

//  Compare
    CP_B = 0xB8,
    CP_C = 0xB9,
    CP_D = 0xBA,
    CP_E = 0xBB,
    CP_H = 0xBC,
    CP_L = 0xBD,
    CP_HL = 0xBE,
    CP_A = 0xBF,
    CP_N = 0xFE,

//  Decrement
    DEC_B = 0x05,
    DEC_BC = 0x0B,
    DEC_C = 0x0D,
    DEC_D = 0x15,
    DEC_DE = 0x1B,
    DEC_E = 0x1D,
    DEC_H = 0x25,
    DEC_HL = 0x2B,
    DEC_L = 0x2D,
    DEC_HL_ADDR = 0x35,
    DEC_SP = 0x3B,
    DEC_A = 0x3D,

//  Decimal Adjust for Addition
    DAA = 0x27,

//  Interrupt...
    DI = 0xF3,              // ...disable
    EI = 0xFB,              // ...enable

//  Exchange
    EX_AF_A_F = 0x08,
    EX_DE_HL = 0xEB,
    EXX = 0xD9,
    EX_SP_ADDR_HL = 0xE3,

//  Halt CPU
    HALT = 0x76,

//  No Operation
    NOP = 0x00,

//  Increment
    INC_BC = 0x03,
    INC_B = 0x04,
    INC_C = 0x0C,
    INC_DE = 0x13,
    INC_D = 0x14,
    INC_E = 0x1C,
    INC_HL = 0x23,
    INC_H = 0x24,
    INC_L = 0x2C,
    INC_SP = 0x33,
    INC_HL_ADDR = 0x34,
    INC_A = 0x3C,

//  Jump...
    JP_NZ_NN = 0xC2,        // ...if Z=0
    JP_NN = 0xC3,           // ...no condition
    JP_Z_NN = 0xCA,         // ...if Z=1
    JP_NC_NN = 0xD2,        // ...if C=0
    JP_C_NN = 0xDA,         // ...if C=1
    JP_PO_NN = 0xE2,        // ...if P=0
    JP_HL_ADDR = 0xE9,      // ...to HL address
    JP_PE_NN = 0xEA,        // ...if P=1
    JP_P_NN = 0xF2,         // ...if S=0
    JP_M_NN = 0xFA,         // ...if S=1

//  I/O
    OUT_N_ADDR_A = 0xD3,
    IN_A_N_ADDR = 0xDB,

//  Jump using B-decrement zero check
    DJNZ_D = 0x10,

//  Jump Relative...
    JR_D = 0x18,            // ...no condition
    JR_NZ_D = 0x20,         // ...if Z=0
    JR_Z_D = 0x28,          // ...if Z=1
    JR_NC_D = 0x30,         // ...if C=0
    JR_C_D = 0x38,          // ...if C=1

//  Complement Accumulator
    CPL = 0x2F,

//  Set Carry Flag
    SCF = 0x37,

//  Complement Carry Flag
    CCF = 0x3F,

//  Load
    LD_BC_NN = 0x01,
    LD_BC_ADDR_NN = 0x02,
    LD_B_N = 0x06,
    LD_A_BC_ADDR = 0x0A,
    LD_C_N = 0x0E,
    LD_DE_NN = 0x11,
    LD_DE_ADDR_A = 0x12,
    LD_D_N = 0x16,
    LD_A_DE_ADDR = 0x1A,
    LD_E_N = 0x1E,
    LD_HL_NN = 0x21,
    LD_NN_ADDR_HL = 0x22,
    LD_H_N = 0x26,
    LD_HL_NN_ADDR = 0x2A,
    LD_L_N = 0x2E,
    LD_SP_NN = 0x31,
    LD_SP_HL = 0xF9,
    LD_NN_ADDR_A = 0x32,
    LD_HL_ADDR_N = 0x36,
    LD_A_NN_ADDR = 0x3A,
    LD_A_N = 0x3E,
    LD_B_B = 0x40,
    LD_B_C = 0x41,
    LD_B_D = 0x42,
    LD_B_E = 0x43,
    LD_B_H = 0x44,
    LD_B_L = 0x45,
    LD_B_HL_ADDR = 0x46,
    LD_B_A = 0x47,
    LD_C_B = 0x48,
    LD_C_C = 0x49,
    LD_C_D = 0x4A,
    LD_C_E = 0x4B,
    LD_C_H = 0x4C,
    LD_C_L = 0x4D,
    LD_C_HL_ADDR = 0x4E,
    LD_C_A = 0x4F,
    LD_D_B = 0x50,
    LD_D_C = 0x51,
    LD_D_D = 0x52,
    LD_D_E = 0x53,
    LD_D_H = 0x54,
    LD_D_L = 0x55,
    LD_D_HL_ADDR = 0x56,
    LD_D_A = 0x57,
    LD_E_B = 0x58,
    LD_E_C = 0x59,
    LD_E_D = 0x5A,
    LD_E_E = 0x5B,
    LD_E_H = 0x5C,
    LD_E_L = 0x5D,
    LD_E_HL_ADDR = 0x5E,
    LD_E_A = 0x5F,
    LD_H_B = 0x60,
    LD_H_C = 0x61,
    LD_H_D = 0x62,
    LD_H_E = 0x63,
    LD_H_H = 0x64,
    LD_H_L = 0x65,
    LD_H_HL_ADDR = 0x66,
    LD_H_A = 0x67,
    LD_L_B = 0x68,
    LD_L_C = 0x69,
    LD_L_D = 0x6A,
    LD_L_E = 0x6B,
    LD_L_H = 0x6C,
    LD_L_L = 0x6D,
    LD_L_HL_ADDR = 0x6E,
    LD_L_A = 0x6F,
    LD_HL_ADDR_B = 0x70,
    LD_HL_ADDR_C = 0x71,
    LD_HL_ADDR_D = 0x72,
    LD_HL_ADDR_E = 0x73,
    LD_HL_ADDR_H = 0x74,
    LD_HL_ADDR_L = 0x75,
    LD_HL_ADDR_A = 0x77,
    LD_A_B = 0x78,
    LD_A_C = 0x79,
    LD_A_D = 0x7A,
    LD_A_E = 0x7B,
    LD_A_H = 0x7C,
    LD_A_L = 0x7D,
    LD_A_HL_ADDR = 0x7E,
    LD_A_A = 0x7F,

//  Logical OR
    OR_B = 0xB0,
    OR_C = 0xB1,
    OR_D = 0xB2,
    OR_E = 0xB3,
    OR_H = 0xB4,
    OR_L = 0xB5,
    OR_HL = 0xB6,
    OR_A = 0xB7,
    OR_N = 0xF6,

//  Pop
    POP_B_C = 0xC1,
    POP_D_E = 0xD1,
    POP_H_L = 0xE1,
    POP_A_F = 0xF1,

//  Push
    PUSH_B_C = 0xC5,
    PUSH_D_E = 0xD5,
    PUSH_H_L = 0xE5,
    PUSH_A_F = 0xF5,

//  Return...
    RET_NZ = 0xC0,          // ...if Z=0
    RET_Z = 0xC8,           // ...if Z=1
    RET = 0xC9,             // ...no condition
    RET_NC = 0xD0,          // ...if C=0
    RET_C = 0xD8,           // ...if C=1
    RET_PO = 0xE0,          // ...if P=0
    RET_PE = 0xE8,          // ...if P=1
    RET_P = 0xF0,           // ...if S=0
    RET_M = 0xF8,           // ...if S=1

//  Rotate
    RLA = 0x17,
    RLCA = 0x07,
    RRA = 0x1F,
    RRCA = 0x0F,

//  Reset
    RST_00_H = 0xC7,
    RST_08_H = 0xCF,
    RST_10_H = 0xD7,
    RST_18_H = 0xDF,
    RST_20_H = 0xE7,
    RST_28_H = 0xEF,
    RST_30_H = 0xF7,
    RST_38_H = 0xFF,

//  Exclusive OR (XOR)
    XOR_B = 0xA8,
    XOR_C = 0xA9,
    XOR_D = 0xAA,
    XOR_E = 0xAB,
    XOR_H = 0xAC,
    XOR_L = 0xAD,
    XOR_HL = 0xAE,
    XOR_A = 0xAF,

//  Groups
    Bit_Group = 0xCB,
    IX_Group = 0xDD,
    Misc_Group = 0xED,
    IY_Group = 0xFD,
};
