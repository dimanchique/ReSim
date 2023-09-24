#include "CPU6502_TestingSuite.h"

class CPU6502_JSRFixture : public CPU6502_TestFixture{};

TEST_F(CPU6502_JSRFixture, JSR_ABS_CanJump) {
    // given:
    mem[0xFFFC] = CPU6502_OpCodes::JSR_ABS;
    mem[0xFFFD] = 0x42;
    mem[0xFFFE] = 0x42;

    cyclesExpected = 6;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.PC, 0x4242);
    CheckCyclesCount();
}

TEST_F(CPU6502_JSRFixture, JSR_ABS_CanExecuteNextOpCode) {
    // given:
    mem[0xFFFC] = CPU6502_OpCodes::JSR_ABS;
    mem[0xFFFD] = 0x42;
    mem[0xFFFE] = 0x42;
    mem[0x4242] = CPU6502_OpCodes::LDA_IM;
    mem[0x4243] = 0x84;

    cyclesExpected = 6 + 2;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x84);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);                             // 0x84 is 0b10000100 and N is checking the 7's bit in A and it's 1
    CheckCyclesCount();
}

class CPU6502_JSR_RTSFixture : public CPU6502_TestFixture{};

TEST_F(CPU6502_JSR_RTSFixture, JSR_ABS_RTS_IMPL_CanJumpToSubroutineAndJumpBack) {
    // given:
    cpu.Reset(mem, 0xFF00);
    mem[0xFF00] = CPU6502_OpCodes::JSR_ABS;         // 6 cycles
    mem[0xFF01] = 0x00;
    mem[0xFF02] = 0x80;
    mem[0x8000] = CPU6502_OpCodes::RTS_IMPL;        // 6 cycles
    mem[0xFF03] = CPU6502_OpCodes::LDA_IM;          // 2 cycles
    mem[0xFF04] = 0x42;

    cyclesExpected = 6 + 6 + 2;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x42);
    CheckCyclesCount();
}

TEST_F(CPU6502_JSR_RTSFixture, JSR_ABS_RTS_IMPL_CanJumpMultipleTimesInARow) {
    // given:
    cpu.Reset(mem, 0xFF00);
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

    cyclesExpected = 6 + 6 + 6 + 6 + 2;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x42);
    CheckCyclesCount();
}

TEST_F(CPU6502_JSR_RTSFixture, JSR_ABS_RTS_IMPL_CanDoJumpInsideJump) {
    // given:
    cpu.Reset(mem, 0xFF00);
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

    cyclesExpected = 6 + 6 + 6 + 6 + 2;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x42);
    CheckCyclesCount();
}

class CPU6502_JMPFixture : public CPU6502_TestFixture{};

TEST_F(CPU6502_JMPFixture, JMP_ABS_CanJump) {
    // given:
    mem[0xFFFC] = CPU6502_OpCodes::JMP_ABS;
    mem[0xFFFD] = 0x42;
    mem[0xFFFE] = 0x42;

    cyclesExpected = 3;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.PC, 0x4242);
    CheckCyclesCount();
}

TEST_F(CPU6502_JMPFixture, JMP_ABS_CanJumpMultipleTimesInARow) {
    // given:
    cpu.Reset(mem, 0xFF00);
    mem[0xFF00] = CPU6502_OpCodes::JMP_ABS;        // 3 cycles
    mem[0xFF01] = 0x00;
    mem[0xFF02] = 0x80;
    mem[0x8000] = CPU6502_OpCodes::JMP_ABS;        // 3 cycles
    mem[0x8001] = 0x03;
    mem[0x8002] = 0xFF;

    cyclesExpected = 3 + 3;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.PC, 0xFF03);
    CheckCyclesCount();
}

TEST_F(CPU6502_JMPFixture, JMP_IND_CanJump) {
    // given:
    cpu.Reset(mem, 0xFF00);
    mem[0xFF00] = CPU6502_OpCodes::JMP_IND;        // 5 cycles
    mem[0xFF01] = 0x00;
    mem[0xFF02] = 0x80;
    mem[0x8000] = 0x03;
    mem[0x8001] = 0xFF;

    cyclesExpected = 5;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.PC, 0xFF03);
    CheckCyclesCount();
}

TEST_F(CPU6502_JMPFixture, BRK_IND_CanGoToInterruptAndGoBack) {
    // given:
    cpu.Reset(mem, 0xFF00);
    mem[0xFFFE] = 0x00;
    mem[0xFFFF] = 0x80;
    mem[0xFF00] = CPU6502_OpCodes::BRK_IMPL;
    mem[0xFF01] = CPU6502_OpCodes::LDA_IM;
    mem[0xFF02] = 0x80;
    mem[0x8000] = CPU6502_OpCodes::RTI_IMPL;

    cyclesExpected = 7 + 2 + 6;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x80);
    CheckCyclesCount();
}