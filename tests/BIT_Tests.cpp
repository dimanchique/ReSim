#include "CPU6502_TestingSuite.h"

class CPU6502_BITFixture : public CPU6502_TestFixture {
public:
    void BIT_ZP_CanTestMemoryValue(BYTE maskValue, BYTE targetValue) {
        // given:
        cpu.A = maskValue;
        mem[0xFFFC] = BIT_ZP;
        mem[0xFFFD] = 0x42;
        mem[0x42] = targetValue;

        cyclesExpected = 3;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.Status.V, (targetValue >> 6) & 1);
        EXPECT_EQ(cpu.Status.N, (targetValue >> 7) & 1);
        CheckCyclesCount();
    }

    void BIT_ABS_CanTestMemoryValue(BYTE maskValue, BYTE targetValue) {
        // given:
        cpu.A = maskValue;
        mem[0xFFFC] = BIT_ABS;
        mem[0xFFFD] = 0x00;
        mem[0xFFFE] = 0x42;
        mem[0x4200] = targetValue;

        cyclesExpected = 4;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.Status.V, (targetValue >> 6) & 1);
        EXPECT_EQ(cpu.Status.N, (targetValue >> 7) & 1);
        CheckCyclesCount();
    }
};

TEST_F(CPU6502_BITFixture, BIT_ZP_CanTestmemoryValue) {
    BIT_ZP_CanTestMemoryValue(0x42, 0x42);
    EXPECT_FALSE(cpu.Status.Z);
}

TEST_F(CPU6502_BITFixture, BIT_ZP_CanAffectZeroValue) {
    BIT_ZP_CanTestMemoryValue(0x42, 0x00);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(CPU6502_BITFixture, BIT_ABS_CanTestmemoryValue) {
    BIT_ABS_CanTestMemoryValue(0x42, 0x42);
    EXPECT_FALSE(cpu.Status.Z);
}

TEST_F(CPU6502_BITFixture, BIT_ABS_CanAffectZeroValue) {
    BIT_ABS_CanTestMemoryValue(0x42, 0x00);
    EXPECT_TRUE(cpu.Status.Z);
}
