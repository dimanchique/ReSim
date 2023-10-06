#include "CPU6502_INC_Tests.h"

class CPU6502_INXFixture : public CPU6502_INCFixture {};

TEST_F(CPU6502_INXFixture, INX_IMPL_CanAffectX) {
    cpu.X = 0x9;
    INC_IMPL_CanAffectValue(INX_IMPL, cpu.X);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(CPU6502_INXFixture, INX_IMPL_CanAffectZeroFlag) {
    cpu.X = 0xFF;
    INC_IMPL_CanAffectValue(INX_IMPL, cpu.X);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(CPU6502_INXFixture, INX_IMPL_CanAffectNegativeFlag) {
    cpu.X = 0xFE;
    INC_IMPL_CanAffectValue(INX_IMPL, cpu.X);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
}
