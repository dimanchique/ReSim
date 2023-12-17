#pragma once
#include "MOS6502_TestingSuite.h"

class MOS6502_INCFixture : public MOS6502_TestFixture {
public:
    void INC_ZP_CanAffectValue(MOS6502_OpCodes opcode, BYTE memoryValue, BYTE offsetValueRegister = 0);
    void INC_ABS_CanAffectValue(MOS6502_OpCodes opcode, BYTE memoryValue, BYTE offsetValueRegister = 0);
    void INC_IMPL_CanAffectValue(MOS6502_OpCodes opcode, BYTE &targetRegister);
};
