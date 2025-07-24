#pragma once

#include "core/types.h"

enum MOS6502_OpCodes : BYTE {

//  ADC - Add with Carry
    ADC_IM = 0x69,
    ADC_ZP = 0x65,
    ADC_ZPX = 0x75,
    ADC_ABS = 0x6D,
    ADC_ABSX = 0x7D,
    ADC_ABSY = 0x79,
    ADC_INDX = 0x61,
    ADC_INDY = 0x71,

//  AND - Logical AND
    AND_IM = 0x29,
    AND_ZP = 0x25,
    AND_ZPX = 0x35,
    AND_ABS = 0x2D,
    AND_ABSX = 0x3D,
    AND_ABSY = 0x39,
    AND_INDX = 0x21,
    AND_INDY = 0x31,

//  ASL - Arithmetic Shift Left
    ASL_ACC = 0x0A,
    ASL_ZP = 0x06,
    ASL_ZPX = 0x16,
    ASL_ABS = 0x0E,
    ASL_ABSX = 0x1E,

//  LSR - Logical Shift Right
    LSR_ACC = 0x4A,
    LSR_ZP = 0x46,
    LSR_ZPX = 0x56,
    LSR_ABS = 0x4E,
    LSR_ABSX = 0x5E,

//  BIT - Bit Test
    BIT_ZP = 0x24,
    BIT_ABS = 0x2C,

//  Branch if...
    BCC_REL = 0x90,     //  ...Carry Reset
    BCS_REL = 0xB0,     //  ...Carry Set
    BEQ_REL = 0xF0,     //  ...Equal (Z=1)
    BMI_REL = 0x30,     //  ...Minus (S=1)
    BNE_REL = 0xD0,     //  ...Not Equal (Z=0)
    BPL_REL = 0x10,     //  ...Positive (S=0)
    BVC_REL = 0x50,     //  ...Overflow Reset
    BVS_REL = 0x70,     //  ...Overflow Set

//  BRK - Force Interrupt
    BRK_IMPL = 0x00,

//  Clear...
    CLC_IMPL = 0x18,    //  ...Carry Flag
    CLD_IMPL = 0xD8,    //  ...Decimal Mode
    CLI_IMPL = 0x58,    //  ...Interrupt Disable
    CLV_IMPL = 0xB8,    //  ...Overflow Flag

//  Compare...
    CMP_IM = 0xC9,      //  ...Memory
    CMP_ZP = 0xC5,      //
    CMP_ZPX = 0xD5,     //
    CMP_ABS = 0xCD,     //
    CMP_ABSX = 0xDD,    //
    CMP_ABSY = 0xD9,    //
    CMP_INDX = 0xC1,    //
    CMP_INDY = 0xD1,    //
    CPX_IM = 0xE0,      //  ...X Register
    CPX_ZP = 0xE4,      //
    CPX_ABS = 0xEC,     //
    CPY_IM = 0xC0,      //  ...Y Register
    CPY_ZP = 0xC4,      //
    CPY_ABS = 0xCC,     //

//  Decrement...
    DEC_ZP = 0xC6,      //  ...Memory
    DEC_ZPX = 0xD6,     //
    DEC_ABS = 0xCE,     //
    DEC_ABSX = 0xDE,    //
    DEX_IMPL = 0xCA,    //  ...X Register
    DEY_IMPL = 0x88,    //  ...Y Register

//  Increment...
    INC_ZP = 0xE6,      //  ...Memory
    INC_ZPX = 0xF6,     //
    INC_ABS = 0xEE,     //
    INC_ABSX = 0xFE,    //
    INX_IMPL = 0xE8,    //  ...X Register
    INY_IMPL = 0xC8,    //  ...Y Register

//  EOR - Exclusive OR
    EOR_IM = 0x49,
    EOR_ZP = 0x45,
    EOR_ZPX = 0x55,
    EOR_ABS = 0x4D,
    EOR_ABSX = 0x5D,
    EOR_ABSY = 0x59,
    EOR_INDX = 0x41,
    EOR_INDY = 0x51,

//  JMP - Jump
    JMP_ABS = 0x4C,
    JMP_IND = 0x6C,

//  JSR - Jump to Subroutine
    JSR_ABS = 0x20,

//  Load...
    LDA_IM = 0xA9,      //  ...Accumulator
    LDA_ZP = 0xA5,      //
    LDA_ZPX = 0xB5,     //
    LDA_ABS = 0xAD,     //
    LDA_ABSX = 0xBD,    //
    LDA_ABSY = 0xB9,    //
    LDA_INDX = 0xA1,    //
    LDA_INDY = 0xB1,    //
    LDX_IM = 0xA2,      //  ...X Register
    LDX_ZP = 0xA6,      //
    LDX_ZPY = 0xB6,     //
    LDX_ABS = 0xAE,     //
    LDX_ABSY = 0xBE,    //
    LDY_IM = 0xA0,      //  ...Y Register
    LDY_ZP = 0xA4,      //
    LDY_ZPX = 0xB4,     //
    LDY_ABS = 0xAC,     //
    LDY_ABSX = 0xBC,    //

//  NOP - No Operation
    NOP_IMPL = 0xEA,

//  ORA - Logical Inclusive OR
    ORA_IM = 0x09,
    ORA_ZP = 0x05,
    ORA_ZPX = 0x15,
    ORA_ABS = 0x0D,
    ORA_ABSX = 0x1D,
    ORA_ABSY = 0x19,
    ORA_INDX = 0x01,
    ORA_INDY = 0x11,

//  Push...
    PHA_IMPL = 0x48,    //  ...Accumulator
    PHP_IMPL = 0x08,    //  ...Processor Status

//  Pull...
    PLA_IMPL = 0x68,    //  ...Accumulator
    PLP_IMPL = 0x28,    //  ...Processor Status

//  Rotate...
    ROL_ACC = 0x2A,     //  ...Left
    ROL_ZP = 0x26,      //
    ROL_ZPX = 0x36,     //
    ROL_ABS = 0x2E,     //
    ROL_ABSX = 0x3E,    //
    ROR_ACC = 0x6A,     //  ...Right
    ROR_ZP = 0x66,      //
    ROR_ZPX = 0x76,     //
    ROR_ABS = 0x6E,     //
    ROR_ABSX = 0x7E,    //

//  Return
    RTI_IMPL = 0x40,    //  ...from Interrupt
    RTS_IMPL = 0x60,    //  ...from Subroutine

//  SBC - Subtract with Carry
    SBC_IM = 0xE9,
    SBC_ZP = 0xE5,
    SBC_ZPX = 0xF5,
    SBC_ABS = 0xED,
    SBC_ABSX = 0xFD,
    SBC_ABSY = 0xF9,
    SBC_INDX = 0xE1,
    SBC_INDY = 0xF1,

//  Set...
    SEC_IMPL = 0x38,    //  ...Carry Flag
    SED_IMPL = 0xF8,    //  ...Decimal Flag
    SEI_IMPL = 0x78,    //  ...Interrupt Disable

//  Store...
    STA_ZP = 0x85,      //  ...Accumulator
    STA_ZPX = 0x95,     //
    STA_ABS = 0x8D,     //
    STA_ABSX = 0x9D,    //
    STA_ABSY = 0x99,    //
    STA_INDX = 0x81,    //
    STA_INDY = 0x91,    //
    STX_ZP = 0x86,      //  X Register
    STX_ZPY = 0x96,     //
    STX_ABS = 0x8E,     //
    STY_ZP = 0x84,      //  Y Register
    STY_ZPX = 0x94,     //
    STY_ABS = 0x8C,     //

//  Transfer...
    TAX_IMPL = 0xAA,    //  ...Accumulator to X
    TAY_IMPL = 0xA8,    //  ...Accumulator to Y
    TSX_IMPL = 0xBA,    //  ...Stack Pointer to X
    TXA_IMPL = 0x8A,    //  ...X to Accumulator
    TXS_IMPL = 0x9A,    //  ...X to Stack Pointer
    TYA_IMPL = 0x98     //  ...Y to Accumulator
};
