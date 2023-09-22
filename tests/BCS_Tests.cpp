#include "CPU6502_B_Tests.h"

class CPU6502_BCSFixture : public CPU6502_BFixture {};

TEST_F(CPU6502_BCSFixture, BCS_REL_CanBranch){
    B_REL_CanBranch(CPU6502_OpCodes::BCS_REL, CPU6502_Status_C, true);
}

TEST_F(CPU6502_BCSFixture, BCS_REL_CannotBranch){
    B_REL_CannotBranch(CPU6502_OpCodes::BCS_REL, CPU6502_Status_C, false);
}

TEST_F(CPU6502_BCSFixture, BCS_REL_CanBranch_WithPageCrossing){
    B_REL_CanBranch_WithPageCrossing(CPU6502_OpCodes::BCS_REL, CPU6502_Status_C, true);
}
