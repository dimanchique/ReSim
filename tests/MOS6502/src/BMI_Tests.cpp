#include "MOS6502_B_Tests.h"

class MOS6502_BMIFixture : public MOS6502_BFixture {};

TEST_F(MOS6502_BMIFixture, BMI_REL_CanBranch) {
    B_REL_CanBranch(BMI_REL, MOS6502_Status_N, true);
}

TEST_F(MOS6502_BMIFixture, BMI_REL_CannotBranch) {
    B_REL_CannotBranch(BMI_REL, MOS6502_Status_N, false);
}

TEST_F(MOS6502_BMIFixture, BMI_REL_CanBranch_WithPageCrossing) {
    B_REL_CanBranch_WithPageCrossing(BMI_REL, MOS6502_Status_N, true);
}
