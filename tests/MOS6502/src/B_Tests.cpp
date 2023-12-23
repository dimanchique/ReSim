#include "MOS6502_B_Tests.h"

void MOS6502_BFixture::B_REL_CanBranch(MOS6502_OpCodes opcode, BYTE targetStatusFlag, bool flagValue) {
    // given:
    cpu.Status.SetStatusFlagValue(targetStatusFlag, flagValue);
    mem[0xFFFC] = opcode;
    mem[0xFFFD] = -10;
    mem[0xFFFD - 10 + 1] = MOS6502_OpCodes::LDA_IM;
    mem[0xFFFD - 10 + 2] = 0x15;

    cyclesExpected = 2 + 1 + 2;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x15);
    CheckCyclesCount();
}

void MOS6502_BFixture::B_REL_CannotBranch(MOS6502_OpCodes opcode, BYTE targetStatusFlag, bool flagValue) {
    // given:
    cpu.Status.SetStatusFlagValue(targetStatusFlag, flagValue);
    mem[0xFFFC] = opcode;
    mem[0xFFFD] = -10;

    cyclesExpected = 2;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.PC, 0xFFFE);
    CheckCyclesCount();
}

void MOS6502_BFixture::B_REL_CanBranch_WithPageCrossing(MOS6502_OpCodes opcode, BYTE targetStatusFlag, bool flagValue) {
    // given:
    cpu.Reset(mem, 0x4000);
    cpu.Status.SetStatusFlagValue(targetStatusFlag, flagValue);
    mem[0x4000] = opcode;
    mem[0x4001] = -10;
    mem[0x4001 - 10 + 1] = MOS6502_OpCodes::LDA_IM;
    mem[0x4001 - 10 + 2] = 0x15;

    cyclesExpected = 2 + 2 + 2;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x15);
    CheckCyclesCount();
}
