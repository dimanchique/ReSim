#include "MOS6502_LD_Tests.h"

class MOS6502_LDXFixture : public MOS6502_LDFixture {};

TEST_F(MOS6502_LDXFixture, LDX_IM_CanLoadValue) {
    LD_IM_CanLoadValue(LDX_IM, cpu.X);
}

TEST_F(MOS6502_LDXFixture, LDX_IM_CanAffectZeroFlag) {
    LD_IM_CanAffectZeroFlag(LDX_IM);
}

TEST_F(MOS6502_LDXFixture, LDX_IM_CanAffectNegativeFlag) {
    LD_IM_CanAffectNegativeFlag(LDX_IM);
}

TEST_F(MOS6502_LDXFixture, LDX_ZP_CanLoadValue) {
    LD_ZP_CanLoadValue(LDX_ZP, cpu.X);
}

TEST_F(MOS6502_LDXFixture, LDX_ZPY_CanLoadValue) {
    cpu.Y = 0x5;
    LD_ZP_CanLoadValue(LDX_ZPY, cpu.X, cpu.Y);
}

TEST_F(MOS6502_LDXFixture, LDX_ZPY_CanLoadValue_WithWrap) {
    cpu.Y = 0xFF;
    LD_ZP_CanLoadValue(LDX_ZPY, cpu.X, cpu.Y);
}

TEST_F(MOS6502_LDXFixture, LDX_ABS_CanLoadValue) {
    LD_ABS_CanLoadValue(LDX_ABS, cpu.X);
}

TEST_F(MOS6502_LDXFixture, LDX_ABSY_CanLoadValue) {
    cpu.Y = 0x01;
    LD_ABS_CanLoadValue(LDX_ABSY, cpu.X, cpu.Y);
}

TEST_F(MOS6502_LDXFixture, LDX_ABSY_CanLoadValue_WithExtraCycleOnPageCrossing) {
    cpu.Y = 0xFF;
    LD_ABS_CanLoadValue(LDX_ABSY, cpu.X, cpu.Y);
}
