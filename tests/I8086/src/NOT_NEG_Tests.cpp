#include "I8086_GroupTests.h"
#include "I8086_OpCodes_Groups.h"

class I8086_NOT_NEG_Fixture : public I8086_GroupFixture {};

TEST_F(I8086_NOT_NEG_Fixture, NOT_BX_Addressed_Mem) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 0;
    modReg.leftOp.memData.mode = modeBX;

    cpu.Status.C = 0;
    cpu.AX = 0x0060;
    cpu.BX = 0x009A;
    cpu.DS = 0x4000;
    cyclesExpected = 16 + 5;

    const BYTE memValue = 0b01010101;
    const DWORD memAddress = cpu.BX + (cpu.DS << 4);
    const BYTE refValue = 0b10101010;

    TestMemoryInstruction(memAddress, memValue, GRP3a_Eb, modReg, GRP3a_NOT, 16);

    WORD result = mem[memAddress];
    EXPECT_EQ(result, refValue);
    EXPECT_EQ(cpu.Status.C, 0);
}

TEST_F(I8086_NOT_NEG_Fixture, NEG_BX_Addressed_Mem) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 0;
    modReg.leftOp.memData.mode = modeBX;

    cpu.Status.C = 0;
    cpu.AX = 0x0060;
    cpu.BX = 0x009A;
    cpu.DS = 0x4000;
    cyclesExpected = 16 + 5;

    const WORD memValue = 0b01010101'01010101;
    const DWORD memAddress = cpu.BX + (cpu.DS << 4);
    const WORD refValue = 0b10101010'10101011;

    TestMemoryInstruction(memAddress, memValue, GRP3b_Ev, modReg, GRP3b_NEG, 16);

    WORD result = mem[memAddress];
    result |= (mem[memAddress + 1] << 8);
    EXPECT_EQ(result, refValue);
    EXPECT_EQ(cpu.Status.C, 1);
}

TEST_F(I8086_NOT_NEG_Fixture, NOT_BH_Reg) {
    const BYTE reg = bBH;
    cpu.Status.C = 0;
    cpu.BH = 0b00000000;
    const BYTE refValue = 0b11111111;

    TestRegisterInstruction(&cpu.BH, refValue, GRP3a_Eb, &reg, GRP3a_NOT, 16);
    EXPECT_EQ(cpu.Status.C, 0);
}

TEST_F(I8086_NOT_NEG_Fixture, NEG_CX_Reg) {
    const BYTE reg = wCX;
    cpu.Status.C = 0;
    cpu.CX = 0b11001100'11001100;
    const WORD refValue = 0b00110011'00110100;

    TestRegisterInstruction(&cpu.CX, refValue, GRP3b_Ev, &reg, GRP3b_NEG, 16);
    EXPECT_EQ(cpu.Status.C, 1);
}
