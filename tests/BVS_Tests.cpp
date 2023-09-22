#include "CPU6502_B_Tests.h"

class CPU6502_BVSFixture : public CPU6502_BFixture {};

TEST_F(CPU6502_BVSFixture, BVS_REL_CanBranch){
    B_REL_CanBranch(CPU6502_OpCodes::BVS_REL, CPU6502_Status_V, true);
}

TEST_F(CPU6502_BVSFixture, BVS_REL_CannotBranch){
    B_REL_CannotBranch(CPU6502_OpCodes::BVS_REL, CPU6502_Status_V, false);
}

TEST_F(CPU6502_BVSFixture, BVS_REL_CanBranch_WithPageCrossing){
    B_REL_CanBranch_WithPageCrossing(CPU6502_OpCodes::BVS_REL, CPU6502_Status_V, true);
}
