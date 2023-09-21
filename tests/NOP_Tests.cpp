#include "CPU6502_TestingSuite.h"

class CPU6502_NOPFixture : public CPU6502_TestFixture{};

TEST_F(CPU6502_NOPFixture, NOP_IMPL_CanTakeCycles){
    // given:
    mem[0xFFFC] = CPU6502_OpCodes::NOP_IMPL;

    CyclesExpected = 2;

    // when:
    CyclesPassed = cpu.Run(mem);

    // then:
    CheckCyclesCount();
}

