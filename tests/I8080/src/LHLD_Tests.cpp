#include "I8080_TestingSuite.h"

class I8080_LHLDFixture : public I8080_TestFixture {};

TEST_F(I8080_LHLDFixture, LHLD_CanLoadHL_1) {
    // given:
    mem[0x1234] = 0x22;
    mem[0x1235] = 0x33;
    mem[0x0000] = I8080_OpCodes::LHLD;
    mem[0x0001] = 0x12;
    mem[0x0002] = 0x34;

    cyclesExpected = 16;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(0x22, cpu.L);
    EXPECT_EQ(0x33, cpu.H);
    CheckCyclesCount();
}

TEST_F(I8080_LHLDFixture, LHLD_CanLoadHL_2) {
    // given:
    mem[0x25B] = 0xFF;
    mem[0x25C] = 0x03;
    mem[0x0000] = I8080_OpCodes::LHLD;
    mem[0x0001] = 0x02;
    mem[0x0002] = 0x5B;

    cyclesExpected = 16;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(0xFF, cpu.L);
    EXPECT_EQ(0x03, cpu.H);
    CheckCyclesCount();
}

