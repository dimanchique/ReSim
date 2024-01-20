#include "I8080_TestingSuite.h"

class I8080_CMCFixture : public I8080_TestFixture {};

TEST_F(I8080_CMCFixture, CMC_CanComplimentCarry) {
    bool InitialCarry = false;
    cpu.Status.C = InitialCarry;
    mem[0x0000] = I8080_OpCodes::CMC;

    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.Status.C, !InitialCarry);
    CheckCyclesCount();
}
