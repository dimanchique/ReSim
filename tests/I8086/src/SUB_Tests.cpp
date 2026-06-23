#include "I8086_DoubleOpTests.h"
#include "I8086_SingleOpTests.h"

class I8086_SUB_Fixture : public I8086_DoubleOpFixture {};
class I8086_SUB_IM_Fixture : public I8086_SingleOpFixture {};

// Mem (BX addressed) <-- Mem (BX addressed) - AX
TEST_F(I8086_SUB_Fixture, SUB_Ev_Gv_BX_Addressed_AX) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 0;
    modReg.leftOp.memData.mode = modeBX;

    modReg.rightOp.archetype = OperandArchetype::Reg;
    modReg.rightOp.regData = wAX;

    cpu.AX = 0x0060;
    cpu.BX = 0x009A;
    cpu.DS = 0x4000;
    cyclesExpected = 16 + 5;

    const WORD memValue = 0x0012;
    const DWORD memAddress = cpu.BX + (cpu.DS << 4);
    const WORD refValue = memValue - cpu.AX;

    TestMemRegInstruction(memAddress, memValue, SUB_Ev_Gv, modReg, 16);

    WORD result = mem[memAddress];
    result |= (mem[memAddress + 1] << 8);
    EXPECT_EQ(result, refValue);

    EXPECT_TRUE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

// AX <-- AX - BX
TEST_F(I8086_SUB_Fixture, SUB_Gv_Ev_AX_BX) {
    cpu.AX = 0x4336;
    cpu.BX = 0x0136;
    const BYTE leftReg = wAX;
    const BYTE rightReg = wBX;
    const WORD refValue = cpu.AX - cpu.BX;

    TestRegRegInstruction<WORD>(&leftReg, &rightReg, SUB_Gv_Ev, 16);

    EXPECT_EQ(cpu.AX, refValue);

    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8086_SUB_IM_Fixture, SUB_AL_Ib_Test1) {
    TestAccumulatorWithImmediateData<BYTE>(0x61, 0x65, SUB_AL_Ib, 4);
    EXPECT_EQ(cpu.AL, BYTE(0x61-0x65));

    EXPECT_TRUE(cpu.Status.C);
    EXPECT_TRUE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8086_SUB_IM_Fixture, SUB_AL_Ib_Test2_WithCarry) {
    TestAccumulatorWithImmediateData<BYTE>(0xFF, 0xFF, SUB_AL_Ib, 4);
    EXPECT_EQ(cpu.AL, 0x00);

    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8086_SUB_IM_Fixture, SUB_AX_Iv_Test1) {
    TestAccumulatorWithImmediateData<WORD>(0x1111, 0x2222, SUB_AX_Iv, 4);
    EXPECT_EQ(cpu.AX, WORD(0x1111 - 0x2222));

    EXPECT_TRUE(cpu.Status.C);
    EXPECT_TRUE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8086_SUB_IM_Fixture, SUB_AX_Iv_Test2_WithCarry) {
    TestAccumulatorWithImmediateData<WORD>(0x0000, 0x0001, SUB_AX_Iv, 4);
    EXPECT_EQ(cpu.AX, 0xFFFF);

    EXPECT_TRUE(cpu.Status.C);
    EXPECT_TRUE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8086_SUB_IM_Fixture, SUB_AX_Iv_Test3) {
    TestAccumulatorWithImmediateData<WORD>(0x8001, 0x0001, SUB_AX_Iv, 4);
    EXPECT_EQ(cpu.AX, 0x8000);

    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8086_SUB_Fixture, SUB_Ev_Gv_BP_Addressed_WithDisp_DX) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 2;
    modReg.leftOp.memData.dispValue = 0x100;
    modReg.leftOp.memData.mode = modeBP;

    modReg.rightOp.archetype = OperandArchetype::Reg;
    modReg.rightOp.regData = wDX;

    cpu.DX = 0x0060;
    cpu.SS = 0x2000;
    cyclesExpected = 16 + 9;

    const WORD memValue = 0x12C;
    const DWORD memAddress = modReg.leftOp.memData.dispValue + (cpu.SS << 4);
    const WORD refValue = memValue - cpu.DX;

    TestMemRegInstruction(memAddress, memValue, SUB_Ev_Gv, modReg, 16);

    WORD result = mem[memAddress];
    result |= (mem[memAddress + 1] << 8);
    EXPECT_EQ(result, refValue);
}

TEST_F(I8086_SUB_Fixture, SUB_Gb_Eb_AL_BH) {
    cpu.AL = 0x41;
    cpu.BH = 0x5A;
    const BYTE leftReg = bAL;
    const BYTE rightReg = bBH;
    const BYTE refValue = 0xE7;

    TestRegRegInstruction<BYTE>(&leftReg, &rightReg, SUB_Gb_Eb, 16);

    EXPECT_EQ(cpu.AL, refValue);

    EXPECT_TRUE(cpu.Status.C);
    EXPECT_TRUE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8086_SUB_IM_Fixture, SUB_AL_Ib_ZeroResult) {
    TestAccumulatorWithImmediateData<BYTE>(0x00, 0x00, SUB_AL_Ib, 4);
    EXPECT_EQ(cpu.AL, 0x00);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.P);
}
