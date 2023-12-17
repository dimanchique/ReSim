#pragma once
#include "MOS6502_TestingSuite.h"

class MOS6502_DECFixture : public MOS6502_TestFixture {
public:
    void DEC_ZP_CanAffectValue(MOS6502_OpCodes opcode, BYTE memoryValue, BYTE offsetValueRegister = 0);
    void DEC_ABS_CanAffectValue(MOS6502_OpCodes opcode, BYTE memoryValue, BYTE offsetValueRegister = 0);
    void DEC_IMPL_CanAffectValue(MOS6502_OpCodes opcode, BYTE &targetRegister);
};
