#pragma once
#include "CPU6502_TestingSuite.h"

class CPU6502_BFixture : public CPU6502_TestFixture{
public:
    void B_REL_CanBranch(CPU6502_OpCodes OpCode, BYTE TargetStatusFlag, bool FlagValue);
    void B_REL_CannotBranch(CPU6502_OpCodes OpCode, BYTE TargetStatusFlag, bool FlagValue);
    void B_REL_CanBranch_WithPageCrossing(CPU6502_OpCodes OpCode, BYTE TargetStatusFlag, bool FlagValue);
};
