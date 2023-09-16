#include "CPU6502_DE_Tests.h"

class CPU6502_DEYFixture : public CPU6502_DEFixture{};

TEST_F(CPU6502_DEYFixture, DEY_IMPL_CanAffectY){
    cpu.Y = 0x9;
    DE_IMPL_CanAffectValue(DEY_IMPL, cpu.Y);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(CPU6502_DEYFixture, DEY_IMPL_CanAffectZeroFlag){
    cpu.Y = 0x1;
    DE_IMPL_CanAffectValue(DEY_IMPL, cpu.Y);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(CPU6502_DEYFixture, DEY_IMPL_CanAffectNegativeFlag){
    cpu.Y = 0x0;
    DE_IMPL_CanAffectValue(DEY_IMPL, cpu.Y);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
}