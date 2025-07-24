#include "I8086_GroupTests.h"
#include "I8086_ImpliedOpTests.h"
#include "I8086_OpCodesGroups.h"

class I8086_INC_DEC_Fixture : public I8086_GroupFixture {};
class I8086_INC_DEC_Word_Fixture : public I8086_ImpliedOpTests {};

TEST_F(I8086_INC_DEC_Fixture, INC_Eb_Addressed_Mem) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 0;
    modReg.leftOp.memData.mode = modeBX;

    cpu.Status.O = 0;
    cpu.AX = 0x0060;
    cpu.BX = 0x009A;
    cpu.DS = 0x4000;
    cyclesExpected = 16 + 5;

    const BYTE memValue = 0b01010101;
    const DWORD memAddress = cpu.BX + (cpu.DS << 4);
    const BYTE refValue = 0b01010110;

    TestMemoryInstruction(memAddress, memValue, GRP4_Eb, modReg, GRP4_INC, 16);

    BYTE result = mem[memAddress];
    EXPECT_EQ(result, refValue);
}

TEST_F(I8086_INC_DEC_Fixture, INC_Eb_BH_Reg) {
    const BYTE reg = bBH;
    cpu.Status.O = 0;
    cpu.BH = 0b01010101;
    const BYTE refValue = 0b01010110;

    TestRegisterInstruction(&cpu.BH, refValue, GRP4_Eb, &reg, GRP4_INC, 16);
}

TEST_F(I8086_INC_DEC_Fixture, DEC_Eb_AH_Reg) {
    const BYTE reg = bAH;
    cpu.Status.O = 0;
    cpu.AH = 0b10000000;
    const BYTE refValue = 0b01111111;

    TestRegisterInstruction(&cpu.AH, refValue, GRP4_Eb, &reg, GRP4_DEC, 16);
}

/**
 *
 * INC/DEC Word Test Suite
 *
 */

TEST_F(I8086_INC_DEC_Word_Fixture, INC_AX) {
    cpu.Status.O = 0;
    cpu.AX = 0b11111111'11111111;
    const WORD refValue = 0b00000000'00000000;

    TestImpliedInstruction(INC_AX);
    EXPECT_EQ(cpu.AX, refValue);
    EXPECT_TRUE(cpu.Status.O);
}

TEST_F(I8086_INC_DEC_Word_Fixture, DEC_BX) {
    cpu.Status.O = 0;
    cpu.BX = 0b00000000'00000000;
    const WORD refValue = 0b11111111'11111111;

    TestImpliedInstruction(DEC_BX);
    EXPECT_EQ(cpu.BX, refValue);
    EXPECT_TRUE(cpu.Status.O);
}

TEST_F(I8086_INC_DEC_Word_Fixture, INC_SP) {
    cpu.Status.O = 0;
    cpu.SP = 0b00000000'11111111;
    const WORD refValue = 0b00000001'00000000;

    TestImpliedInstruction(INC_SP);
    EXPECT_EQ(cpu.SP, refValue);
    EXPECT_FALSE(cpu.Status.O);
}

TEST_F(I8086_INC_DEC_Word_Fixture, DEC_SI) {
    cpu.Status.O = 0;
    cpu.SI = 0b00000001'00000000;
    const WORD refValue = 0b00000000'11111111;

    TestImpliedInstruction(DEC_SI);
    EXPECT_EQ(cpu.SI, refValue);
    EXPECT_FALSE(cpu.Status.O);
}
