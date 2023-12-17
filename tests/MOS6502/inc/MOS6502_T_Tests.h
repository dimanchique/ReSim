#pragma once
#include "MOS6502_TestingSuite.h"

class MOS6502_TFixture : public MOS6502_TestFixture {
public:
    void T_IMPL_CanTransferValue(MOS6502_OpCodes opcode, BYTE &sourceRegister, BYTE &destinationRegister);
    void T_IMPL_CanAffectNegativeFlag(MOS6502_OpCodes opcode, BYTE &sourceRegister, BYTE &destinationRegister);
    void T_IMPL_CanAffectZeroFlag(MOS6502_OpCodes opcode, BYTE &sourceRegister, BYTE &destinationRegister);
};
