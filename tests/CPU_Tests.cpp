#include "CPU6502_TestingSuite.h"

class CPU6502_CPUFixture : public CPU6502_TestFixture{};

TEST_F(CPU6502_CPUFixture, CpuDoesNothingWithZerocycles) {
    // given:
    cyclesExpected = 0;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    CheckCyclesCount();
}

TEST_F(CPU6502_CPUFixture, CpuCanExecuteMorecyclesThenRequested) {
    // given:
    mem[0xFFFC] = CPU6502_OpCodes::JSR_ABS;     // This instruction takes 6 cycles
    mem[0xFFFD] = 0x42;
    mem[0xFFFE] = 0x42;

    cyclesExpected = 1;                         // We're "expecting" 1 cycle

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    CheckCyclesCount(6);                        // But there are 6 actually
}

class UtilsTests : public testing::Test{};
TEST_F(UtilsTests, PageCrossingTest) {
    EXPECT_TRUE(CPU6502::isPageCrossed(0x4001, 0x3ffe));
    EXPECT_TRUE(CPU6502::isPageCrossed(0x4001, 0x4101));
    EXPECT_FALSE(CPU6502::isPageCrossed(0x4001, 0x4005));
    EXPECT_FALSE(CPU6502::isPageCrossed(0x3333, 0x3335));
}
