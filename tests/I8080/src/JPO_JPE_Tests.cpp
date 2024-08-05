#include "I8080_TestingSuite.h"

class I8080_JPEFixture : public I8080_TestFixture {};

TEST_F(I8080_JPEFixture, JPE_CanJumpOnParitySet) {
    // given:
    cpu.Status.P = 1;
    mem[0x0000] = JPE;
    mem[0x0001] = 0x3C;
    mem[0x0002] = 0x00;
    mem[0x3C00] = STOP_OPCODE;

    cyclesExpected = 10;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.PC, 0x3C00);
    CheckCyclesCount();
}

TEST_F(I8080_JPEFixture, JPE_CannotJumpOnParityReset) {
    // given:
    cpu.Status.P = 0;
    mem[0x0000] = JPE;
    mem[0x0001] = 0x3C;
    mem[0x0002] = 0x00;
    mem[0x0003] = STOP_OPCODE;

    cyclesExpected = 10;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.PC, 0x0003);
    CheckCyclesCount();
}

class I8080_JPOFixture : public I8080_TestFixture {};

TEST_F(I8080_JPOFixture, JPO_CanJumpOnParityReset) {
    // given:
    cpu.Status.P = 0;
    mem[0x0000] = JPO;
    mem[0x0001] = 0x3C;
    mem[0x0002] = 0x00;
    mem[0x3C00] = STOP_OPCODE;

    cyclesExpected = 10;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.PC, 0x3C00);
    CheckCyclesCount();
}

TEST_F(I8080_JPOFixture, JPO_CannotJumpOnParitySet) {
    // given:
    cpu.Status.P = 1;
    mem[0x0000] = JPO;
    mem[0x0001] = 0x3C;
    mem[0x0002] = 0x00;
    mem[0x0003] = STOP_OPCODE;

    cyclesExpected = 10;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.PC, 0x0003);
    CheckCyclesCount();
}
