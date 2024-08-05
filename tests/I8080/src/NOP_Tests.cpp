#include "I8080_TestingSuite.h"

class I8080_NOPFixture : public I8080_TestFixture {};

TEST_F(I8080_NOPFixture, NOP_CanTakeCycles) {
    // given:
    mem[0x0000] = NOP;
    mem[0x0001] = STOP_OPCODE;

    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    CheckCyclesCount();
}

