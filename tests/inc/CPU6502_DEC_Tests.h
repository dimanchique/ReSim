#pragma once
#include "CPU6502_TestingSuite.h"

class CPU6502_DECFixture : public CPU6502_TestFixture{
public:
    void DEC_ZP_CanAffectValue(CPU6502_OpCodes OpCode, BYTE MemoryValue, BYTE OffsetValueRegister = 0);
    void DEC_ABS_CanAffectValue(CPU6502_OpCodes OpCode, BYTE MemoryValue, BYTE OffsetValueRegister = 0);
    void DEC_IMPL_CanAffectValue(CPU6502_OpCodes OpCode, BYTE& TargetRegister);
};
