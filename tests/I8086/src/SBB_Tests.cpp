#include "I8086_DoubleOpTests.h"
#include "I8086_SingleOpTests.h"

class I8086_SBB_Fixture : public I8086_DoubleOpFixture {
};

class I8086_SBB_IM_Fixture : public I8086_SingleOpFixture {
};

TEST_F(I8086_SBB_Fixture, SBB_Ev_Gv_BX_Addressed_AX) {
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

    TestMemRegInstruction(memAddress, memValue, SBB_Ev_Gv, modReg, 16);

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

TEST_F(I8086_SBB_Fixture, SBB_Gv_Ev_AX_BX) {
    cpu.AX = 0x4336;
    cpu.BX = 0x0136;
    const BYTE leftReg = wAX;
    const BYTE rightReg = wBX;
    const WORD refValue = cpu.AX - cpu.BX;

    TestRegRegInstruction<WORD>(&leftReg, &rightReg, SBB_Gv_Ev, 16);

    EXPECT_EQ(cpu.AX, refValue);

    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8086_SBB_IM_Fixture, SBB_AL_Ib_Test1) {
    TestAccumulatorWithImmediateData<BYTE>(0x65, 0x61, SBB_AL_Ib, 4);
    EXPECT_EQ(cpu.AL, BYTE(0x65 - 0x61));

    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8086_SBB_IM_Fixture, SBB_AL_Ib_Test2_WithBorrow) {
    TestAccumulatorWithImmediateData<BYTE>(0xFF, 0xFF, SBB_AL_Ib, 4);
    EXPECT_EQ(cpu.AL, 0x00);

    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8086_SBB_IM_Fixture, SBB_AX_Iv_Test1) {
    TestAccumulatorWithImmediateData<WORD>(0x2222, 0x1111, SBB_AX_Iv, 4);
    EXPECT_EQ(cpu.AX, WORD(0x2222 - 0x1111));

    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8086_SBB_IM_Fixture, SBB_AX_Iv_Test2) {
    TestAccumulatorWithImmediateData<WORD>(0x0001, 0x0000, SBB_AX_Iv, 4);
    EXPECT_EQ(cpu.AX, 0x0001);

    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8086_SBB_IM_Fixture, SBB_AX_Iv_Test3) {
    TestAccumulatorWithImmediateData<WORD>(0x0000, 0x0001, SBB_AX_Iv, 4);
    EXPECT_EQ(cpu.AX, 0xFFFF);

    EXPECT_TRUE(cpu.Status.C);
    EXPECT_TRUE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8086_SBB_Fixture, SBB_Ev_Gv_BP_Addressed_WithDisp_DX) {
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

    TestMemRegInstruction(memAddress, memValue, SBB_Ev_Gv, modReg, 16);

    WORD result = mem[memAddress];
    result |= (mem[memAddress + 1] << 8);
    EXPECT_EQ(result, refValue);
}

TEST_F(I8086_SBB_Fixture, SBB_Gb_Eb_AL_BH) {
    cpu.AL = 0x41;
    cpu.BH = 0x5A;
    const BYTE leftReg = bAL;
    const BYTE rightReg = bBH;
    const BYTE refValue = 0xE7;

    TestRegRegInstruction<BYTE>(&leftReg, &rightReg, SBB_Gb_Eb, 16);

    EXPECT_EQ(cpu.AL, refValue);

    EXPECT_TRUE(cpu.Status.C);
    EXPECT_TRUE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8086_SBB_IM_Fixture, SBB_AL_Ib_ZeroResult) {
    TestAccumulatorWithImmediateData<BYTE>(0x00, 0x00, SBB_AL_Ib, 4);
    EXPECT_EQ(cpu.AL, 0x00);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8086_SBB_Fixture, SBB_Gv_Ev_AX_BX_WithBorrow) {
    cpu.AX = 0x4336;
    cpu.BX = 0x0136;
    cpu.Status.C = 1;
    const BYTE leftReg = wAX;
    const BYTE rightReg = wBX;
    const WORD refValue = cpu.AX - cpu.BX - 1;

    TestRegRegInstruction<WORD>(&leftReg, &rightReg, SBB_Gv_Ev, 16);

    EXPECT_EQ(cpu.AX, refValue);

    EXPECT_FALSE(cpu.Status.C);
    EXPECT_TRUE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8086_SBB_IM_Fixture, SBB_AL_Ib_Test1_WithBorrow) {
    cpu.Status.C = 1;
    TestAccumulatorWithImmediateData<BYTE>(0x65, 0x61, SBB_AL_Ib, 4);
    EXPECT_EQ(cpu.AL, 0x65 - 0x61 - 1);

    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8086_SBB_IM_Fixture, SBB_AL_Ib_Test2_WithBorrow_WithBorrow) {
    cpu.Status.C = 1;
    TestAccumulatorWithImmediateData<BYTE>(0xFF, 0x01, SBB_AL_Ib, 4);
    EXPECT_EQ(cpu.AL, 0xFF - 0x01 - 1);

    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8086_SBB_IM_Fixture, SBB_AL_Ib_Test3_WithOverflow_WithBorrow) {
    cpu.Status.C = 1;
    TestAccumulatorWithImmediateData<BYTE>(0x80, 0x01, SBB_AL_Ib, 4);
    EXPECT_EQ(cpu.AL, 0x80 - 0x01 - 1);

    EXPECT_FALSE(cpu.Status.C);
    EXPECT_TRUE(cpu.Status.A);
    EXPECT_TRUE(cpu.Status.O);
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8086_SBB_IM_Fixture, SBB_AX_Iv_Test1_WithBorrow) {
    cpu.Status.C = 1;
    TestAccumulatorWithImmediateData<WORD>(0x2222, 0x1111, SBB_AX_Iv, 4);
    EXPECT_EQ(cpu.AX, 0x2222 - 0x1111 - 1);

    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8086_SBB_IM_Fixture, SBB_AX_Iv_Test2_WithBorrow_WithBorrow) {
    cpu.Status.C = 1;
    TestAccumulatorWithImmediateData<WORD>(0xFFFF, 0x0001, SBB_AX_Iv, 4);
    EXPECT_EQ(cpu.AX, 0xFFFD);

    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8086_SBB_IM_Fixture, SBB_AX_Iv_Test3_WithOverflow_WithBorrow) {
    cpu.Status.C = 1;
    TestAccumulatorWithImmediateData<WORD>(0x8000, 0x0001, SBB_AX_Iv, 4);
    EXPECT_EQ(cpu.AX, 0x7FFE);

    EXPECT_FALSE(cpu.Status.C);
    EXPECT_TRUE(cpu.Status.A);
    EXPECT_TRUE(cpu.Status.O);
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8086_SBB_Fixture, SBB_Ev_Gv_BX_Addressed_AX_WithBorrow) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 0;
    modReg.leftOp.memData.mode = modeBX;

    modReg.rightOp.archetype = OperandArchetype::Reg;
    modReg.rightOp.regData = wAX;

    cpu.AX = 0x0060;
    cpu.BX = 0x009A;
    cpu.DS = 0x4000;
    cpu.Status.C = 1;
    cyclesExpected = 16 + 5;

    const WORD memValue = 0x12C;
    const DWORD memAddress = cpu.BX + (cpu.DS << 4);
    const WORD refValue = memValue - cpu.AX - 1;

    TestMemRegInstruction(memAddress, memValue, SBB_Ev_Gv, modReg, 16);

    WORD result = mem[memAddress];
    result |= (mem[memAddress + 1] << 8);
    EXPECT_EQ(result, refValue);
}

TEST_F(I8086_SBB_Fixture, SBB_Gb_Eb_AL_BH_WithBorrow) {
    cpu.AL = 0x60;
    cpu.BH = 0x9A;
    cpu.Status.C = 1;
    const BYTE leftReg = bAL;
    const BYTE rightReg = bBH;
    const BYTE refValue = 0x60 - 0x9A - 1;

    TestRegRegInstruction<BYTE>(&leftReg, &rightReg, SBB_Gb_Eb, 16);

    EXPECT_EQ(cpu.AL, refValue);
}

TEST_F(I8086_SBB_IM_Fixture, SBB_AL_Ib_ZeroResult_WithBorrow) {
    cpu.Status.C = 1;
    TestAccumulatorWithImmediateData<BYTE>(0x01, 0x00, SBB_AL_Ib, 4);
    EXPECT_EQ(cpu.AL, 0x00);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.P);
}
