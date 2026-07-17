#pragma once

#include "core/types.h"

enum I8086_OpCodes_Main : BYTE {

//  ASCII Adjust...
    AAA = 0x37,             // ...for Addition
    AAS = 0x3F,             // ...for Subtraction
    AAM = 0xD4,             // ...for Multiplication
    AAD = 0xD5,             // ...for Division

//  Add with Carry
    ADC_Eb_Gb = 0x10,
    ADC_Ev_Gv = 0x11,
    ADC_Gb_Eb = 0x12,
    ADC_Gv_Ev = 0x13,
    ADC_AL_Ib = 0x14,
    ADC_AX_Iv = 0x15,

//  Add
    ADD_Eb_Gb = 0x00,
    ADD_Ev_Gv = 0x01,
    ADD_Gb_Eb = 0x02,
    ADD_Gv_Ev = 0x03,
    ADD_AL_Ib = 0x04,
    ADD_AX_Iv = 0x05,

//  Logical AND
    AND_Eb_Gb = 0x20,
    AND_Ev_Gv = 0x21,
    AND_Gb_Eb = 0x22,
    AND_Gv_Ev = 0x23,
    AND_AL_Ib = 0x24,
    AND_AX_Iv = 0x25,

//  Call
    CALL_Ap = 0x9A,
    CALL_Jv = 0xE8,

//  Convert...
    CBW = 0x98,             // ...Byte to Word
    CWD = 0x99,             // ...Word to Doubleword

//  Compare Two Operands
    CMP_AL_Ib = 0x3C,
    CMP_AX_Iv = 0x3D,
    CMP_Eb_Gb = 0x38,
    CMP_Ev_Gv = 0x39,
    CMP_Gb_Eb = 0x3A,
    CMP_Gv_Ev = 0x3B,

//  Segments override
    ES = 0x26,
    CS = 0x2E,
    SS = 0x36,
    DS = 0x3E,

//  Decimal Adjust...
    DAA = 0x27,             // ...for Addition
    DAS = 0x2F,             // ...for Subtraction

//  Decrement
    DEC_AX = 0x48,
    DEC_BP = 0x4D,
    DEC_BX = 0x4B,
    DEC_CX = 0x49,
    DEC_DI = 0x4F,
    DEC_DX = 0x4A,
    DEC_SI = 0x4E,
    DEC_SP = 0x4C,

//  Group
    GRP1_Eb_Ib = 0x80,
    GRP1_Ev_Iv = 0x81,
    // GRP1_Eb_Ib = 0x82,   //duplicated 0x80 ???
    GRP1_Ev_Ib = 0x83,
    GRP2_Eb_1 = 0xD0,
    GRP2_Ev_1 = 0xD1,
    GRP2_Eb_CL = 0xD2,
    GRP2_Ev_CL = 0xD3,
    GRP3a_Eb = 0xF6,
    GRP3b_Ev = 0xF7,
    GRP4_Eb = 0xFE,
    GRP5_Ev = 0xFF,

//  Halt CPU
    HLT = 0xF4,

//  Increment
    INC_AX = 0x40,
    INC_BP = 0x45,
    INC_BX = 0x43,
    INC_CX = 0x41,
    INC_DI = 0x47,
    INC_DX = 0x42,
    INC_SI = 0x46,
    INC_SP = 0x44,

//  Interrupt
    INTO = 0xCE,
    INT_3 = 0xCC,
    INT_Ib = 0xCD,

//  Return from Interrupt
    IRET = 0xCF,

//  Input data from port
    IN_AL_DX = 0xEC,
    IN_AL_Ib = 0xE4,
    IN_AX_DX = 0xED,
    IN_AX_Ib = 0xE5,

//  Jump
    JA_Jb = 0x77,
    JBE_Jb = 0x76,
    JB_Jb = 0x72,
    JCXZ_Jb = 0xE3,
    JGE_Jb = 0x7D,
    JG_Jb = 0x7F,
    JLE_Jb = 0x7E,
    JL_Jb = 0x7C,
    JMP_Ap = 0xEA,
    JMP_Jb = 0xEB,
    JMP_Jv = 0xE9,
    JNB_Jb = 0x73,
    JNO_Jb = 0x71,
    JNS_Jb = 0x79,
    JNZ_Jb = 0x75,
    JO_Jb = 0x70,
    JPE_Jb = 0x7A,
    JPO_Jb = 0x7B,
    JS_Jb = 0x78,
    JZ_Jb = 0x74,

//  Load Pointer to...
    LDS_Gv_Mp = 0xC5,       // ...DS
    LES_Gv_Mp = 0xC4,       // ...ES

//  Load Effective Address
    LEA_Gv_M = 0x8D,

//  Assert Bus Lock
    LOCK = 0xF0,

//  Loop control
    LOOPNZ_Jb = 0xE0,
    LOOPZ_Jb = 0xE1,
    LOOP_Jb = 0xE2,

//  Move data
    MOV_AH_Ib = 0xB4,
    MOV_AL_Ib = 0xB0,
    MOV_AL_Ob = 0xA0,
    MOV_AX_Iv = 0xB8,
    MOV_AX_Ov = 0xA1,
    MOV_BH_Ib = 0xB7,
    MOV_BL_Ib = 0xB3,
    MOV_BP_Iv = 0xBD,
    MOV_BX_Iv = 0xBB,
    MOV_CH_Ib = 0xB5,
    MOV_CL_Ib = 0xB1,
    MOV_CX_Iv = 0xB9,
    MOV_DH_Ib = 0xB6,
    MOV_DI_Iv = 0xBF,
    MOV_DL_Ib = 0xB2,
    MOV_DX_Iv = 0xBA,
    MOV_Eb_Gb = 0x88,
    MOV_Eb_Ib = 0xC6,
    MOV_Ev_Gv = 0x89,
    MOV_Ev_Iv = 0xC7,
    MOV_Ew_Sw = 0x8C,
    MOV_Gb_Eb = 0x8A,
    MOV_Gv_Ev = 0x8B,
    MOV_Ob_AL = 0xA2,
    MOV_Ov_AX = 0xA3,
    MOV_SI_Iv = 0xBE,
    MOV_SP_Iv = 0xBC,
    MOV_Sw_Ew = 0x8E,

//  No Operation
    NOP = 0x90,

//  Logical OR
    OR_AL_Ib = 0x0C,
    OR_AX_Iv = 0x0D,
    OR_Eb_Gb = 0x08,
    OR_Ev_Gv = 0x09,
    OR_Gb_Eb = 0x0A,
    OR_Gv_Ev = 0x0B,

//  Output data to port
    OUT_Ib_AL = 0xE6,
    OUT_Ib_AX = 0xE7,
    OUT_DX_AL = 0xEE,
    OUT_DX_AX = 0xEF,

//  Push flags
    PUSHF = 0x9C,

//  Push
    PUSH_AX = 0x50,
    PUSH_CX = 0x51,
    PUSH_DX = 0x52,
    PUSH_BX = 0x53,
    PUSH_SP = 0x54,
    PUSH_BP = 0x55,
    PUSH_SI = 0x56,
    PUSH_DI = 0x57,
    PUSH_ES = 0x06,
    PUSH_CS = 0x0E,
    PUSH_SS = 0x16,
    PUSH_DS = 0x1E,

//  Pop flags
    POPF = 0x9D,

//  Pop
    POP_AX = 0x58,
    POP_CX = 0x59,
    POP_DX = 0x5A,
    POP_BX = 0x5B,
    POP_SP = 0x5C,
    POP_BP = 0x5D,
    POP_SI = 0x5E,
    POP_DI = 0x5F,
    POP_ES = 0x07,
    POP_SS = 0x17,
    POP_DS = 0x1F,
    POP_Ev = 0x8F,

//  Repeat
    REPNZ = 0xF2,
    REPZ = 0xF3,

//  Return
    RET_Iw = 0xC2,
    RET = 0xC3,
    RETF_Iw = 0xCA,
    RETF = 0xCB,

//  Store AH in Flags
    SAHF = 0x9E,

//  Load AH From Flags
    LAHF = 0x9F,

//  Subtract with Borrow
    SBB_Eb_Gb = 0x18,
    SBB_Ev_Gv = 0x19,
    SBB_Gb_Eb = 0x1A,
    SBB_Gv_Ev = 0x1B,
    SBB_AL_Ib = 0x1C,
    SBB_AX_Iv = 0x1D,

//  Set flags...
    STC = 0xF9,             // ...carry flag
    STI = 0xFB,             // ...interrupt enable flag
    STD = 0xFD,             // ...direction flag

//  Clear flags...
    CLC = 0xF8,             // ... carry flag
    CLI = 0xFA,             // ... interrupt enable flag
    CLD = 0xFC,             // ... direction flag

//  Complement Carry Flag
    CMC = 0xF5,

//  Subtract
    SUB_Eb_Gb = 0x28,
    SUB_Ev_Gv = 0x29,
    SUB_Gb_Eb = 0x2A,
    SUB_Gv_Ev = 0x2B,
    SUB_AL_Ib = 0x2C,
    SUB_AX_Iv = 0x2D,

//  Logical Compare
    TEST_Gb_Eb = 0x84,
    TEST_Gv_Ev = 0x85,
    TEST_AL_Ib = 0xA8,
    TEST_AX_Iv = 0xA9,

//  Wait While TEST pin not Asserted
    WAIT = 0x9B,

//  Exchange
    XCHG_Gb_Eb = 0x86,
    XCHG_Gv_Ev = 0x87,
    XCHG_CX_AX = 0x91,
    XCHG_DX_AX = 0x92,
    XCHG_BX_AX = 0x93,
    XCHG_SP_AX = 0x94,
    XCHG_BP_AX = 0x95,
    XCHG_SI_AX = 0x96,
    XCHG_DI_AX = 0x97,

//  Table Look-up Translation
    XLAT = 0xD7,

//  Exclusive OR (XOR)
    XOR_AL_Ib = 0x34,
    XOR_AX_Iv = 0x35,
    XOR_Eb_Gb = 0x30,
    XOR_Ev_Gv = 0x31,
    XOR_Gb_Eb = 0x32,
    XOR_Gv_Ev = 0x33,

///////////////////////////////////
//  Primitive String Operations  //
///////////////////////////////////

//  Move the string...
    MOVSB = 0xA4,           // ...if operand is Byte String
    MOVSW = 0xA5,           // ...if operand is Word String

//  Compare string...
    CMPSB = 0xA6,           // ...if operand is Byte String
    CMPSW = 0xA7,           // ...if operand is Word String

//  Scan string...
    SCASB = 0xAE,           // ...if operand is Byte String
    SCASW = 0xAF,           // ...if operand is Word String

//  Load cache string element...
    LODSB = 0xAC,           // ...if operand is Byte String
    LODSW = 0xAD,           // ...if operand is Word String

//  Store string...
    STOSB = 0xAA,           // ...if operand is Byte String
    STOSW = 0xAB,           // ...if operand is Word String

};
