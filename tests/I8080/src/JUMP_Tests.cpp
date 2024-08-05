#include "I8080_TestingSuite.h"

class I8080_JUMPFixture : public I8080_TestFixture {};

TEST_F(I8080_JUMPFixture, JMP_CanJump) {
    // given:
    mem[0x0000] = JMP;
    mem[0x0001] = 0x3C;
    mem[0x0002] = 0x00;
    mem[0x3C00] = STOP_OPCODE;

    cyclesExpected = 10;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.PC, 0x3C00);
    CheckCyclesCount();
}

TEST_F(I8080_JUMPFixture, JMP_CanJumpMultipleTimes) {
    // given:
    mem[0x0000] = JMP;
    mem[0x0001] = 0x3C;
    mem[0x0002] = 0x00;
    mem[0x0004] = STOP_OPCODE;
    mem[0x3C00] = JMP;
    mem[0x3C01] = 0x00;
    mem[0x3C02] = 0x04;

    cyclesExpected = 10 + 10;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.PC, 0x0004);
    CheckCyclesCount();
}
