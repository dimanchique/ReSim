#include "I8080_TestingSuite.h"

class I8080_STCFixture : public I8080_TestFixture {};

TEST_F(I8080_STCFixture, STC_CanSetCarry) {
    cpu.Status.C = 0;
    mem[0x0000] = I8080_OpCodes::STC;

    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.Status.C, 1);
    CheckCyclesCount();
}
