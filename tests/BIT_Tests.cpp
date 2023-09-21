#include "CPU6502_TestingSuite.h"

class CPU6502_BITFixture : public CPU6502_TestFixture {
public:

    void BIT_ZP_CanTestMemoryValue(BYTE MaskValue, BYTE TargetValue) {
        cpu.A = MaskValue;
        mem[0xFFFC] = BIT_ZP;
        mem[0xFFFD] = 0x42;
        mem[0x42] = TargetValue;

        CyclesExpected = 3;

        // when:
        CyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.Status.V, (TargetValue >> 6) & 1);
        EXPECT_EQ(cpu.Status.N, (TargetValue >> 7) & 1);
        CheckCyclesCount();
    }

    void BIT_ABS_CanTestMemoryValue(BYTE MaskValue, BYTE TargetValue) {
        cpu.A = MaskValue;
        mem[0xFFFC] = BIT_ABS;
        mem[0xFFFD] = 0x00;
        mem[0xFFFE] = 0x42;
        mem[0x4200] = TargetValue;

        CyclesExpected = 4;

        // when:
        CyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.Status.V, (TargetValue >> 6) & 1);
        EXPECT_EQ(cpu.Status.N, (TargetValue >> 7) & 1);
        CheckCyclesCount();
    }
};

TEST_F(CPU6502_BITFixture, BIT_ZP_CanTestMemoryValue){
    BIT_ZP_CanTestMemoryValue(0x42, 0x42);
    EXPECT_FALSE(cpu.Status.Z);
}

TEST_F(CPU6502_BITFixture, BIT_ZP_CanAffectZeroValue){
    BIT_ZP_CanTestMemoryValue(0x42, 0x00);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(CPU6502_BITFixture, BIT_ABS_CanTestMemoryValue){
    BIT_ABS_CanTestMemoryValue(0x42, 0x42);
    EXPECT_FALSE(cpu.Status.Z);
}

TEST_F(CPU6502_BITFixture, BIT_ABS_CanAffectZeroValue){
    BIT_ABS_CanTestMemoryValue(0x42, 0x00);
    EXPECT_TRUE(cpu.Status.Z);
}
