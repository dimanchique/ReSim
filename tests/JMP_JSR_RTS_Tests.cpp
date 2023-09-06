#include "CPU6502_TestingSuite.h"

class CPU6502_JSRFixture : public CPU6502_TestFixture{};

TEST_F(CPU6502_JSRFixture, JSR_ABS_CanJump) {
    // given:
    mem[0xFFFC] = CPU6502_OpCodes::JSR_ABS;
    mem[0xFFFD] = 0x42;
    mem[0xFFFE] = 0x42;

    const U32 NumCycles = 6;

    // when:
    U32 CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(cpu.PC, 0x4242);
    EXPECT_EQ(CNT, NumCycles);
}

TEST_F(CPU6502_JSRFixture, JSR_ABS_CanExecuteNextOpCode) {
    // given:
    mem[0xFFFC] = CPU6502_OpCodes::JSR_ABS;
    mem[0xFFFD] = 0x42;
    mem[0xFFFE] = 0x42;
    mem[0x4242] = CPU6502_OpCodes::LDA_IM;
    mem[0x4243] = 0x84;

    const U32 NumCycles = 6 + 2;

    // when:
    U32 CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(cpu.A, 0x84);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);                             // 0x84 is 0b10000100 and N is checking the 7's bit in A and it's 1
    EXPECT_EQ(CNT, NumCycles);
}

class CPU6502_JSR_RTSFixture : public CPU6502_TestFixture{};

TEST_F(CPU6502_JSR_RTSFixture, JSR_ABS_RTS_IMPL_CanJumpToSubroutineAndJumpBack) {
    // given:
    cpu.Reset(0xFF00, mem);
    mem[0xFF00] = CPU6502_OpCodes::JSR_ABS;         // 6 cycles
    mem[0xFF01] = 0x00;
    mem[0xFF02] = 0x80;
    mem[0x8000] = CPU6502_OpCodes::RTS_IMPL;        // 6 cycles
    mem[0xFF03] = CPU6502_OpCodes::LDA_IM;          // 2 cycles
    mem[0xFF04] = 0x42;

    const U32 NumCycles = 6 + 6 + 2;

    // when:
    U32 CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(cpu.A, 0x42);
    EXPECT_EQ(CNT, NumCycles);
}

TEST_F(CPU6502_JSR_RTSFixture, JSR_ABS_RTS_IMPL_CanJumpMultipleTimesInARow) {
    // given:
    cpu.Reset(0xFF00, mem);
    mem[0xFF00] = CPU6502_OpCodes::JSR_ABS;         // 6 cycles
    mem[0xFF01] = 0x00;
    mem[0xFF02] = 0x80;
    mem[0x8000] = CPU6502_OpCodes::RTS_IMPL;        // 6 cycles
    mem[0xFF03] = CPU6502_OpCodes::JSR_ABS;         // 6 cycles
    mem[0xFF04] = 0x00;
    mem[0xFF05] = 0x42;
    mem[0x4200] = CPU6502_OpCodes::RTS_IMPL;        // 6 cycles
    mem[0xFF06] = CPU6502_OpCodes::LDA_IM;          // 2 cycles
    mem[0xFF07] = 0x42;

    const U32 NumCycles = 6 + 6 + 6 + 6 + 2;

    // when:
    U32 CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(cpu.A, 0x42);
    EXPECT_EQ(CNT, NumCycles);
}

TEST_F(CPU6502_JSR_RTSFixture, JSR_ABS_RTS_IMPL_CanDoJumpInsideJump) {
    // given:
    cpu.Reset(0xFF00, mem);
    mem[0xFF00] = CPU6502_OpCodes::JSR_ABS;         // 6 cycles
    mem[0xFF01] = 0x00;
    mem[0xFF02] = 0x80;
    mem[0x8000] = CPU6502_OpCodes::JSR_ABS;         // 6 cycles
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x42;
    mem[0x4200] = CPU6502_OpCodes::RTS_IMPL;        // 6 cycles
    mem[0x8003] = CPU6502_OpCodes::RTS_IMPL;        // 6 cycles
    mem[0xFF03] = CPU6502_OpCodes::LDA_IM;          // 2 cycles
    mem[0xFF04] = 0x42;

    const U32 NumCycles = 6 + 6 + 6 + 6 + 2;

    // when:
    U32 CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(cpu.A, 0x42);
    EXPECT_EQ(CNT, NumCycles);
}