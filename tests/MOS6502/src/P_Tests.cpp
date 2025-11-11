#include "MOS6502_TestingSuite.h"

class MOS6502_PFixture : public MOS6502_TestFixture {};

TEST_F(MOS6502_PFixture, PHA_IMPL_CanPushAccumulator) {
    // given:
    cpu.A = 0x42;
    mem[effectiveAddress++] = PHA_IMPL;
    mem[effectiveAddress++] = PLA_IMPL;
    mem[effectiveAddress++] = RTS_IMPL;

    cyclesExpected = 3 + 4;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(mem[cpu.StackPointerToAddress()], 0x42);
    CheckCyclesCount();
}

TEST_F(MOS6502_PFixture, PHA_IMPL_CanPushAndPullAccumulator) {
    // given:
    cpu.A = 0x42;
    mem[effectiveAddress++] = PHA_IMPL;
    mem[effectiveAddress++] = TXA_IMPL;
    mem[effectiveAddress++] = PLA_IMPL;
    mem[effectiveAddress++] = RTS_IMPL;

    cyclesExpected = 3 + 2 + 4;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.A, 0x42);
    CheckCyclesCount();
}

TEST_F(MOS6502_PFixture, PHP_IMPL_CanPushStatusRegister) {
    // given:
    cpu.Status.Value = 0x42;                      // just for test
    mem[effectiveAddress++] = PHP_IMPL;
    mem[effectiveAddress++] = PLP_IMPL;
    mem[effectiveAddress++] = RTS_IMPL;

    cyclesExpected = 3 + 4;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(mem[cpu.StackPointerToAddress()], 0x42);
    CheckCyclesCount();
}

TEST_F(MOS6502_PFixture, PHP_IMPL_CanPushAndPullAccumulator) {
    // given:
    cpu.Status.Value = 0x42;
    mem[effectiveAddress++] = PHP_IMPL;
    mem[effectiveAddress++] = PHA_IMPL;
    mem[effectiveAddress++] = PLP_IMPL;
    mem[effectiveAddress++] = PLA_IMPL;
    mem[effectiveAddress++] = RTS_IMPL;

    cyclesExpected = 3 + 3 + 4 + 4;

    // when:
    cyclesPassed = cpu.Run();

    // then:
    EXPECT_EQ(cpu.A, 0x42);
    EXPECT_EQ(cpu.Status.Value, 0x00);
    CheckCyclesCount();
}
