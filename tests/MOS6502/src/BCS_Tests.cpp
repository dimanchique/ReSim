#include "MOS6502_B_Tests.h"

class MOS6502_BCSFixture : public MOS6502_BFixture {};

TEST_F(MOS6502_BCSFixture, BCS_REL_CanBranch) {
    B_REL_CanBranch(BCS_REL, MOS6502_Status_C, true);
}

TEST_F(MOS6502_BCSFixture, BCS_REL_CannotBranch) {
    B_REL_CannotBranch(BCS_REL, MOS6502_Status_C, false);
}

TEST_F(MOS6502_BCSFixture, BCS_REL_CanBranch_WithPageCrossing) {
    B_REL_CanBranch_WithPageCrossing(BCS_REL, MOS6502_Status_C, true);
}
