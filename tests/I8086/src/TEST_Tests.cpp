#include "I8086_DoubleOpTests.h"
#include "I8086_SingleOpTests.h"

 class I8086_TEST_Fixture : public I8086_DoubleOpFixture {};
 class I8086_TEST_IM_Fixture : public I8086_SingleOpFixture {};

// Mem (BX addressed) <-- AX | Mem (BX addressed)
TEST_F(I8086_TEST_Fixture, TEST_Ev_Gv_BX_Addressed_AX) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 0;
    modReg.leftOp.memData.mode = modeBX;

    modReg.rightOp.archetype = OperandArchetype::Reg;
    modReg.rightOp.regData = wAX;

    const WORD initialAX = 0x0060;
    cpu.AX = initialAX;
    cpu.BX = 0x009A;
    cpu.DS = 0x4000;
    cyclesExpected = 16 + 5;
    cpu.Status.Value = 0;

    const WORD memValue = 0x12C;
    const DWORD memAddress = cpu.BX + (cpu.DS << 4);

    TestMemRegInstruction(memAddress, memValue, TEST_Gv_Ev, modReg, 16);

    EXPECT_EQ(cpu.AX, initialAX);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
    EXPECT_FALSE(cpu.Status.S);
}

// Mem (Direct addressed) <-- BX | Mem (Direct addressed)
TEST_F(I8086_TEST_Fixture, TEST_Ev_Gv_Direct_Addressed_BX) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 0;
    modReg.leftOp.memData.mode = modeDirect;

    modReg.rightOp.archetype = OperandArchetype::Reg;
    modReg.rightOp.regData = wBX;

    const WORD initialBX = 0x0060;
    cpu.BX = initialBX;
    cyclesExpected = 16 + 6;

    const WORD memValue = 0x0000;
    const DWORD memAddress = 0x1000;

    TestMemRegInstruction(memAddress, memValue, TEST_Gv_Ev, modReg, 16);

    EXPECT_EQ(cpu.BX, initialBX);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
    EXPECT_FALSE(cpu.Status.S);
}

// Mem (BP addressed WithDisp) <-- DX | Mem (BP addressed WithDisp)
TEST_F(I8086_TEST_Fixture, TEST_Ev_Gv_BP_Addressed_WithDisp_DX) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 2;
    modReg.leftOp.memData.dispValue = 0x100;
    modReg.leftOp.memData.mode = modeBP;

    modReg.rightOp.archetype = OperandArchetype::Reg;
    modReg.rightOp.regData = wDX;

    const WORD initialDX = 0xFF60;
    cpu.DX = initialDX;
    cpu.SS = 0x2000; // BP is force-replacing by SS
    cyclesExpected = 16 + 9;

    const WORD memValue = 0xFF60;
    const DWORD memAddress = modReg.leftOp.memData.dispValue + (cpu.SS << 4);

    TestMemRegInstruction(memAddress, memValue, TEST_Gv_Ev, modReg, 16);

    EXPECT_EQ(cpu.DX, initialDX);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
    EXPECT_TRUE(cpu.Status.S);
}

// Mem (BX SI addressed WithDisp) <-- AX | Mem (BX SI addressed WithDisp)
TEST_F(I8086_TEST_Fixture, TEST_Ev_Gv_BXSI_Addressed_WithDisp_AX) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 1;
    modReg.leftOp.memData.dispValue = 0xAD;
    modReg.leftOp.memData.mode = modeBXpSI;

    modReg.rightOp.archetype = OperandArchetype::Reg;
    modReg.rightOp.regData = wAX;

    const WORD initialAX = 0xFF60;
    cpu.AX = 0xFF60;
    cpu.BX = 0x8000;
    cpu.SI = 0x1000;
    cpu.DS = 0x2000;
    cyclesExpected = 16 + 11;

    const WORD memValue = 0x12C;
    const DWORD memAddress = cpu.BX + cpu.SI + modReg.leftOp.memData.dispValue + (cpu.DS << 4);

    TestMemRegInstruction(memAddress, memValue, TEST_Gv_Ev, modReg, 16);

    EXPECT_EQ(cpu.AX, initialAX);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
    EXPECT_FALSE(cpu.Status.S);
}

// AX <-- AX | BX
TEST_F(I8086_TEST_Fixture, TEST_Gv_Ev_AX_BX) {
    const WORD initialAX = 0x0060;
    cpu.AX = initialAX;
    cpu.BX = 0x009A;
    const BYTE leftReg = wAX;
    const BYTE rightReg = wBX;

    TestRegRegInstruction<WORD>(&leftReg, &rightReg, TEST_Gv_Ev, 16);

    EXPECT_EQ(cpu.AX, initialAX);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
    EXPECT_FALSE(cpu.Status.S);
}

// BX <-- BX | DI
TEST_F(I8086_TEST_Fixture, TEST_Gv_Ev_BX_DI) {
    const WORD initialBX = 0x0060;
    cpu.BX = initialBX;
    cpu.DI = 0x009A;
    const BYTE leftReg = wBX;
    const BYTE rightReg = wDI;

    TestRegRegInstruction<WORD>(&leftReg, &rightReg, TEST_Gv_Ev, 16);

    EXPECT_EQ(cpu.BX, initialBX);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
    EXPECT_FALSE(cpu.Status.S);
}

// AL <-- AL | BH
TEST_F(I8086_TEST_Fixture, TEST_Gb_Eb_AL_BH) {
    const BYTE initialAL = 0x60;
    cpu.AL = initialAL;
    cpu.BH = 0x9A;
    const BYTE leftReg = bAL;
    const BYTE rightReg = bBH;

    TestRegRegInstruction<BYTE>(&leftReg, &rightReg, TEST_Gb_Eb, 16);

    EXPECT_EQ(cpu.AL, initialAL);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
    EXPECT_FALSE(cpu.Status.S);
}

// BL <-- BL | CL
TEST_F(I8086_TEST_Fixture, TEST_Gb_Eb_BL_CL) {
    const BYTE initialBL = 0xF0;
    cpu.BL = initialBL;
    cpu.CL = 0xF0;
    const BYTE leftReg = bBL;
    const BYTE rightReg = bCL;

    TestRegRegInstruction<BYTE>(&leftReg, &rightReg, TEST_Gb_Eb, 16);

    EXPECT_EQ(cpu.BL, initialBL);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
    EXPECT_TRUE(cpu.Status.S);
}

TEST_F(I8086_TEST_IM_Fixture, TEST_AL_Ib_Test1) {
    TestAccumulatorWithImmediateData<BYTE>(0x11, 0x22, TEST_AL_Ib, 4);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
    EXPECT_FALSE(cpu.Status.S);
}

TEST_F(I8086_TEST_IM_Fixture, TEST_AL_Ib_Test2) {
    TestAccumulatorWithImmediateData<BYTE>(0x10, 0x01, TEST_AL_Ib, 4);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
    EXPECT_FALSE(cpu.Status.S);
}

TEST_F(I8086_TEST_IM_Fixture, TEST_AL_Ib_Test3) {
    TestAccumulatorWithImmediateData<BYTE>(0x00, 0x00, TEST_AL_Ib, 4);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
    EXPECT_FALSE(cpu.Status.S);
}

TEST_F(I8086_TEST_IM_Fixture, TEST_AL_Ib_Test4) {
    TestAccumulatorWithImmediateData<BYTE>(0xFF, 0xFF, TEST_AL_Ib, 4);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
    EXPECT_TRUE(cpu.Status.S);
}

TEST_F(I8086_TEST_IM_Fixture, TEST_AL_Ib_Test5) {
    TestAccumulatorWithImmediateData<BYTE>(0xFF, 0x00, TEST_AL_Ib, 4);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
    EXPECT_FALSE(cpu.Status.S);
}

TEST_F(I8086_TEST_IM_Fixture, TEST_AL_Iv_Test1) {
    TestAccumulatorWithImmediateData<WORD>(0x1111, 0x2222, TEST_AX_Iv, 4);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
    EXPECT_FALSE(cpu.Status.S);
}

TEST_F(I8086_TEST_IM_Fixture, TEST_AL_Iv_Test2) {
    TestAccumulatorWithImmediateData<WORD>(0x1010, 0x0101, TEST_AX_Iv, 4);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
    EXPECT_FALSE(cpu.Status.S);
}

TEST_F(I8086_TEST_IM_Fixture, TEST_AL_Iv_Test3) {
    TestAccumulatorWithImmediateData<WORD>(0x0000, 0x0000, TEST_AX_Iv, 4);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
    EXPECT_FALSE(cpu.Status.S);
}

TEST_F(I8086_TEST_IM_Fixture, TEST_AL_Iv_Test4) {
    TestAccumulatorWithImmediateData<WORD>(0xFFFF, 0xFFFF, TEST_AX_Iv, 4);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
    EXPECT_TRUE(cpu.Status.S);
}

TEST_F(I8086_TEST_IM_Fixture, TEST_AL_Iv_Test5) {
    TestAccumulatorWithImmediateData<WORD>(0xFFFF, 0x0000, TEST_AX_Iv, 4);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
    EXPECT_FALSE(cpu.Status.S);
}
