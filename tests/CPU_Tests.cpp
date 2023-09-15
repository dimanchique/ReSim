#include "CPU6502_TestingSuite.h"

class CPU6502_CPUFixture : public CPU6502_TestFixture{};

TEST_F(CPU6502_CPUFixture, CpuDoesNothingWithZeroCycles) {
    // given:
    CyclesExpected = 0;

    // when:
    CyclesPassed = cpu.Run(CyclesExpected, mem);

    // then:
    CheckCyclesCount();
}

TEST_F(CPU6502_CPUFixture, CpuCanExecuteMoreCyclesThenRequested) {
    // given:
    mem[0xFFFC] = CPU6502_OpCodes::JSR_ABS;     // This instruction takes 6 cycles
    mem[0xFFFD] = 0x42;
    mem[0xFFFE] = 0x42;

    CyclesExpected = 1;                         // We're "expecting" 1 cycle

    // when:
    CyclesPassed = cpu.Run(CyclesExpected, mem);

    // then:
    CheckCyclesCount(6);                        // But there are 6 actually
}
