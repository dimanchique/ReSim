#include "MOS6502_TestingSuite.h"

class MOS6502_NOPFixture : public MOS6502_TestFixture {};

TEST_F(MOS6502_NOPFixture, NOP_IMPL_CanTakeCycles) {
    // given:
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0xFF;
    mem[0xFF00] = NOP_IMPL;
    mem[0xFF01] = STOP_OPCODE;

    cyclesExpected = 2;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    CheckCyclesCount();
}

