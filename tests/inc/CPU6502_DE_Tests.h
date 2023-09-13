#pragma once
#include "CPU6502_TestingSuite.h"

class CPU6502_DEFixture : public CPU6502_TestFixture{
public:
    void DE_ZP_CanAffectValue(CPU6502_OpCodes OpCode, BYTE MemoryValue, BYTE OffsetValueRegister = 0);
    void DE_ABS_CanAffectValue(CPU6502_OpCodes OpCode, BYTE MemoryValue, BYTE OffsetValueRegister = 0);
    void DE_IMPL_CanAffectValue(CPU6502_OpCodes OpCode, BYTE& TargetRegister);
};
