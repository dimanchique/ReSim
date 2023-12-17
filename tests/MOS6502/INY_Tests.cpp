#include "MOS6502_INC_Tests.h"

class MOS6502_INYFixture : public MOS6502_INCFixture {};

TEST_F(MOS6502_INYFixture, INY_IMPL_CanAffectY) {
    cpu.Y = 0x9;
    INC_IMPL_CanAffectValue(INY_IMPL, cpu.Y);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(MOS6502_INYFixture, INY_IMPL_CanAffectZeroFlag) {
    cpu.Y = 0xFF;
    INC_IMPL_CanAffectValue(INY_IMPL, cpu.Y);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(MOS6502_INYFixture, INY_IMPL_CanAffectNegativeFlag) {
    cpu.Y = 0xFE;
    INC_IMPL_CanAffectValue(INY_IMPL, cpu.Y);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
}