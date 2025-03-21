#include "I8086_GroupTests.h"

class I8086_ROL_RCL_SAL_SHL_Fixture : public I8086_GroupFixture {};

TEST_F(I8086_ROL_RCL_SAL_SHL_Fixture, ROL_1_BX_Addressed_Mem) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 0;
    modReg.leftOp.memData.mode = modeBX;

    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.AX = 0x0060;
    cpu.BX = 0x009A;
    cpu.DS = 0x4000;
    cyclesExpected = 16 + 5;

    const BYTE memValue = 0b01010101;
    const DWORD memAddress = cpu.BX + (cpu.DS << 4);
    const BYTE refValue = 0b10101010;

    TestMemoryInstruction(memAddress, memValue, GRP2_Eb_1, modReg, GRP2_ROL, 16);

    WORD result = mem[memAddress];
    EXPECT_EQ(result, refValue);

    EXPECT_EQ(cpu.Status.C, 0);
    EXPECT_EQ(cpu.Status.O, 1);
}

TEST_F(I8086_ROL_RCL_SAL_SHL_Fixture, ROL_1_BH_Reg) {
    const BYTE reg = bBH;
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.BH = 0b01010101;
    const BYTE refValue = 0b10101010;

    TestRegisterInstruction(&cpu.BH, refValue, GRP2_Eb_1, &reg, GRP2_ROL, 16);
    EXPECT_EQ(cpu.Status.C, 0);
    EXPECT_EQ(cpu.Status.O, 1);
}

TEST_F(I8086_ROL_RCL_SAL_SHL_Fixture, ROL_1_AH_Reg) {
    const BYTE reg = bAH;
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.AH = 0b10000000;
    const BYTE refValue = 0b00000001;

    TestRegisterInstruction(&cpu.AH, refValue, GRP2_Eb_1, &reg, GRP2_ROL, 16);
    EXPECT_EQ(cpu.Status.C, 1);
    EXPECT_EQ(cpu.Status.O, 1);
}

TEST_F(I8086_ROL_RCL_SAL_SHL_Fixture, ROL_CL_AX_Reg) {
    const BYTE reg = wAX;
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.AX = 0b00000000'00000001;
    cpu.CL = 0x0F;
    const WORD refValue = 0b10000000'00000000;

    TestRegisterInstruction(&cpu.AX, refValue, GRP2_Ev_CL, &reg, GRP2_ROL, 16);
    EXPECT_EQ(cpu.Status.C, 0);
    EXPECT_EQ(cpu.Status.O, 0);
}

TEST_F(I8086_ROL_RCL_SAL_SHL_Fixture, RCL_1_AL_Reg) {
    const BYTE reg = bAL;
    cpu.Status.C = 1;
    cpu.Status.O = 0;
    cpu.AL = 0b00000000;
    const BYTE refValue = 0b00000001;

    TestRegisterInstruction(&cpu.AL, refValue, GRP2_Eb_1, &reg, GRP2_RCL, 16);
    EXPECT_EQ(cpu.Status.C, 0);
    EXPECT_EQ(cpu.Status.O, 1);
}

TEST_F(I8086_ROL_RCL_SAL_SHL_Fixture, RCL_1_BH_Reg) {
    const BYTE reg = bBH;
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.BH = 0b00101010;
    const BYTE refValue = 0b01010100;

    TestRegisterInstruction(&cpu.BH, refValue, GRP2_Eb_1, &reg, GRP2_RCL, 16);
    EXPECT_EQ(cpu.Status.C, 0);
    EXPECT_EQ(cpu.Status.O, 0);
}

TEST_F(I8086_ROL_RCL_SAL_SHL_Fixture, RCL_CL_DX_Reg) {
    const BYTE reg = wDX;
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.DX = 0b00101010;
    cpu.CL = 0x10;
    const WORD refValue = 0b00010101;

    TestRegisterInstruction(&cpu.DX, refValue, GRP2_Ev_CL, &reg, GRP2_RCL, 16);
    EXPECT_EQ(cpu.Status.C, 0);
    EXPECT_EQ(cpu.Status.O, 0);
}

TEST_F(I8086_ROL_RCL_SAL_SHL_Fixture, SAL_SHL_1_BL_Reg) {
    const BYTE reg = bBL;
    cpu.Status.C = 1;
    cpu.Status.O = 0;
    cpu.BL = 0b00000001;
    const BYTE refValue = 0b00000010;

    TestRegisterInstruction(&cpu.BL, refValue, GRP2_Eb_1, &reg, GRP2_SHL, 16);
    EXPECT_EQ(cpu.Status.C, 0);
    EXPECT_EQ(cpu.Status.O, 0);
}

TEST_F(I8086_ROL_RCL_SAL_SHL_Fixture, SAL_SHL_1_CL_Reg) {
    const BYTE reg = bCL;
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.CL = 0b00101010;
    const BYTE refValue = 0b01010100;

    TestRegisterInstruction(&cpu.CL, refValue, GRP2_Eb_1, &reg, GRP2_SHL, 16);
    EXPECT_EQ(cpu.Status.C, 0);
    EXPECT_EQ(cpu.Status.O, 0);
}

TEST_F(I8086_ROL_RCL_SAL_SHL_Fixture, SAL_SHL_CL_AX_Reg) {
    const BYTE reg = wAX;
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.AX = 0b00000000'00101010;
    cpu.CL = 0x08;
    const WORD refValue = 0b00101010'00000000;

    TestRegisterInstruction(&cpu.AX, refValue, GRP2_Ev_CL, &reg, GRP2_SHL, 16);
    EXPECT_EQ(cpu.Status.C, 0);
    EXPECT_EQ(cpu.Status.O, 0);
}
