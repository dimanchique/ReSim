#include "I8080_TestingSuite.h"

class I8080_NOPFixture : public I8080_TestFixture {};

TEST_F(I8080_NOPFixture, NOP_CanTakeCycles) {
    // given:
    mem[0x0000] = I8080_OpCodes::NOP;

    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    CheckCyclesCount();
}

