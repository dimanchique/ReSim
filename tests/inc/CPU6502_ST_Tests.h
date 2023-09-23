#pragma once
#include "CPU6502_TestingSuite.h"

class CPU6502_STFixture : public CPU6502_TestFixture{
public:
    void ST_ZP_CanStoreValue(CPU6502_OpCodes opcode, BYTE& sourceRegister);
    void ST_ZP_CanStoreValue(CPU6502_OpCodes opcode, BYTE& sourceRegister, BYTE affectingRegister);
    void ST_ABS_CanStoreValue(CPU6502_OpCodes opcode, BYTE& sourceRegister);
    void ST_ABS_CanStoreValue(CPU6502_OpCodes opcode, BYTE& sourceRegister, BYTE affectingRegister);
};
