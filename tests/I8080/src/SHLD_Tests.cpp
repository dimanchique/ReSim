#include "I8080_TestingSuite.h"

class I8080_SHLDFixture : public I8080_TestFixture {};

TEST_F(I8080_SHLDFixture, SHLD_CanStoreHL_1) {
    // given:
    cpu.H = 0x22;
    cpu.L = 0x33;
    mem[0x0000] = I8080_OpCodes::SHLD;
    mem[0x0001] = 0x12;
    mem[0x0002] = 0x34;

    cyclesExpected = 16;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(mem[0x1234], 0x33);
    EXPECT_EQ(mem[0x1235], 0x22);
    CheckCyclesCount();
}

TEST_F(I8080_SHLDFixture, SHLD_CanStoreHL_2) {
    // given:
    cpu.H = 0xAE;
    cpu.L = 0x29;
    mem[0x0000] = I8080_OpCodes::SHLD;
    mem[0x0001] = 0x01;
    mem[0x0002] = 0x0A;

    cyclesExpected = 16;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(mem[0x010A], 0x29);
    EXPECT_EQ(mem[0x010B], 0xAE);
    CheckCyclesCount();
}

