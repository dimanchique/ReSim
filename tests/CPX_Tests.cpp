#include "CPU6502_CM_Tests.h"

class CPU6502_CPXFixture : public CPU6502_CMFixture{};

TEST_F(CPU6502_CPXFixture, CPX_IM_CanCompare){
    CM_IM(CPU6502_OpCodes::CPX_IM, cpu.X, 0x10, 0x4);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
}

TEST_F(CPU6502_CPXFixture, CPX_IM_CanAffectZeroFlag){
    CM_IM(CPU6502_OpCodes::CPX_IM, cpu.X, 0x10, 0x10);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(CPU6502_CPXFixture, CPX_IM_CanAffectNegativeFlag){
    CM_IM(CPU6502_OpCodes::CPX_IM, cpu.X, 0x10, 0x11);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(CPU6502_CPXFixture, CPX_ZP_CanCompare){
    CM_ZP(CPU6502_OpCodes::CPX_ZP, cpu.X, 0x10, 0x4);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
}

TEST_F(CPU6502_CPXFixture, CPX_ABS_CanCompare){
    CM_ABS(CPU6502_OpCodes::CPX_ABS, cpu.X, 0x10, 0x4);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
}
