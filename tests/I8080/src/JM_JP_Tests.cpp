#include "I8080_TestingSuite.h"

class I8080_JMFixture : public I8080_TestFixture {};

TEST_F(I8080_JMFixture, JM_CanJumpOnSignSet) {
    // given:
    cpu.Status.S = 1;
    mem[0x0000] = JM;
    mem[0x0001] = 0x3C;
    mem[0x0002] = 0x00;
    mem[0x003C] = RET;

    cyclesExpected = 10;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.PC, 0x003C);
    CheckCyclesCount();
}

TEST_F(I8080_JMFixture, JM_CannotJumpOnSignReset) {
    // given:
    cpu.Status.S = 0;
    mem[0x0000] = JM;
    mem[0x0001] = 0x3C;
    mem[0x0002] = 0x00;
    mem[0x0003] = RET;

    cyclesExpected = 10;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.PC, 0x0003);
    CheckCyclesCount();
}

class I8080_JPFixture : public I8080_TestFixture {};

TEST_F(I8080_JPFixture, JP_CanJumpOnSignReset) {
    // given:
    cpu.Status.S = 0;
    mem[0x0000] = JP;
    mem[0x0001] = 0x3C;
    mem[0x0002] = 0x00;
    mem[0x003C] = RET;

    cyclesExpected = 10;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.PC, 0x003C);
    CheckCyclesCount();
}

TEST_F(I8080_JPFixture, JP_CannotJumpOnSignSet) {
    // given:
    cpu.Status.S = 1;
    mem[0x0000] = JP;
    mem[0x0001] = 0x3C;
    mem[0x0002] = 0x00;
    mem[0x0003] = RET;

    cyclesExpected = 10;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.PC, 0x0003);
    CheckCyclesCount();
}
