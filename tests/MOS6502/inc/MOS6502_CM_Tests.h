#pragma once
#include "MOS6502_TestingSuite.h"

class MOS6502_CMFixture : public MOS6502_TestFixture {
public:
    void CM_IM_CanCompare(MOS6502_OpCodes opcode, BYTE &targetRegister, BYTE initialValue, BYTE memoryValue);
    void CM_ZP_CanCompare(MOS6502_OpCodes opcode, BYTE &targetRegister, BYTE initialValue, BYTE memoryValue);
    void CM_ZP_CanCompare(MOS6502_OpCodes opcode, BYTE &targetRegister, BYTE initialValue, BYTE memoryValue, BYTE affectingRegister);
    void CM_ABS_CanCompare(MOS6502_OpCodes opcode, BYTE &targetRegister, BYTE initialValue, BYTE memoryValue);
    void CM_ABS_CanCompare(MOS6502_OpCodes opcode, BYTE &targetRegister, BYTE initialValue, BYTE memoryValue, BYTE affectingRegister);
};
