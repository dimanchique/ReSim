#include "MOS6502_B_Tests.h"

class MOS6502_BVSFixture : public MOS6502_BFixture {};

TEST_F(MOS6502_BVSFixture, BVS_REL_CanBranch) {
    B_REL_CanBranch(MOS6502_OpCodes::BVS_REL, MOS6502_Status_V, true);
}

TEST_F(MOS6502_BVSFixture, BVS_REL_CannotBranch) {
    B_REL_CannotBranch(MOS6502_OpCodes::BVS_REL, MOS6502_Status_V, false);
}

TEST_F(MOS6502_BVSFixture, BVS_REL_CanBranch_WithPageCrossing) {
    B_REL_CanBranch_WithPageCrossing(MOS6502_OpCodes::BVS_REL, MOS6502_Status_V, true);
}
