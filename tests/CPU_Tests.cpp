#include "CPU6502_TestingSuite.h"

class CPU6502_CPUFixture : public CPU6502_TestFixture {};

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

class UtilsTests : public testing::Test {};

TEST_F(UtilsTests, PageCrossingTest) {
    EXPECT_TRUE(IsPageCrossed(0x4001, 0x3ffe));
    EXPECT_TRUE(IsPageCrossed(0x4001, 0x4101));
    EXPECT_FALSE(IsPageCrossed(0x4001, 0x4005));
    EXPECT_FALSE(IsPageCrossed(0x3333, 0x3335));
}

TEST_F(UtilsTests, DataConversionTest) {
    EXPECT_EQ((BYTE) 45, (SBYTE) 45);
    EXPECT_NE((BYTE) 250, (SBYTE) 250);
    EXPECT_EQ((BYTE) 258, 0x2);
    EXPECT_EQ((SBYTE) 253, -3);
}
