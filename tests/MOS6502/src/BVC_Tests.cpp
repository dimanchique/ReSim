#include "MOS6502_B_Tests.h"

class MOS6502_BVCFixture : public MOS6502_BFixture {};

TEST_F(MOS6502_BVCFixture, BVC_REL_CanBranch) {
    B_REL_CanBranch(BVC_REL, MOS6502_Status_V, false);
}

TEST_F(MOS6502_BVCFixture, BVC_REL_CannotBranch) {
    B_REL_CannotBranch(BVC_REL, MOS6502_Status_V, true);
}

TEST_F(MOS6502_BVCFixture, BVC_REL_CanBranch_WithPageCrossing) {
    B_REL_CanBranch_WithPageCrossing(BVC_REL, MOS6502_Status_V, false);
}
