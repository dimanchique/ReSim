#include "I8086_TestingSuite.h"

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
    mem[effectiveAddress] = STOP_OPCODE;

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
    mem[effectiveAddress] = STOP_OPCODE;

    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.ES, cpu.CS);
    EXPECT_EQ(cpu.SS, value_3);
    EXPECT_EQ(cpu.DS, 0xB00B);
}
