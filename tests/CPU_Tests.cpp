#include "CPU6502_TestingSuite.h"

class CPU6502_CPUFixture : public CPU6502_TestFixture{};

TEST_F(CPU6502_CPUFixture, CpuDoesNothingWithZeroCycles) {
    // given:
    const U32 NumCycles = 0;

    // when:
    CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(NumCycles, CNT);
}

TEST_F(CPU6502_CPUFixture, CpuCanExecuteMoreCyclesThenRequested) {
    // given:
    mem[0xFFFC] = CPU6502_OpCodes::JSR_ABS;     // This instruction takes 6 sycles
    mem[0xFFFD] = 0x42;
    mem[0xFFFE] = 0x42;

    const U32 NumCycles = 1;                    // We're "expecting" 1 cycle

    // when:
    CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(CNT, 6);                          // But there are 6 actually
}
