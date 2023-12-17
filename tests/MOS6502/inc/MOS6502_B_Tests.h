#pragma once
#include "MOS6502_TestingSuite.h"

class MOS6502_BFixture : public MOS6502_TestFixture {
public:
    void B_REL_CanBranch(MOS6502_OpCodes opcode, BYTE targetStatusFlag, bool flagValue);
    void B_REL_CannotBranch(MOS6502_OpCodes opcode, BYTE targetStatusFlag, bool flagValue);
    void B_REL_CanBranch_WithPageCrossing(MOS6502_OpCodes opcode, BYTE targetStatusFlag, bool flagValue);
};
