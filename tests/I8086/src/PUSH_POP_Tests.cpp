#include "I8086_TestingSuite.h"
#include "I8086_GroupTests.h"
#include "I8086_SingleOpTests.h"
#include "I8086_ImpliedOpTests.h"
#include "I8086_OpCodes_Groups.h"

class I8086_PUSH_POP_Fixture : public I8086_TestFixture {};

TEST_F(I8086_PUSH_POP_Fixture, PUSH_AX_BX_CX_DX_POP_AX_BX_CX_DX) {
    // given:
    const WORD value_1 = 0xDEAD;
    const WORD value_2 = 0xBEEF;
    const WORD value_3 = 0xCAFE;
    const WORD value_4 = 0xBABE;
    cpu.AX = value_1;
    cpu.BX = value_2;
    cpu.CX = value_3;
    cpu.DX = value_4;
    cpu.SP = 0x6000;

    mem[effectiveAddress++] = PUSH_AX;
    mem[effectiveAddress++] = PUSH_BX;
    mem[effectiveAddress++] = PUSH_CX;
    mem[effectiveAddress++] = PUSH_DX;
    mem[effectiveAddress++] = POP_AX;
    mem[effectiveAddress++] = POP_BX;
    mem[effectiveAddress++] = POP_CX;
    mem[effectiveAddress++] = POP_DX;
    mem[effectiveAddress] = I8086_STOP_OPCODE;

    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.AX, value_4);
    EXPECT_EQ(cpu.BX, value_3);
    EXPECT_EQ(cpu.CX, value_2);
    EXPECT_EQ(cpu.DX, value_1);
}

TEST_F(I8086_PUSH_POP_Fixture, PUSH_ES_SS_DS_POP_ES_SS_DS) {
    // given:
    const WORD value_1 = 0xDEAD;
    const WORD value_2 = 0xBEEF;
    const WORD value_3 = 0xCAFE;
    cpu.ES = value_1;
    cpu.SS = value_2;
    cpu.DS = value_3;
    cpu.SP = 0x6000;

    mem[effectiveAddress++] = PUSH_ES;
    mem[effectiveAddress++] = PUSH_SS;
    mem[effectiveAddress++] = PUSH_DS;
    mem[effectiveAddress++] = PUSH_CS;
    mem[effectiveAddress++] = POP_ES;
    mem[effectiveAddress++] = POP_SS;
    mem[effectiveAddress++] = POP_DS;
    mem[0x5FFC + (0xCAFE << 4)] = 0x0B;
    mem[0x5FFD + (0xCAFE << 4)] = 0xB0;
    mem[effectiveAddress] = I8086_STOP_OPCODE;

    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.ES, cpu.CS);
    EXPECT_EQ(cpu.SS, value_3);
    EXPECT_EQ(cpu.DS, 0xB00B);
}

class I8086_PUSH_Ev_Fixture : public I8086_GroupFixture {};

TEST_F(I8086_PUSH_Ev_Fixture, PUSH_Ev) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 0;
    modReg.leftOp.memData.mode = modeBX;

    cpu.Status.C = 0;
    cpu.AX = 0x0060;
    cpu.BX = 0x009A;
    cpu.DS = 0x4000;
    cpu.SP = 0x6000;
    cyclesExpected = 16 + 5;

    const WORD memValue = 0b00000000'01010101;
    const DWORD memAddress = cpu.BX + (cpu.DS << 4);

    TestMemoryInstruction(memAddress, memValue, GRP5_Ev, modReg, GRP5_PUSH, 16);

    WORD result = cpu.PopDataFromStack();
    EXPECT_EQ(result, memValue);
}

class I8086_POP_Ev_Fixture : public I8086_SingleOpFixture {};

TEST_F(I8086_POP_Ev_Fixture, POP_Ev) {
    ModRegByteConstructor modReg;

    modReg.leftOp.archetype = OperandArchetype::Mem;
    modReg.leftOp.memData.dispSize = 0;
    modReg.leftOp.memData.mode = modeBX;

    cpu.Status.C = 0;
    cpu.AX = 0x0060;
    cpu.BX = 0x009A;
    cpu.DS = 0x4000;
    cpu.SP = 0x6000;
    cyclesExpected = 16 + 5;

    const WORD memValue = 0xCCDA;

    cpu.PushDataToStack(memValue);
    TestImpliedInstruction(POP_Ev, modReg, 16);

    DWORD newStackAddress = EFFECTIVE_ADDRESS(cpu.SP, cpu.SS);
    WORD result = mem[newStackAddress - 2];
    result |= (mem[newStackAddress - 1] << 8);
    EXPECT_EQ(result, memValue);
}

class I8086_PUSH_POP_F_Fixture : public I8086_ImpliedOpFixture {};

TEST_F(I8086_PUSH_POP_F_Fixture, PushPopFlag) {
    // given:
    const WORD regValue = 0xDADA;
    const WORD statusValue = 0xBEBE;

    cpu.ES = regValue;
    cpu.Status.Value = statusValue;
    cpu.SP = 0x6000;

    mem[effectiveAddress++] = PUSH_ES;
    mem[effectiveAddress++] = PUSHF;
    mem[effectiveAddress++] = POP_ES;
    mem[effectiveAddress++] = POPF;
    mem[effectiveAddress] = I8086_STOP_OPCODE;

    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.ES, statusValue);
    EXPECT_EQ(cpu.Status.Value, regValue);
}
