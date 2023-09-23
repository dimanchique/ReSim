#include "CPU6502_CM_Tests.h"

class CPU6502_CPYFixture : public CPU6502_CMFixture{};

TEST_F(CPU6502_CPYFixture, CPY_IM_CanCompare){
    CM_IM(CPU6502_OpCodes::CPY_IM, cpu.Y, 0x10, 0x4);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
}

TEST_F(CPU6502_CPYFixture, CPY_IM_CanAffectZeroFlag){
    CM_IM(CPU6502_OpCodes::CPY_IM, cpu.Y, 0x10, 0x10);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(CPU6502_CPYFixture, CPY_IM_CanAffectNegativeFlag){
    CM_IM(CPU6502_OpCodes::CPY_IM, cpu.Y, 0x10, 0x11);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(CPU6502_CPYFixture, CPY_ZP_CanCompare){
    CM_ZP(CPU6502_OpCodes::CPY_ZP, cpu.Y, 0x10, 0x4);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
}

TEST_F(CPU6502_CPYFixture, CPY_ABS_CanCompare){
    CM_ABS(CPU6502_OpCodes::CPY_ABS, cpu.Y, 0x10, 0x4);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
}
