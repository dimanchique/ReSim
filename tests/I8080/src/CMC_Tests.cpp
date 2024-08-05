#include "I8080_TestingSuite.h"

class I8080_CMCFixture : public I8080_TestFixture {};

TEST_F(I8080_CMCFixture, CMC_CanComplimentCarry) {
    bool InitialCarry = false;
    cpu.Status.C = InitialCarry;
    mem[0x0000] = CMC;
    mem[0x0001] = STOP_OPCODE;

    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.Status.C, !InitialCarry);
    CheckCyclesCount();
}
