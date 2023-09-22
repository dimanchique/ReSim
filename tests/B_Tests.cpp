#include "CPU6502_B_Tests.h"

void CPU6502_BFixture::B_REL_CanBranch(CPU6502_OpCodes OpCode, BYTE TargetStatusFlag, bool FlagValue){
    // given:
    cpu.Status.SetStatusFlagValue(TargetStatusFlag, FlagValue);
    mem[0xFFFC] = OpCode;
    mem[0xFFFD] = -10;
    mem[0xFFFD - 10 + 1] = CPU6502_OpCodes::LDA_IM;
    mem[0xFFFD - 10 + 2] = 0x15;

    CyclesExpected = 2 + 1 + 2;

    // when:
    CyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x15);
    CheckCyclesCount();
}

void CPU6502_BFixture::B_REL_CannotBranch(CPU6502_OpCodes OpCode, BYTE TargetStatusFlag, bool FlagValue){
    // given:
    cpu.Status.SetStatusFlagValue(TargetStatusFlag, FlagValue);
    mem[0xFFFC] = OpCode;
    mem[0xFFFD] = -10;

    CyclesExpected = 2;

    // when:
    CyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.PC, 0xFFFE);
    CheckCyclesCount();
}

void CPU6502_BFixture::B_REL_CanBranch_WithPageCrossing(CPU6502_OpCodes OpCode, BYTE TargetStatusFlag, bool FlagValue){
    // given:
    cpu.Reset(0x4000, mem);
    cpu.Status.SetStatusFlagValue(TargetStatusFlag, FlagValue);
    mem[0x4000] = OpCode;
    mem[0x4001] = -10;
    mem[0x4001 - 10 + 1] = CPU6502_OpCodes::LDA_IM;
    mem[0x4001 - 10 + 2] = 0x15;

    CyclesExpected = 2 + 2 + 2;

    // when:
    CyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x15);
    CheckCyclesCount();
}
