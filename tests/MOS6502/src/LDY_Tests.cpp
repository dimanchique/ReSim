#include "MOS6502_LD_Tests.h"

class MOS6502_LDYFixture : public MOS6502_LDFixture {};

TEST_F(MOS6502_LDYFixture, LDY_IM_CanLoadValue) {
    LD_IM_CanLoadValue(LDY_IM, cpu.Y);
}

TEST_F(MOS6502_LDYFixture, LDY_IM_CanAffectZeroFlag) {
    LD_IM_CanAffectZeroFlag(LDY_IM);
}

TEST_F(MOS6502_LDYFixture, LDY_IM_CanAffectNegativeFlag) {
    LD_IM_CanAffectNegativeFlag(LDY_IM);
}

TEST_F(MOS6502_LDYFixture, LDY_ZP_CanLoadValue) {
    LD_ZP_CanLoadValue(LDY_ZP, cpu.Y);
}

TEST_F(MOS6502_LDYFixture, LDY_ZPX_CanLoadValue) {
    cpu.X = 0x5;
    LD_ZP_CanLoadValue(LDY_ZPX, cpu.Y, cpu.X);
}

TEST_F(MOS6502_LDYFixture, LDY_ZPX_CanLoadValue_WithWrap) {
    cpu.X = 0xFF;
    LD_ZP_CanLoadValue(LDY_ZPX, cpu.Y, cpu.X);
}

TEST_F(MOS6502_LDYFixture, LDY_ABS_CanLoadValue) {
    LD_ABS_CanLoadValue(LDY_ABS, cpu.Y);
}

TEST_F(MOS6502_LDYFixture, LDY_ABSX_CanLoadValue) {
    cpu.X = 0x01;
    LD_ABS_CanLoadValue(LDY_ABSX, cpu.Y, cpu.X);
}

TEST_F(MOS6502_LDYFixture, LDY_ABSX_CanLoadValue_WithExtraCycleOnPageCrossing) {
    cpu.X = 0xFF;
    LD_ABS_CanLoadValue(LDY_ABSX, cpu.Y, cpu.X);
}
