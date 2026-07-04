#include "I8086_DoubleOpTests.h"
#include "I8086_SingleOpTests.h"

class I8086_CMP_Fixture : public I8086_DoubleOpFixture {};
class I8086_CMP_IM_Fixture : public I8086_SingleOpFixture {};

// CMP [BX], AX — flags only, no write
TEST_F(I8086_CMP_Fixture, CMP_Ev_Gv_BX_Addressed_AX) {
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

    TestMemRegInstruction(memAddress, memValue, CMP_Ev_Gv, modReg, 16);

    WORD result = mem[memAddress];
    result |= (mem[memAddress + 1] << 8);
    EXPECT_EQ(result, memValue);

    EXPECT_TRUE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

// CMP AX, BX — flags only, no write
TEST_F(I8086_CMP_Fixture, CMP_Gv_Ev_AX_BX) {
    cpu.AX = 0x4336;
    cpu.BX = 0x0136;

    const BYTE leftReg = wAX;
    const BYTE rightReg = wBX;

    TestRegRegInstruction<WORD>(&leftReg, &rightReg, CMP_Gv_Ev, 16);

    EXPECT_EQ(cpu.AX, 0x4336);
    EXPECT_EQ(cpu.BX, 0x0136);

    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8086_CMP_IM_Fixture, CMP_AL_Ib_Test1) {
    TestAccumulatorWithImmediateData<BYTE>(0x61, 0x65, CMP_AL_Ib, 4);
    EXPECT_EQ(cpu.AL, 0x61);

    EXPECT_TRUE(cpu.Status.C);
    EXPECT_TRUE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8086_CMP_IM_Fixture, CMP_AL_Ib_Equal) {
    TestAccumulatorWithImmediateData<BYTE>(0xFF, 0xFF, CMP_AL_Ib, 4);
    EXPECT_EQ(cpu.AL, 0xFF);

    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8086_CMP_IM_Fixture, CMP_AX_Iv_Test1) {
    TestAccumulatorWithImmediateData<WORD>(0x1111, 0x2222, CMP_AX_Iv, 4);
    EXPECT_EQ(cpu.AX, 0x1111);

    EXPECT_TRUE(cpu.Status.C);
    EXPECT_TRUE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8086_CMP_IM_Fixture, CMP_AX_Iv_Borrow) {
    TestAccumulatorWithImmediateData<WORD>(0x0000, 0x0001, CMP_AX_Iv, 4);
    EXPECT_EQ(cpu.AX, 0x0000);

    EXPECT_TRUE(cpu.Status.C);
    EXPECT_TRUE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8086_CMP_IM_Fixture, CMP_AX_Iv_NoBorrow) {
    TestAccumulatorWithImmediateData<WORD>(0x8001, 0x0001, CMP_AX_Iv, 4);
    EXPECT_EQ(cpu.AX, 0x8001);

    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8086_CMP_Fixture, CMP_Ev_Gv_BP_Addressed_WithDisp_DX) {
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

    TestMemRegInstruction(memAddress, memValue, CMP_Ev_Gv, modReg, 16);

    WORD result = mem[memAddress];
    result |= (mem[memAddress + 1] << 8);
    EXPECT_EQ(result, memValue);
}

TEST_F(I8086_CMP_Fixture, CMP_Gb_Eb_AL_BH) {
    cpu.AL = 0x41;
    cpu.BH = 0x5A;
    const BYTE leftReg = bAL;
    const BYTE rightReg = bBH;

    TestRegRegInstruction<BYTE>(&leftReg, &rightReg, CMP_Gb_Eb, 16);

    EXPECT_EQ(cpu.AL, 0x41);
    EXPECT_EQ(cpu.BH, 0x5A);

    EXPECT_TRUE(cpu.Status.C);
    EXPECT_TRUE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8086_CMP_IM_Fixture, CMP_AL_Ib_Zero) {
    TestAccumulatorWithImmediateData<BYTE>(0x00, 0x00, CMP_AL_Ib, 4);
    EXPECT_EQ(cpu.AL, 0x00);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.P);
}
