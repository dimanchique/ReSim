#include "I8080_TestingSuite.h"

class I8080_JUMPFixture : public I8080_TestFixture {};

TEST_F(I8080_JUMPFixture, JMP_CanJump) {
    // given:
    mem[0x0000] = JMP;
    mem[0x0001] = 0x3C;
    mem[0x0002] = 0x00;
    mem[0x003C] = RET;

    cyclesExpected = 10;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.PC, 0x003C);
    CheckCyclesCount();
}

TEST_F(I8080_JUMPFixture, JMP_CanJumpMultipleTimes) {
    // given:
    mem[0x0000] = JMP;
    mem[0x0001] = 0x3C;
    mem[0x0002] = 0x00;
    mem[0x0400] = RET;
    mem[0x003C] = JMP;
    mem[0x003D] = 0x00;
    mem[0x003E] = 0x04;

    cyclesExpected = 10 + 10;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.PC, 0x0400);
    CheckCyclesCount();
}
