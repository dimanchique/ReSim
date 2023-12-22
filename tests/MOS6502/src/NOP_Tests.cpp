#include "MOS6502_TestingSuite.h"

class MOS6502_NOPFixture : public MOS6502_TestFixture {};

TEST_F(MOS6502_NOPFixture, NOP_IMPL_CanTakecycles) {
    // given:
    mem[0xFFFC] = MOS6502_OpCodes::NOP_IMPL;

    cyclesExpected = 2;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    CheckCyclesCount();
}

