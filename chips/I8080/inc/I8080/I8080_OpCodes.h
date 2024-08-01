#pragma once

#include "core/types.h"

enum I8080_OpCodes : BYTE {

//  ADD - Add Register or Memory To Accumulator
    ADD_A = 0x87,
    ADD_B = 0x80,
    ADD_C = 0x81,
    ADD_D = 0x82,
    ADD_E = 0x83,
    ADD_H = 0x84,
    ADD_L = 0x85,
    ADD_M = 0x86,

//  ADI - ADD Immediate Data to Accumulator
    ADI = 0xC6,

//  ADC - ADD Register or Memory to Accumulator with Carry
    ADC_A = 0x8F,
    ADC_B = 0x88,
    ADC_C = 0x89,
    ADC_D = 0x8A,
    ADC_E = 0x8B,
    ADC_H = 0x8C,
    ADC_L = 0x8D,
    ADC_M = 0x8E,

//  ACI - ADD Immediate Data to Accumulator with Carry
    ACI = 0xCE,

//  ANA - Logical AND Register or Memory with Accumulator
    ANA_A = 0xA7,
    ANA_B = 0xA0,
    ANA_C = 0xA1,
    ANA_D = 0xA2,
    ANA_E = 0xA3,
    ANA_H = 0xA4,
    ANA_L = 0xA5,
    ANA_M = 0xA6,

//  ANI - Logical AND Immediate Data with Accumulator
    ANI = 0xE6,

//  CALL - Call
    CALL = 0xCD,

//  CZ - Call if Zero bit is one
    CZ = 0xCC,

//  CNZ - Call if Zero bit is zero
    CNZ = 0xC4,

//  CP - Call if Sign bit is zero
    CP = 0xF4,

//  CM - Call if Sign bit is one
    CM = 0xFC,

//  CC - Call if Carry bit is one
    CC = 0xDC,

//  CNC - Call if Carry bit is zero
    CNC = 0xD4,

//  CPE - Call if Parity Even
    CPE = 0xEC,

//  CPO - Call if Parity Odd
    CPO = 0xE4,

//  CMA - Complement Accumulator
    CMA = 0x2F,

//  CMC - Complement Carry
    CMC = 0x3F,

//  CMP - Compare Register or Memory with Accumulator
    CMP_A = 0xBF,
    CMP_B = 0xB8,
    CMP_C = 0xB9,
    CMP_D = 0xBa,
    CMP_E = 0xBB,
    CMP_H = 0xBC,
    CMP_L = 0xBD,
    CMP_M = 0xBE,

//  CPI - Compare Immediate Data with Accumulator
    CPI = 0xFE,

//  DAA - Decimal Adjust Accumulator
    DAA = 0x27,

//  DAD - Add 16-bit number stored in B and C, H and L, D and E Registers
    DAD_B = 0x09,
    DAD_D = 0x19,
    DAD_H = 0x29,
    DAD_SP = 0x39,

//  DCR - Decrement Register or Memory
    DCR_A = 0x3D,
    DCR_B = 0x05,
    DCR_C = 0x0D,
    DCR_D = 0x15,
    DCR_E = 0x1D,
    DCR_H = 0x25,
    DCR_L = 0x2D,
    DCR_M = 0x35,

//  DCX - Decrement Register Pair
    DCX_B = 0x0B,
    DCX_D = 0x1B,
    DCX_H = 0x2B,
    DCX_SP = 0x3B,

//  DI - Disable Interrupts
    DI = 0xF3,

//  EI - Enable Interrupts
    EI = 0xFB,

//  HLT - Halt CPU
    HLT = 0x76,

//  IN - Input data to accumulator from outcome device
    IN = 0xDB,

//  INR - Increment Register or Memory
    INR_A = 0x3C,
    INR_B = 0x04,
    INR_C = 0x0C,
    INR_D = 0x14,
    INR_E = 0x1C,
    INR_H = 0x24,
    INR_L = 0x2C,
    INR_M = 0x34,

//  INX - Increment Register Pair
    INX_B = 0x03,
    INX_D = 0x13,
    INX_H = 0x23,
    INX_SP = 0x33,

//  JMP - Jump
    JMP = 0xC3,

//  JZ - Jump if Zero bit is one 
    JZ = 0xCA,

//  JNZ - Jump if Zero bit is zero
    JNZ = 0xC2,

//  JP - Jump if sign bit is zero
    JP = 0xF2,

//  JM - Jump if sign bit is one
    JM = 0xFA,

//  JC - Jump if Carry bit is one
    JC = 0xDa,

//  JNC - Jump if Carry bit is zero
    JNC = 0xD2,

//  JPE - Jump if Parity Even
    JPE = 0xEA,

//  JPO - Jump if Parity Odd
    JPO = 0xE2,

//  LDA - Load Data from Accumulator to Memory
    LDA = 0x3A,

//  LDAX - Load Accumulator data addressed by B and C, or D and E Registers
    LDAX_B = 0x0A,
    LDAX_D = 0x1A,

//  LHLD - Load H and L Registers from Memory
    LHLD = 0x2A,

//  LXI - Load Immediate data into paired Register or SP
    LXI_B = 0x01,
    LXI_D = 0x11,
    LXI_H = 0x21,
    LXI_SP = 0x31,

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

//  NOP - Cmon. Its just nop
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

//  OUT - Output data from accumulator to outcome device
    OUT = 0xD3,

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

//  RAL - Rotate Accumulator through Carry
    RAL = 0x17,

//  RAR - Rotate Accumulator through Carry
    RAR = 0x1F,

//  RLC - Rotate Accumulator Left
    RLC = 0x07,

//  RRC - Rotate Accumulator Right
    RRC = 0x0F,

//  RET - Return
    RET = 0xC9,

//  RZ - Return if Zero bit is one
    RZ = 0xC8,

//  RNZ - Return if Zero bit is zero
    RNZ = 0xC0,

//  RP - Return if Sign bit is zero
    RP = 0xF0,

//  RM - Return if Sign bit is one
    RM = 0xF8,

//  RC - Return if Carry bit is one
    RC = 0xD8,

//  RNC - Return if Carry bit is zero
    RNC = 0xD0,

//  RPE - Return if Parity Even
    RPE = 0xE8,

//  RPO - Return if Parity Odd
    RPO = 0xE0,

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

//  SHLD - Store H and L Register in Memory
    SHLD = 0x22,

//  STA - Store Accumulator Data from Memory
    STA = 0x32,

//  STAX - Store Accumulator data in memory addressed by B and C, or D and E Registers
    STAX_B = 0x02,
    STAX_D = 0x12,

//  STC - Set Carry
    STC = 0x37,

//  SUB - Subtract Register or Memory From Accumulator
    SUB_A = 0x97,
    SUB_B = 0x90,
    SUB_C = 0x91,
    SUB_D = 0x92,
    SUB_E = 0x93,
    SUB_H = 0x94,
    SUB_L = 0x95,
    SUB_M = 0x96,

//  SUI - Subtract Immediate Data from Accumulator
    SUI = 0xD6,

//  SBB - Subtract Register or Memory From Accumulator with Borrow
    SBB_A = 0x9F,
    SBB_B = 0x98,
    SBB_C = 0x99,
    SBB_D = 0x9A,
    SBB_E = 0x9B,
    SBB_H = 0x9C,
    SBB_L = 0x9D,
    SBB_M = 0x9E,

//  SBI - Subtract Immediate Data from Accumulator with Borrow
    SBI = 0xDE,

//  XCHG - Exchange Data held in H and L Registers
    XCHG = 0xEB,

//  XTHL - Exchange Stack
    XTHL = 0xE3,

//  XRA - Logical Exclusive-Or Register or Memory with Accumulator
    XRA_A = 0xAF,
    XRA_B = 0xA8,
    XRA_C = 0xA9,
    XRA_D = 0xAA,
    XRA_E = 0xAB,
    XRA_H = 0xAc,
    XRA_L = 0xAD,
    XRA_M = 0xAE,

//  XRI - Logical Exclusive-Or Immediate Data with Accumulator
    XRI = 0xEE
};
