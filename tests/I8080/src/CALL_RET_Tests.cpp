#include "I8080_TestingSuite.h"

class I8080_CALL_RETFixture : public I8080_TestFixture {};

TEST_F(I8080_CALL_RETFixture, CALL_CanCallAndReturn) {
    // given:
    mem[0x0000] = I8080_OpCodes::CALL;
    mem[0x0001] = 0x3C;
    mem[0x0002] = 0x00;
    mem[0x3C00] = I8080_OpCodes::RET;

    cyclesExpected = 17 + 10;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.PC, 0x0003);
    CheckCyclesCount();
}

TEST_F(I8080_CALL_RETFixture, CALL_CanCallAndReturnMultipleTimes) {
    // given:
    mem[0x0000] = I8080_OpCodes::CALL;
    mem[0x0001] = 0x3C;
    mem[0x0002] = 0x00;
    mem[0x1004] = I8080_OpCodes::RET;
    mem[0x3C00] = I8080_OpCodes::CALL;
    mem[0x3C01] = 0x10;
    mem[0x3C02] = 0x04;
    mem[0x3C03] = I8080_OpCodes::RET;

    cyclesExpected = 17 + 10 + 17 + 10;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.PC, 0x0003);
    CheckCyclesCount();
}

TEST_F(I8080_CALL_RETFixture, CALL_CanCallAndReturnMultipleTimesInARow) {
    // given:
    mem[0x0000] = I8080_OpCodes::CALL;
    mem[0x0001] = 0x3C;
    mem[0x0002] = 0x00;
    mem[0x0003] = I8080_OpCodes::CALL;
    mem[0x0004] = 0x10;
    mem[0x0005] = 0x04;
    mem[0x1004] = I8080_OpCodes::RET;
    mem[0x3C00] = I8080_OpCodes::RET;

    cyclesExpected = 17 + 10 + 17 + 10;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.PC, 0x0006);
    CheckCyclesCount();
}
