#include "CPU6502_B_Tests.h"

class CPU6502_BMIFixture : public CPU6502_BFixture {};

TEST_F(CPU6502_BMIFixture, BMI_REL_CanBranch){
    B_REL_CanBranch(CPU6502_OpCodes::BMI_REL, CPU6502_Status_N, true);
}

TEST_F(CPU6502_BMIFixture, BMI_REL_CannotBranch){
    B_REL_CannotBranch(CPU6502_OpCodes::BMI_REL, CPU6502_Status_N, false);
}

TEST_F(CPU6502_BMIFixture, BMI_REL_CanBranch_WithPageCrossing){
    B_REL_CanBranch_WithPageCrossing(CPU6502_OpCodes::BMI_REL, CPU6502_Status_N, true);
}
