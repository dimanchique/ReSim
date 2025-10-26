#include "I8086_DoubleOpTests.h"
#include "I8086_SingleOpTests.h"

class I8086_ADD_Fixture : public I8086_DoubleOpFixture {
};

class I8086_ADD_IM_Fixture : public I8086_SingleOpFixture {
};

// Mem (BX addressed) <-- AX + Mem (BX addressed)
TEST_F(I8086_ADD_Fixture, ADD_Ev_Gv_BX_Addressed_AX) {
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
    const WORD refValue = cpu.AX + memValue;

    TestMemRegInstruction(memAddress, memValue, ADD_Ev_Gv, modReg, 16);

    WORD result = mem[memAddress];
    result |= (mem[memAddress + 1] << 8);
    EXPECT_EQ(result, refValue);

// Test flags
    EXPECT_FALSE(cpu.Status.C); // No carry
    EXPECT_FALSE(cpu.Status.A);  // Auxiliary carry occurred
    EXPECT_FALSE(cpu.Status.O); // No overflow
    EXPECT_FALSE(cpu.Status.S);  // Not negative
    EXPECT_FALSE(cpu.Status.Z);  // Not zero
    EXPECT_TRUE(cpu.Status.P);  // Odd parity
}

// AX <-- AX + BX
TEST_F(I8086_ADD_Fixture, ADD_Gv_Ev_AX_BX) {
    cpu.AX = 0x0060;
    cpu.BX = 0x009A;
    const BYTE leftReg = wAX;
    const BYTE rightReg = wBX;
    const WORD refValue = cpu.AX + cpu.BX;

    TestRegRegInstruction<WORD>(&leftReg, &rightReg, ADD_Gv_Ev, 16);

    EXPECT_EQ(cpu.AX, refValue);

// Test flags
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8086_ADD_IM_Fixture, ADD_AL_Ib_Test1) {
    TestAccumulatorWithImmediateData<BYTE>(0x11, 0x22, ADD_AL_Ib, 4);
    EXPECT_EQ(cpu.AL, 0x11 + 0x22);

    // Test flags
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P); // 0x33 has even parity
}

TEST_F(I8086_ADD_IM_Fixture, ADD_AL_Ib_Test2_WithCarry) {
    TestAccumulatorWithImmediateData<BYTE>(0xFF, 0x01, ADD_AL_Ib, 4);
    EXPECT_EQ(cpu.AL, 0x00);

    // Test flags
    EXPECT_TRUE(cpu.Status.C); // Carry occurred
    EXPECT_TRUE(cpu.Status.A); // Auxiliary carry occurred
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z); // Zero result
    EXPECT_TRUE(cpu.Status.P); // 0x00 has even parity
}

TEST_F(I8086_ADD_IM_Fixture, ADD_AL_Ib_Test3_WithOverflow) {
    TestAccumulatorWithImmediateData<BYTE>(0x7F, 0x01, ADD_AL_Ib, 4);
    EXPECT_EQ(cpu.AL, 0x80);

    // Test flags
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_TRUE(cpu.Status.A);
    EXPECT_TRUE(cpu.Status.O); // Signed overflow occurred
    EXPECT_TRUE(cpu.Status.S); // Negative result
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

TEST_F(I8086_ADD_IM_Fixture, ADD_AX_Iv_Test1) {
    TestAccumulatorWithImmediateData<WORD>(0x1111, 0x2222, ADD_AX_Iv, 4);
    EXPECT_EQ(cpu.AX, 0x1111 + 0x2222);

    // Test flags
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8086_ADD_IM_Fixture, ADD_AX_Iv_Test2_WithCarry) {
    TestAccumulatorWithImmediateData<WORD>(0xFFFF, 0x0001, ADD_AX_Iv, 4);
    EXPECT_EQ(cpu.AX, 0x0000);

    // Test flags
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_TRUE(cpu.Status.A);
    EXPECT_FALSE(cpu.Status.O);
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.P);
}

TEST_F(I8086_ADD_IM_Fixture, ADD_AX_Iv_Test3_WithOverflow) {
    TestAccumulatorWithImmediateData<WORD>(0x7FFF, 0x0001, ADD_AX_Iv, 4);
    EXPECT_EQ(cpu.AX, 0x8000);

    // Test flags
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_TRUE(cpu.Status.A);
    EXPECT_TRUE(cpu.Status.O);
    EXPECT_TRUE(cpu.Status.S);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.P);
}

// Test with different addressing modes
TEST_F(I8086_ADD_Fixture, ADD_Ev_Gv_BP_Addressed_WithDisp_DX) {
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
    const WORD refValue = cpu.DX + memValue;

    TestMemRegInstruction(memAddress, memValue, ADD_Ev_Gv, modReg, 16);

    WORD result = mem[memAddress];
    result |= (mem[memAddress + 1] << 8);
    EXPECT_EQ(result, refValue);
}

// Test byte operations
TEST_F(I8086_ADD_Fixture, ADD_Gb_Eb_AL_BH) {
    cpu.AL = 0x60;
    cpu.BH = 0x9A;
    const BYTE leftReg = bAL;
    const BYTE rightReg = bBH;
    const BYTE refValue = cpu.AL + cpu.BH;

    TestRegRegInstruction<BYTE>(&leftReg, &rightReg, ADD_Gb_Eb, 16);

    EXPECT_EQ(cpu.AL, refValue);
}

// Test zero result
TEST_F(I8086_ADD_IM_Fixture, ADD_AL_Ib_ZeroResult) {
    TestAccumulatorWithImmediateData<BYTE>(0x00, 0x00, ADD_AL_Ib, 4);
    EXPECT_EQ(cpu.AL, 0x00);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.S);
    EXPECT_TRUE(cpu.Status.P);
}
