#include "MOS6502_TestingSuite.h"

class MOS6502_NOPFixture : public MOS6502_TestFixture {};

TEST_F(MOS6502_NOPFixture, NOP_IMPL_CanTakeCycles) {
    // given:
    mem[effectiveAddress++] = NOP_IMPL;
    mem[effectiveAddress++] = RTS_IMPL;

    cyclesExpected = 2;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    CheckCyclesCount();
}
