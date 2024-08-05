#include "I8080_TestingSuite.h"

class I8080_CMAFixture : public I8080_TestFixture {};

TEST_F(I8080_CMAFixture, CMA_CanComplimentAccumulator) {
    constexpr BYTE initialAccumulator = 0x51;
    cpu.A = initialAccumulator;
    mem[0x0000] = CMA;
    mem[0x0001] = STOP_OPCODE;

    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_NE(initialAccumulator, cpu.A);
    EXPECT_EQ(cpu.A, BYTE(~initialAccumulator));
    CheckCyclesCount();
}
