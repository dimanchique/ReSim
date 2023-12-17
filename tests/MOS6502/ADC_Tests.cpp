#include "MOS6502_TestingSuite.h"

class MOS6502_ADCFixture : public MOS6502_TestFixture {
public:

    void ADC_IM_DoAddValue(BYTE initialValue, BYTE memoryValue) {
        // given:
        cpu.A = initialValue;
        mem[0xFFFC] = ADC_IM;
        mem[0xFFFD] = memoryValue;

        cyclesExpected = 2;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        CheckCyclesCount();
    }
};

TEST_F(MOS6502_ADCFixture, ADC_IM_CanAddValue) {
    ADC_IM_DoAddValue(0x50, 0x10);

    EXPECT_EQ(cpu.A, 0x60);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(MOS6502_ADCFixture, ADC_IM_CanAddValue_WithCarryFlag) {
    cpu.Status.C = 1;

    ADC_IM_DoAddValue(0x50, 0x10);

    EXPECT_EQ(cpu.A, 0x61);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(MOS6502_ADCFixture, ADC_IM_CanAffectNegativeFlag) {
    ADC_IM_DoAddValue(0x00, 0xFF);

    EXPECT_EQ(cpu.A, 0xFF);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
    EXPECT_FALSE(cpu.Status.C);
}

TEST_F(MOS6502_ADCFixture, ADC_IM_CanAffectZeroFlag) {
    cpu.Status.C = 1;
    ADC_IM_DoAddValue(0x00, 0xFF);

    EXPECT_EQ(cpu.A, 0x00);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    EXPECT_TRUE(cpu.Status.C);
}

TEST_F(MOS6502_ADCFixture, ADC_IM_StatusFlagTest_1) {
    ADC_IM_DoAddValue(0x50, 0x10);

    EXPECT_EQ(cpu.A, 0x60);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.V);
}

TEST_F(MOS6502_ADCFixture, ADC_IM_StatusFlagTest_2) {
    ADC_IM_DoAddValue(0x50, 0x50);

    EXPECT_EQ(cpu.A, 0xa0);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_TRUE(cpu.Status.V);
}

TEST_F(MOS6502_ADCFixture, ADC_IM_StatusFlagTest_3) {
    ADC_IM_DoAddValue(0x50, 0x90);

    EXPECT_EQ(cpu.A, 0xe0);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.V);
}

TEST_F(MOS6502_ADCFixture, ADC_IM_StatusFlagTest_4) {
    ADC_IM_DoAddValue(0x50, 0xd0);

    EXPECT_EQ(cpu.A, (0xFF) & 0x120);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.V);
}

TEST_F(MOS6502_ADCFixture, ADC_IM_StatusFlagTest_5) {
    ADC_IM_DoAddValue(0xd0, 0x10);

    EXPECT_EQ(cpu.A, 0xe0);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.V);
}

TEST_F(MOS6502_ADCFixture, ADC_IM_StatusFlagTest_6) {
    ADC_IM_DoAddValue(0xd0, 0x50);

    EXPECT_EQ(cpu.A, (0xFF) & 0x120);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.V);
}

TEST_F(MOS6502_ADCFixture, ADC_IM_StatusFlagTest_7) {
    ADC_IM_DoAddValue(0xd0, 0x90);

    EXPECT_EQ(cpu.A, (0xFF) & 0x160);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_TRUE(cpu.Status.V);
}

TEST_F(MOS6502_ADCFixture, ADC_IM_StatusFlagTest_8) {
    ADC_IM_DoAddValue(0xd0, 0xd0);

    EXPECT_EQ(cpu.A, (0xFF) & 0x1a0);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.V);
}

TEST_F(MOS6502_ADCFixture, ADC_IM_StatusFlagTest_9) {
    ADC_IM_DoAddValue(0x80, 0xFF);

    EXPECT_EQ(cpu.A, (0xFF) & 0x7F);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_TRUE(cpu.Status.V);
}

TEST_F(MOS6502_ADCFixture, ADC_ZP_CanAddValue) {
    // given:
    cpu.A = 0x42;
    mem[0xFFFC] = ADC_ZP;
    mem[0xFFFD] = 0x42;
    mem[0x0042] = 0x02;

    cyclesExpected = 3;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x44);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}

TEST_F(MOS6502_ADCFixture, ADC_ZPX_CanAddValue) {
    // given:
    cpu.A = 0x42;
    cpu.X = 0x15;
    mem[0xFFFC] = ADC_ZPX;
    mem[0xFFFD] = 0x42;
    mem[(mem[0xFFFD] + cpu.X) & 0xFF] = 0x02;
    // store this value in targetRegister register
    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x44);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}

TEST_F(MOS6502_ADCFixture, ADC_ABS_CanAddValue) {
    // given:
    cpu.A = 0x42;
    mem[0xFFFC] = ADC_ABS;
    mem[0xFFFD] = 0x80;
    mem[0xFFFE] = 0x44;
    mem[0x4480] = 0x02;

    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x44);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}

TEST_F(MOS6502_ADCFixture, ADC_ABSX_CanAddValue) {
    // given:
    cpu.A = 0x42;
    cpu.X = 0x15;
    mem[0xFFFC] = ADC_ABSX;
    mem[0xFFFD] = 0x02;
    mem[0xFFFE] = 0x44;
    mem[0x4402 + cpu.X] = 0x02;

    cyclesExpected = IsPageCrossed(0x4402 + cpu.X, 0x4402) ? 5 : 4;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x44);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}

TEST_F(MOS6502_ADCFixture, ADC_ABSY_CanAddValue) {
    // given:
    cpu.A = 0x42;
    cpu.Y = 0x15;
    mem[0xFFFC] = ADC_ABSY;
    mem[0xFFFD] = 0x02;
    mem[0xFFFE] = 0x44;
    mem[0x4402 + cpu.Y] = 0x02;

    cyclesExpected = IsPageCrossed(0x4402 + cpu.Y, 0x4402) ? 5 : 4;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x44);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}


TEST_F(MOS6502_ADCFixture, ADC_INDX_CanAddValue) {
    // given:
    cpu.A = 0x42;
    cpu.X = 0x04;
    mem[0xFFFC] = MOS6502_OpCodes::ADC_INDX;
    mem[0xFFFD] = 0x02;
    mem[0x0006] = 0x00;
    mem[0x0007] = 0x80;
    mem[0x8000] = 0x02;

    cyclesExpected = 6;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x44);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}

TEST_F(MOS6502_ADCFixture, ADC_INDY_CanAddValue) {
    // given:
    cpu.A = 0x42;
    cpu.Y = 0x04;
    mem[0xFFFC] = MOS6502_OpCodes::ADC_INDY;
    mem[0xFFFD] = 0x02;
    mem[0x0002] = 0x00;
    mem[0x0003] = 0x80;
    mem[0x8004] = 0x02;

    cyclesExpected = 5;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x44);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}

TEST_F(MOS6502_ADCFixture, ADC_INDY_CanAddValue_WithExtraCycleOnPageCrossing) {
    // given:
    cpu.A = 0x42;
    cpu.Y = 0xFF;
    mem[0xFFFC] = MOS6502_OpCodes::ADC_INDY;
    mem[0xFFFD] = 0x02;
    mem[0x0002] = 0x02;
    mem[0x0003] = 0x80;
    mem[0x8101] = 0x02;

    cyclesExpected = 6;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x44);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}
