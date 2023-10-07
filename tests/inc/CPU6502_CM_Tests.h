#pragma once
#include "CPU6502_TestingSuite.h"

class CPU6502_CMFixture : public CPU6502_TestFixture {
public:
    void CM_IM(CPU6502_OpCodes opcode, BYTE &targetRegister, BYTE initialValue, BYTE memoryValue);
    void CM_ZP(CPU6502_OpCodes opcode, BYTE &targetRegister, BYTE initialValue, BYTE memoryValue);
    void CM_ZP(CPU6502_OpCodes opcode, BYTE &targetRegister, BYTE initialValue, BYTE memoryValue, BYTE affectingRegister);
    void CM_ABS(CPU6502_OpCodes opcode, BYTE &targetRegister, BYTE initialValue, BYTE memoryValue);
    void CM_ABS(CPU6502_OpCodes opcode, BYTE &targetRegister, BYTE initialValue, BYTE memoryValue, BYTE affectingRegister);
};
