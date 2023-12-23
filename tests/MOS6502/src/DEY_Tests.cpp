#include "MOS6502_DEC_Tests.h"

class MOS6502_DEYFixture : public MOS6502_DECFixture {};

TEST_F(MOS6502_DEYFixture, DEY_IMPL_CanAffectY) {
    cpu.Y = 0x9;
    DEC_IMPL_CanAffectValue(DEY_IMPL, cpu.Y);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(MOS6502_DEYFixture, DEY_IMPL_CanAffectZeroFlag) {
    cpu.Y = 0x1;
    DEC_IMPL_CanAffectValue(DEY_IMPL, cpu.Y);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(MOS6502_DEYFixture, DEY_IMPL_CanAffectNegativeFlag) {
    cpu.Y = 0x0;
    DEC_IMPL_CanAffectValue(DEY_IMPL, cpu.Y);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
}