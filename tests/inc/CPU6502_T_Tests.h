#pragma once
#include "CPU6502_TestingSuite.h"

class CPU6502_TFixture : public CPU6502_TestFixture{
public:
    void T_IMPL_CanTransferValue(CPU6502_OpCodes OpCode, BYTE& SourceRegister, BYTE& DestinationRegister);
    void T_IMPL_CanAffectNegativeFlag(CPU6502_OpCodes OpCode, BYTE& SourceRegister, BYTE& DestinationRegister);
    void T_IMPL_CanAffectZeroFlag(CPU6502_OpCodes OpCode, BYTE& SourceRegister, BYTE& DestinationRegister);
};
