#include "I8080_TestingSuite.h"

class I8080_CALL_RETFixture : public I8080_TestFixture {};

TEST_F(I8080_CALL_RETFixture, CALL_CanCallAndReturn) {
    // given:
    mem[0x0000] = CALL;
    mem[0x0001] = 0x3C;
    mem[0x0002] = 0x00;
    mem[0x0003] = RET;
    mem[0x003C] = RET;

    cyclesExpected = 17 + 10;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.PC, 0x0003);
    CheckCyclesCount();
}

TEST_F(I8080_CALL_RETFixture, CALL_CanCallAndReturnMultipleTimes) {
    // given:
    mem[0x0000] = CALL;
    mem[0x0001] = 0x3C;
    mem[0x0002] = 0x00;
    mem[0x0003] = RET;
    mem[0x1004] = RET;
    mem[0x003C] = CALL;
    mem[0x003D] = 0x04;
    mem[0x003E] = 0x10;
    mem[0x003F] = RET;

    cyclesExpected = 17 + 10 + 17 + 10;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.PC, 0x0003);
    CheckCyclesCount();
}

TEST_F(I8080_CALL_RETFixture, CALL_CanCallAndReturnMultipleTimesInARow) {
    // given:
    mem[0x0000] = CALL;
    mem[0x0001] = 0x3C;
    mem[0x0002] = 0x00;
    mem[0x0003] = CALL;
    mem[0x0004] = 0x04;
    mem[0x0005] = 0x10;
    mem[0x0006] = RET;
    mem[0x1004] = RET;
    mem[0x003C] = RET;

    cyclesExpected = 17 + 10 + 17 + 10;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.PC, 0x0006);
    CheckCyclesCount();
}
