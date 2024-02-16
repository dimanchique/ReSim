#include "I8080_TestingSuite.h"

class I8080_JCFixture : public I8080_TestFixture {};

TEST_F(I8080_JCFixture, JC_CanJumpOnCarrySet) {
    // given:
    cpu.Status.C = 1;
    mem[0x0000] = I8080_OpCodes::JC;
    mem[0x0001] = 0x3C;
    mem[0x0002] = 0x00;

    cyclesExpected = 10;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.PC, 0x3C00);
    CheckCyclesCount();
}

TEST_F(I8080_JCFixture, JC_CannotJumpOnCarryReset) {
    // given:
    cpu.Status.C = 0;
    mem[0x0000] = I8080_OpCodes::JC;
    mem[0x0001] = 0x3C;
    mem[0x0002] = 0x00;

    cyclesExpected = 10;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.PC, 0x0003);
    CheckCyclesCount();
}

class I8080_JNCFixture : public I8080_TestFixture {};

TEST_F(I8080_JNCFixture, JNC_CanJumpOnCarryReset) {
    // given:
    cpu.Status.C = 0;
    mem[0x0000] = I8080_OpCodes::JNC;
    mem[0x0001] = 0x3C;
    mem[0x0002] = 0x00;

    cyclesExpected = 10;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.PC, 0x3C00);
    CheckCyclesCount();
}

TEST_F(I8080_JNCFixture, JNC_CannotJumpOnCarrySet) {
    // given:
    cpu.Status.C = 1;
    mem[0x0000] = I8080_OpCodes::JNC;
    mem[0x0001] = 0x3C;
    mem[0x0002] = 0x00;

    cyclesExpected = 10;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.PC, 0x0003);
    CheckCyclesCount();
}
