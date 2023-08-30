#pragma once
#include "CPU6502_TestingSuite.h"

class CPU6502_STFixture : public CPU6502_TestFixture{
public:
    void ST_ZP_CanStoreValue(CPU6502_OpCodes OpCode, BYTE& SourceRegister);
    void ST_ZP_CanStoreValue(CPU6502_OpCodes OpCode, BYTE& SourceRegister, BYTE AffectingRegister);
    void ST_ABS_CanStoreValue(CPU6502_OpCodes OpCode, BYTE& SourceRegister);
    void ST_ABS_CanStoreValue(CPU6502_OpCodes OpCode, BYTE& SourceRegister, BYTE AffectingRegister);
};
