#include "MOS6502_B_Tests.h"

void MOS6502_BFixture::B_REL_CanBranch(MOS6502_OpCodes_Main opcode, BYTE targetStatusFlag, bool flagValue) {
    // given:
    SetStatusBitByMask(targetStatusFlag, flagValue);
    mem[0xFFFC] = 0x40;
    mem[0xFFFD] = 0x40;
    mem[0x4040] = opcode;
    mem[0x4041] = -10;
    mem[0x4041 - 10 + 1] = LDA_IM;
    mem[0x4041 - 10 + 2] = 0x15;
    mem[0x4041 - 10 + 3] = RTS_IMPL;

    cyclesExpected = 2 + 1 + 2;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.A, 0x15);
    CheckCyclesCount();
}

void MOS6502_BFixture::B_REL_CannotBranch(MOS6502_OpCodes_Main opcode, BYTE targetStatusFlag, bool flagValue) {
    // given:
    SetStatusBitByMask(targetStatusFlag, flagValue);
    mem[effectiveAddress++] = opcode;
    mem[effectiveAddress++] = -10;
    mem[effectiveAddress++] = RTS_IMPL;

    cyclesExpected = 2;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.PC, effectiveAddress - 1);
    CheckCyclesCount();
}

void MOS6502_BFixture::B_REL_CanBranch_WithPageCrossing(MOS6502_OpCodes_Main opcode, BYTE targetStatusFlag, bool flagValue) {
    // given:
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x40;
    SetStatusBitByMask(targetStatusFlag, flagValue);
    mem[0x4000] = opcode;
    mem[0x4001] = -10;
    mem[0x4001 - 10 + 1] = LDA_IM;
    mem[0x4001 - 10 + 2] = 0x15;
    mem[0x4001 - 10 + 3] = RTS_IMPL;

    cyclesExpected = 2 + 2 + 2;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.A, 0x15);
    CheckCyclesCount();
}
