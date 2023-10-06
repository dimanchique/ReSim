#pragma once
#include "CPU6502_TestingSuite.h"

class CPU6502_LDFixture : public CPU6502_TestFixture {
public:
    void LD_IM_CanLoadValue(CPU6502_OpCodes opcode, BYTE &targetRegister);
    void LD_IM_CanAffectZeroFlag(CPU6502_OpCodes opcode);
    void LD_IM_CanAffectNegativeFlag(CPU6502_OpCodes opcode);
    void LD_ZP_CanLoadValue(CPU6502_OpCodes opcode, BYTE &targetRegister);
    void LD_ZP_CanLoadValue(CPU6502_OpCodes opcode, BYTE &targetRegister, BYTE affectingRegister);
    void LD_ABS_CanLoadValue(CPU6502_OpCodes opcode, BYTE &targetRegister);
    void LD_ABS_CanLoadValue(CPU6502_OpCodes opcode, BYTE &targetRegister, BYTE affectingRegister);
};
