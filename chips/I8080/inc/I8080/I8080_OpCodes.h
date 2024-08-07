#pragma once

#include "core/types.h"

enum I8080_OpCodes : BYTE {

//  Add...
    ADD_A = 0x87,       //  ...Register or Memory To Accumulator
    ADD_B = 0x80,       //
    ADD_C = 0x81,       //
    ADD_D = 0x82,       //
    ADD_E = 0x83,       //
    ADD_H = 0x84,       //
    ADD_L = 0x85,       //
    ADD_M = 0x86,       //
    ADI = 0xC6,         //  ...Immediate Data to Accumulator
    ADC_A = 0x8F,       //  ...Register or Memory to Accumulator with Carry
    ADC_B = 0x88,       //
    ADC_C = 0x89,       //
    ADC_D = 0x8A,       //
    ADC_E = 0x8B,       //
    ADC_H = 0x8C,       //
    ADC_L = 0x8D,       //
    ADC_M = 0x8E,       //
    ACI = 0xCE,         //  ...Immediate Data to Accumulator with Carry
    DAD_B = 0x09,       //  ...16-bit number stored in B and C
    DAD_D = 0x19,       //  ...16-bit number stored in D and E
    DAD_H = 0x29,       //  ...16-bit number stored in H and L
    DAD_SP = 0x39,      //  ...16-bit number stored in SP

//  AND...
    ANA_A = 0xA7,       //  ...Register or Memory with Accumulator
    ANA_B = 0xA0,       //
    ANA_C = 0xA1,       //
    ANA_D = 0xA2,       //
    ANA_E = 0xA3,       //
    ANA_H = 0xA4,       //
    ANA_L = 0xA5,       //
    ANA_M = 0xA6,       //
    ANI = 0xE6,         //  ...Immediate Data with Accumulator

//  CALL - Call
    CALL = 0xCD,

//  Call if...
    CZ = 0xCC,      //  ...Zero bit is set
    CNZ = 0xC4,     //  ...Zero bit is reset
    CM = 0xFC,      //  ...Sign bit is set
    CP = 0xF4,      //  ...Sign bit is reset
    CC = 0xDC,      //  ...Carry bit is set
    CNC = 0xD4,     //  ...Carry bit is reset
    CPE = 0xEC,     //  ...Parity bit is set (Even)
    CPO = 0xE4,     //  ...Parity bit is reset (Odd)

//  Complement...
    CMA = 0x2F,     //  ...Accumulator
    CMC = 0x3F,     //  ...Carry

//  Compare...
    CMP_A = 0xBF,   //  ...Register or Memory with Accumulator
    CMP_B = 0xB8,   //
    CMP_C = 0xB9,   //
    CMP_D = 0xBa,   //
    CMP_E = 0xBB,   //
    CMP_H = 0xBC,   //
    CMP_L = 0xBD,   //
    CMP_M = 0xBE,   //
    CPI = 0xFE,     //  ...Immediate Data with Accumulator

//  DAA - Decimal Adjust Accumulator
    DAA = 0x27,

//  Decrement...
    DCR_A = 0x3D,   //  ...Register or Memory
    DCR_B = 0x05,   //
    DCR_C = 0x0D,   //
    DCR_D = 0x15,   //
    DCR_E = 0x1D,   //
    DCR_H = 0x25,   //
    DCR_L = 0x2D,   //
    DCR_M = 0x35,   //
    DCX_B = 0x0B,   //  ...Register Pair
    DCX_D = 0x1B,   //
    DCX_H = 0x2B,   //
    DCX_SP = 0x3B,  //

//  Interrupts
    DI = 0xF3,      //  ...Disable
    EI = 0xFB,      //  ...Enable

//  HLT - Halt CPU
    HLT = 0x76,

//  IN - Input data to accumulator from outcome device
    IN = 0xDB,

//  OUT - Output data from accumulator to outcome device
    OUT = 0xD3,

//  Increment...
    INR_A = 0x3C,   //  ...Register or Memory
    INR_B = 0x04,   //
    INR_C = 0x0C,   //
    INR_D = 0x14,   //
    INR_E = 0x1C,   //
    INR_H = 0x24,   //
    INR_L = 0x2C,   //
    INR_M = 0x34,   //
    INX_B = 0x03,   //  ...Register Pair
    INX_D = 0x13,   //
    INX_H = 0x23,   //
    INX_SP = 0x33,  //

//  JMP - Jump
    JMP = 0xC3,

//  Jump if...
    JZ = 0xCC,      //  ...Zero bit is set
    JNZ = 0xC4,     //  ...Zero bit is reset
    JM = 0xFC,      //  ...Sign bit is set
    JP = 0xF4,      //  ...Sign bit is reset
    JC = 0xDC,      //  ...Carry bit is set
    JNC = 0xD4,     //  ...Carry bit is reset
    JPE = 0xEC,     //  ...Parity bit is set (Even)
    JPO = 0xE4,     //  ...Parity bit is reset (Odd)

//  Load...
    LDA = 0x3A,     //  ...Data from Accumulator to Memory
    LDAX_B = 0x0A,  //  ...Accumulator data addressed by B and C Registers
    LDAX_D = 0x1A,  //  ...Accumulator data addressed by D and E Registers
    LHLD = 0x2A,    //  ...H and L Registers from Memory
    LXI_B = 0x01,   //  ...Immediate data into BC Register
    LXI_D = 0x11,   //  ...Immediate data into DE Register
    LXI_H = 0x21,   //  ...Immediate data into HL Register
    LXI_SP = 0x31,  //  ...Immediate data into SP Register

//  MOV - Transfer Data between Register or Memory
    MOV_A_A = 0x7F,
    MOV_A_B = 0x78,
    MOV_A_C = 0x79,
    MOV_A_D = 0x7A,
    MOV_A_E = 0x7B,
    MOV_A_H = 0x7C,
    MOV_A_L = 0x7D,
    MOV_A_M = 0x7E,
    MOV_B_A = 0x47,
    MOV_B_B = 0x40,
    MOV_B_C = 0x41,
    MOV_B_D = 0x42,
    MOV_B_E = 0x43,
    MOV_B_H = 0x44,
    MOV_B_L = 0x45,
    MOV_B_M = 0x46,
    MOV_C_A = 0x4F,
    MOV_C_B = 0x48,
    MOV_C_C = 0x49,
    MOV_C_D = 0x4A,
    MOV_C_E = 0x4B,
    MOV_C_H = 0x4C,
    MOV_C_L = 0x4D,
    MOV_C_M = 0x4E,
    MOV_D_A = 0x57,
    MOV_D_B = 0x50,
    MOV_D_C = 0x51,
    MOV_D_D = 0x52,
    MOV_D_E = 0x53,
    MOV_D_H = 0x54,
    MOV_D_L = 0x55,
    MOV_D_M = 0x56,
    MOV_E_A = 0x5F,
    MOV_E_B = 0x58,
    MOV_E_C = 0x59,
    MOV_E_D = 0x5A,
    MOV_E_E = 0x5B,
    MOV_E_H = 0x5C,
    MOV_E_L = 0x5D,
    MOV_E_M = 0x5E,
    MOV_H_A = 0x67,
    MOV_H_B = 0x60,
    MOV_H_C = 0x61,
    MOV_H_D = 0x62,
    MOV_H_E = 0x63,
    MOV_H_H = 0x64,
    MOV_H_L = 0x65,
    MOV_H_M = 0x66,
    MOV_L_A = 0x6F,
    MOV_L_B = 0x68,
    MOV_L_C = 0x69,
    MOV_L_D = 0x6A,
    MOV_L_E = 0x6B,
    MOV_L_H = 0x6C,
    MOV_L_L = 0x6D,
    MOV_L_M = 0x6E,
    MOV_M_A = 0x77,
    MOV_M_B = 0x70,
    MOV_M_C = 0x71,
    MOV_M_D = 0x72,
    MOV_M_E = 0x73,
    MOV_M_H = 0x74,
    MOV_M_L = 0x75,

//  MVI - Move Immediate Data in specified Register
    MVI_A = 0x3E,
    MVI_B = 0x06,
    MVI_C = 0x0E,
    MVI_D = 0x16,
    MVI_E = 0x1E,
    MVI_H = 0x26,
    MVI_L = 0x2E,
    MVI_M = 0x36,

//  NOP - No Operation
    NOP = 0x00,

//  ORA - Logical OR Register or Memory with Accumulator
    ORA_A = 0xB7,
    ORA_B = 0xB0,
    ORA_C = 0xB1,
    ORA_D = 0xB2,
    ORA_E = 0xB3,
    ORA_H = 0xB4,
    ORA_L = 0xB5,
    ORA_M = 0xB6,

//  ORI - Logical OR Immediate Data with Accumulator
    ORI = 0xF6,

//  PCHL - Insert into program counter data from H and L Registers
    PCHL = 0xE9,

//  POP - Pop Data off Stack
    POP_B = 0xC1,
    POP_D = 0xD1,
    POP_H = 0xE1,
    POP_PSW = 0xF1,

//  PUSH - Push Data on Stack
    PUSH_B = 0xC5,
    PUSH_D = 0xD5,
    PUSH_H = 0xE5,
    PUSH_PSW = 0xF5,

//  Rotate
    RAL = 0x17,     //  ...Accumulator Left through Carry
    RAR = 0x1F,     //  ...Accumulator Right through Carry
    RLC = 0x07,     //  ...Accumulator Left
    RRC = 0x0F,     //  ...Accumulator Right

//  RET - Return
    RET = 0xC9,

//  Return if...
    RZ = 0xCC,      //  ...Zero bit is set
    RNZ = 0xC4,     //  ...Zero bit is reset
    RM = 0xFC,      //  ...Sign bit is set
    RP = 0xF4,      //  ...Sign bit is reset
    RC = 0xDC,      //  ...Carry bit is set
    RNC = 0xD4,     //  ...Carry bit is reset
    RPE = 0xEC,     //  ...Parity bit is set (Even)
    RPO = 0xE4,     //  ...Parity bit is reset (Odd)

//  RST - Reset
    RST_0 = 0xC7,
    RST_1 = 0xCF,
    RST_2 = 0xD7,
    RST_3 = 0xDF,
    RST_4 = 0xE7,
    RST_5 = 0xEF,
    RST_6 = 0xF7,
    RST_7 = 0xFF,

//  SPHL - Load SP from H and L Registers
    SPHL = 0xF9,

//  Store
    SHLD = 0x22,    //  ...H and L Register in Memory
    STA = 0x32,     //  ...Accumulator Data from Memory
    STAX_B = 0x02,  //  ...Accumulator data in memory addressed by B and C
    STAX_D = 0x12,  //  ...Accumulator data in memory addressed by D and E

//  STC - Set Carry
    STC = 0x37,

//  Subtract...
    SUB_A = 0x97,   //  ...Register or Memory From Accumulator
    SUB_B = 0x90,   //
    SUB_C = 0x91,   //
    SUB_D = 0x92,   //
    SUB_E = 0x93,   //
    SUB_H = 0x94,   //
    SUB_L = 0x95,   //
    SUB_M = 0x96,   //
    SUI = 0xD6,     //  ...Immediate Data from Accumulator
    SBB_A = 0x9F,   //  ...Register or Memory From Accumulator with Borrow
    SBB_B = 0x98,   //
    SBB_C = 0x99,   //
    SBB_D = 0x9A,   //
    SBB_E = 0x9B,   //
    SBB_H = 0x9C,   //
    SBB_L = 0x9D,   //
    SBB_M = 0x9E,   //
    SBI = 0xDE,     //  ...Immediate Data from Accumulator with Borrow

//  Exchange...
    XCHG = 0xEB,    //  ...Data held in H and L Registers
    XTHL = 0xE3,    //  ...Stack

//  Logical Exclusive-Or...
    XRA_A = 0xAF,   //  ...Register or Memory with Accumulator
    XRA_B = 0xA8,   //
    XRA_C = 0xA9,   //
    XRA_D = 0xAA,   //
    XRA_E = 0xAB,   //
    XRA_H = 0xAc,   //
    XRA_L = 0xAD,   //
    XRA_M = 0xAE,   //
    XRI = 0xEE      //  ...Immediate Data with Accumulator
};
