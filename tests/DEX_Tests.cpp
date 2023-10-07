#include "CPU6502_DEC_Tests.h"

class CPU6502_DEXFixture : public CPU6502_DECFixture {};

TEST_F(CPU6502_DEXFixture, DEX_IMPL_CanAffectX) {
    cpu.X = 0x9;
    DEC_IMPL_CanAffectValue(DEX_IMPL, cpu.X);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(CPU6502_DEXFixture, DEX_IMPL_CanAffectZeroFlag) {
    cpu.X = 0x1;
    DEC_IMPL_CanAffectValue(DEX_IMPL, cpu.X);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(CPU6502_DEXFixture, DEX_IMPL_CanAffectNegativeFlag) {
    cpu.X = 0x0;
    DEC_IMPL_CanAffectValue(DEX_IMPL, cpu.X);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
}
