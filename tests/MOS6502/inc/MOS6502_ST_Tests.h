#pragma once
#include "MOS6502_TestingSuite.h"

class MOS6502_STFixture : public MOS6502_TestFixture {
public:
    void ST_ZP_CanStoreValue(MOS6502_OpCodes opcode, BYTE &sourceRegister);
    void ST_ZP_CanStoreValue(MOS6502_OpCodes opcode, BYTE &sourceRegister, BYTE affectingRegister);
    void ST_ABS_CanStoreValue(MOS6502_OpCodes opcode, BYTE &sourceRegister);
    void ST_ABS_CanStoreValue(MOS6502_OpCodes opcode, BYTE &sourceRegister, BYTE affectingRegister);
};
