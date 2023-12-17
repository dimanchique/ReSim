#pragma once
#include "MOS6502_TestingSuite.h"

class MOS6502_LDFixture : public MOS6502_TestFixture {
public:
    void LD_IM_CanLoadValue(MOS6502_OpCodes opcode, BYTE &targetRegister);
    void LD_IM_CanAffectZeroFlag(MOS6502_OpCodes opcode);
    void LD_IM_CanAffectNegativeFlag(MOS6502_OpCodes opcode);
    void LD_ZP_CanLoadValue(MOS6502_OpCodes opcode, BYTE &targetRegister);
    void LD_ZP_CanLoadValue(MOS6502_OpCodes opcode, BYTE &targetRegister, BYTE affectingRegister);
    void LD_ABS_CanLoadValue(MOS6502_OpCodes opcode, BYTE &targetRegister);
    void LD_ABS_CanLoadValue(MOS6502_OpCodes opcode, BYTE &targetRegister, BYTE affectingRegister);
};
