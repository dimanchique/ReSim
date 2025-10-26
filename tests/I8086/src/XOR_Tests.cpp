#include "I8086_DoubleOpTests.h"
#include "I8086_SingleOpTests.h"

class I8086_XOR_Fixture : public I8086_DoubleOpFixture {};
class I8086_XOR_IM_Fixture : public I8086_SingleOpFixture {};

// Mem (BX addressed) <-- AX ^ Mem (BX addressed)
TEST_F(I8086_XOR_Fixture, XOR_Ev_Gv_BX_Addressed_AX) {
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

    const WORD memValue = 0x12C;
    const DWORD memAddress = cpu.BX + (cpu.DS << 4);
    const WORD refValue = cpu.AX ^ memValue;

    TestMemRegInstruction(memAddress, memValue, XOR_Ev_Gv, modReg, 16);

    WORD result = mem[memAddress];
    result |= (mem[memAddress + 1] << 8);
    EXPECT_EQ(result, refValue);
}

// Mem (Direct addressed) <-- BX ^ Mem (Direct addressed)
TEST_F(I8086_XOR_Fixture, XOR_Ev_Gv_Direct_Addressed_BX) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 0;
    modReg.leftOp.memData.mode = modeDirect;

    modReg.rightOp.archetype = OperandArchetype::Reg;
    modReg.rightOp.regData = wBX;

    cpu.BX = 0x0060;
    cyclesExpected = 16 + 6;

    const WORD memValue = 0x12C;
    const DWORD memAddress = 0x1000;
    const WORD refValue = cpu.BX ^ memValue;

    TestMemRegInstruction(memAddress, memValue, XOR_Ev_Gv, modReg, 16);

    WORD result = mem[memAddress];
    result |= (mem[memAddress + 1] << 8);
    EXPECT_EQ(result, refValue);
}

// Mem (BP addressed WithDisp) <-- DX ^ Mem (BP addressed WithDisp)
TEST_F(I8086_XOR_Fixture, XOR_Ev_Gv_BP_Addressed_WithDisp_DX) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 2;
    modReg.leftOp.memData.dispValue = 0x100;
    modReg.leftOp.memData.mode = modeBP;

    modReg.rightOp.archetype = OperandArchetype::Reg;
    modReg.rightOp.regData = wDX;

    cpu.DX = 0x0060;
    cpu.SS = 0x2000; // BP is force-replacing by SS
    cyclesExpected = 16 + 9;

    const WORD memValue = 0x12C;
    const DWORD memAddress = modReg.leftOp.memData.dispValue + (cpu.SS << 4);
    const WORD refValue = cpu.DX ^ memValue;

    TestMemRegInstruction(memAddress, memValue, XOR_Ev_Gv, modReg, 16);

    WORD result = mem[memAddress];
    result |= (mem[memAddress + 1] << 8);
    EXPECT_EQ(result, refValue);
}

// Mem (BX SI addressed WithDisp) <-- AX ^ Mem (BX SI addressed WithDisp)
TEST_F(I8086_XOR_Fixture, XOR_Ev_Gv_BXSI_Addressed_WithDisp_AX) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 1;
    modReg.leftOp.memData.dispValue = 0xAD;
    modReg.leftOp.memData.mode = modeBXpSI;

    modReg.rightOp.archetype = OperandArchetype::Reg;
    modReg.rightOp.regData = wAX;

    cpu.AX = 0x0060;
    cpu.BX = 0x8000;
    cpu.SI = 0x1000;
    cpu.DS = 0x2000;
    cyclesExpected = 16 + 11;

    const WORD memValue = 0x12C;
    const DWORD memAddress = cpu.BX + cpu.SI + modReg.leftOp.memData.dispValue + (cpu.DS << 4);
    const WORD refValue = cpu.AX ^ memValue;

    TestMemRegInstruction(memAddress, memValue, XOR_Ev_Gv, modReg, 16);

    WORD result = mem[memAddress];
    result |= (mem[memAddress + 1] << 8);
    EXPECT_EQ(result, refValue);
}

// AX <-- AX ^ BX
TEST_F(I8086_XOR_Fixture, XOR_Gv_Ev_AX_BX) {
    cpu.AX = 0x0060;
    cpu.BX = 0x009A;
    const BYTE leftReg = wAX;
    const BYTE rightReg = wBX;
    const WORD refValue = cpu.AX ^ cpu.BX;

    TestRegRegInstruction<WORD>(&leftReg, &rightReg, XOR_Gv_Ev, 16);

    EXPECT_EQ(cpu.AX, refValue);
}

// BX <-- BX ^ DI
TEST_F(I8086_XOR_Fixture, XOR_Gv_Ev_BX_DI) {
    cpu.BX = 0x0060;
    cpu.DI = 0x009A;
    const BYTE leftReg = wBX;
    const BYTE rightReg = wDI;
    const WORD refValue = cpu.BX ^ cpu.DI;

    TestRegRegInstruction<WORD>(&leftReg, &rightReg, XOR_Gv_Ev, 16);

    EXPECT_EQ(cpu.BX, refValue);
}

// AL <-- AL ^ BH
TEST_F(I8086_XOR_Fixture, XOR_Gb_Eb_AL_BH) {
    cpu.AL = 0x60;
    cpu.BH = 0x9A;
    const BYTE leftReg = bAL;
    const BYTE rightReg = bBH;
    const BYTE refValue = cpu.AL ^ cpu.BH;

    TestRegRegInstruction<BYTE>(&leftReg, &rightReg, XOR_Gb_Eb, 16);

    EXPECT_EQ(cpu.AL, refValue);
}

// BL <-- BL ^ CL
TEST_F(I8086_XOR_Fixture, XOR_Gb_Eb_BL_CL) {
    cpu.BL = 0x0060;
    cpu.CL = 0x009A;
    const BYTE leftReg = bBL;
    const BYTE rightReg = bCL;
    const BYTE refValue = cpu.BL ^ cpu.CL;

    TestRegRegInstruction<BYTE>(&leftReg, &rightReg, XOR_Gb_Eb, 16);

    EXPECT_EQ(cpu.BL, refValue);
}

TEST_F(I8086_XOR_IM_Fixture, XOR_AL_Ib_Test1) {
    TestAccumulatorWithImmediateData<BYTE>(0x11, 0x22, XOR_AL_Ib, 4);
    EXPECT_EQ(cpu.AL, 0x11 ^ 0x22);
}

TEST_F(I8086_XOR_IM_Fixture, XOR_AL_Ib_Test2) {
    TestAccumulatorWithImmediateData<BYTE>(0x10, 0x01, XOR_AL_Ib, 4);
    EXPECT_EQ(cpu.AL, 0x10 ^ 0x01);
}

TEST_F(I8086_XOR_IM_Fixture, XOR_AL_Ib_Test3) {
    TestAccumulatorWithImmediateData<BYTE>(0x00, 0x00, XOR_AL_Ib, 4);
    EXPECT_EQ(cpu.AL, 0x00 ^ 0x00);
}

TEST_F(I8086_XOR_IM_Fixture, XOR_AL_Ib_Test4) {
    TestAccumulatorWithImmediateData<BYTE>(0xFF, 0xFF, XOR_AL_Ib, 4);
    EXPECT_EQ(cpu.AL, 0xFF ^ 0xFF);
}

TEST_F(I8086_XOR_IM_Fixture, XOR_AL_Ib_Test5) {
    TestAccumulatorWithImmediateData<BYTE>(0xFF, 0x00, XOR_AL_Ib, 4);
    EXPECT_EQ(cpu.AL, 0xFF ^ 0x00);
}

TEST_F(I8086_XOR_IM_Fixture, XOR_AL_Iv_Test1) {
    TestAccumulatorWithImmediateData<WORD>(0x1111, 0x2222, XOR_AX_Iv, 4);
    EXPECT_EQ(cpu.AX, 0x1111 ^ 0x2222);
}

TEST_F(I8086_XOR_IM_Fixture, XOR_AL_Iv_Test2) {
    TestAccumulatorWithImmediateData<WORD>(0x1010, 0x0101, XOR_AX_Iv, 4);
    EXPECT_EQ(cpu.AX, 0x1010 ^ 0x0101);
}

TEST_F(I8086_XOR_IM_Fixture, XOR_AL_Iv_Test3) {
    TestAccumulatorWithImmediateData<WORD>(0x0000, 0x0000, XOR_AX_Iv, 4);
    EXPECT_EQ(cpu.AX, 0x0000 ^ 0x0000);
}

TEST_F(I8086_XOR_IM_Fixture, XOR_AL_Iv_Test4) {
    TestAccumulatorWithImmediateData<WORD>(0xFFFF, 0xFFFF, XOR_AX_Iv, 4);
    EXPECT_EQ(cpu.AX, 0xFFFF ^ 0xFFFF);
}

TEST_F(I8086_XOR_IM_Fixture, XOR_AL_Iv_Test5) {
    TestAccumulatorWithImmediateData<WORD>(0xFFFF, 0x0000, XOR_AX_Iv, 4);
    EXPECT_EQ(cpu.AX, 0xFFFF ^ 0x0000);
}
