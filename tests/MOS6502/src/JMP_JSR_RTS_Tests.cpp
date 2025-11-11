#include "MOS6502_TestingSuite.h"

class MOS6502_JSRFixture : public MOS6502_TestFixture {};

TEST_F(MOS6502_JSRFixture, JSR_ABS_CanJump) {
    // given:
    mem[effectiveAddress++] = JSR_ABS;
    mem[effectiveAddress++] = 0x42;
    mem[effectiveAddress++] = 0x42;
    mem[0x4242] = RTS_IMPL;
    mem[effectiveAddress++] = RTS_IMPL;

    cyclesExpected = 12;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.PC, 0xFF03);
    CheckCyclesCount();
}

TEST_F(MOS6502_JSRFixture, JSR_ABS_CanExecuteNextOpCode) {
    // given:
    mem[effectiveAddress++] = JSR_ABS;
    mem[effectiveAddress++] = 0x42;
    mem[effectiveAddress++] = 0x42;
    mem[0x4242] = LDA_IM;
    mem[0x4243] = 0x84;
    mem[0x4244] = RTS_IMPL;
    mem[effectiveAddress++] = RTS_IMPL;

    cyclesExpected = 6 + 6 + 2;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.A, 0x84);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
    CheckCyclesCount();
}

class MOS6502_JSR_RTSFixture : public MOS6502_TestFixture {
};

TEST_F(MOS6502_JSR_RTSFixture, JSR_ABS_RTS_IMPL_CanJumpToSubroutineAndJumpBack) {
    // given:
    mem[effectiveAddress++] = JSR_ABS;          // 6 cycles
    mem[effectiveAddress++] = 0x00;
    mem[effectiveAddress++] = 0x80;
    mem[0x8000] = RTS_IMPL;                     // 6 cycles
    mem[effectiveAddress++] = LDA_IM;           // 2 cycles
    mem[effectiveAddress++] = 0x42;
    mem[effectiveAddress++] = RTS_IMPL;

    cyclesExpected = 6 + 6 + 2;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.A, 0x42);
    CheckCyclesCount();
}

TEST_F(MOS6502_JSR_RTSFixture, JSR_ABS_RTS_IMPL_CanJumpMultipleTimesInARow) {
    // given:
    mem[effectiveAddress++] = JSR_ABS;          // 6 cycles
    mem[effectiveAddress++] = 0x00;
    mem[effectiveAddress++] = 0x80;
    mem[0x8000] = RTS_IMPL;                     // 6 cycles
    mem[effectiveAddress++] = JSR_ABS;          // 6 cycles
    mem[effectiveAddress++] = 0x00;
    mem[effectiveAddress++] = 0x42;
    mem[0x4200] = RTS_IMPL;                     // 6 cycles
    mem[effectiveAddress++] = LDA_IM;           // 2 cycles
    mem[effectiveAddress++] = 0x42;
    mem[effectiveAddress++] = RTS_IMPL;

    cyclesExpected = 6 + 6 + 6 + 6 + 2;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.A, 0x42);
    CheckCyclesCount();
}

TEST_F(MOS6502_JSR_RTSFixture, JSR_ABS_RTS_IMPL_CanDoJumpInsideJump) {
    // given:
    mem[effectiveAddress++] = JSR_ABS;          // 6 cycles
    mem[effectiveAddress++] = 0x00;
    mem[effectiveAddress++] = 0x80;
    mem[0x8000] = JSR_ABS;                      // 6 cycles
    mem[0x8001] = 0x00;
    mem[0x8002] = 0x42;
    mem[0x4200] = RTS_IMPL;                     // 6 cycles
    mem[0x8003] = RTS_IMPL;                     // 6 cycles
    mem[effectiveAddress++] = LDA_IM;           // 2 cycles
    mem[effectiveAddress++] = 0x42;
    mem[effectiveAddress++] = RTS_IMPL;

    cyclesExpected = 6 + 6 + 6 + 6 + 2;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.A, 0x42);
    CheckCyclesCount();
}

class MOS6502_JMPFixture : public MOS6502_TestFixture {
};

TEST_F(MOS6502_JMPFixture, JMP_ABS_CanJump) {
    // given:
    mem[effectiveAddress++] = JMP_ABS;
    mem[effectiveAddress++] = 0x42;
    mem[effectiveAddress++] = 0x42;
    mem[0x4242] = RTS_IMPL;

    cyclesExpected = 3;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.PC, 0x4242);
    CheckCyclesCount();
}

TEST_F(MOS6502_JMPFixture, JMP_ABS_CanJumpMultipleTimesInARow) {
    // given:
    mem[effectiveAddress++] = JMP_ABS;          // 3 cycles
    mem[effectiveAddress++] = 0x00;
    mem[effectiveAddress++] = 0x80;
    mem[0x8000] = JMP_ABS;                      // 3 cycles
    mem[0x8001] = 0x03;
    mem[0x8002] = 0xFF;
    mem[effectiveAddress++] = RTS_IMPL;

    cyclesExpected = 3 + 3;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.PC, 0xFF03);
    CheckCyclesCount();
}

TEST_F(MOS6502_JMPFixture, JMP_IND_CanJump) {
    // given:
    mem[effectiveAddress++] = JMP_IND;          // 5 cycles
    mem[effectiveAddress++] = 0x00;
    mem[effectiveAddress++] = 0x80;
    mem[0x8000] = 0x03;
    mem[0x8001] = 0xFF;
    mem[effectiveAddress++] = RTS_IMPL;

    cyclesExpected = 5;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.PC, 0xFF03);
    CheckCyclesCount();
}

TEST_F(MOS6502_JMPFixture, BRK_IND_CanGoToInterruptAndGoBack) {
    // given:
    mem[0xFFFE] = 0x00; // Set interrupt vector
    mem[0xFFFF] = 0x80;
    mem[effectiveAddress++] = BRK_IMPL;
    mem[effectiveAddress++] = LDA_IM;
    mem[effectiveAddress++] = 0x80;
    mem[effectiveAddress++] = RTS_IMPL;
    mem[0x8000] = RTI_IMPL;

    cyclesExpected = 7 + 2 + 6;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.A, 0x80);
    CheckCyclesCount();
}
