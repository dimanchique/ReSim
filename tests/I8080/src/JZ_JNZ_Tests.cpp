#include "I8080_TestingSuite.h"

class I8080_JZFixture : public I8080_TestFixture {};

TEST_F(I8080_JZFixture, JZ_CanJumpOnZeroSet) {
    // given:
    cpu.Status.Z = 1;
    mem[0x0000] = JZ;
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

TEST_F(I8080_JZFixture, JZ_CannotJumpOnZeroReset) {
    // given:
    cpu.Status.Z = 0;
    mem[0x0000] = JZ;
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

class I8080_JNZFixture : public I8080_TestFixture {};

TEST_F(I8080_JNZFixture, JNZ_CanJumpOnZeroReset) {
    // given:
    cpu.Status.Z = 0;
    mem[0x0000] = JNZ;
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

TEST_F(I8080_JNZFixture, JNZ_CannotJumpOnZeroSet) {
    // given:
    cpu.Status.Z = 1;
    mem[0x0000] = JNZ;
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
