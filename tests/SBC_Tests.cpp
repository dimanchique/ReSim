#include "CPU6502_TestingSuite.h"

class CPU6502_SBCFixture : public CPU6502_TestFixture {
public:
    void SBC_IM_DoSubtractValue(BYTE initialValue, BYTE memoryValue) {
        // given:
        cpu.A = initialValue;
        mem[0xFFFC] = SBC_IM;
        mem[0xFFFD] = memoryValue;

        cyclesExpected = 2;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        CheckCyclesCount();
    }
};

TEST_F(CPU6502_SBCFixture, SBC_IM_CanSubtractValue) {
    SBC_IM_DoSubtractValue(0x50, 0x10);

    EXPECT_EQ(cpu.A, 0x3F);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(CPU6502_SBCFixture, SBC_IM_CanSubtractValue_WithCarryFlag) {
    cpu.Status.C = 1;

    SBC_IM_DoSubtractValue(0x50, 0x10);

    EXPECT_EQ(cpu.A, 0x40);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(CPU6502_SBCFixture, SBC_IM_CanAffectNegativeFlag) {
    SBC_IM_DoSubtractValue(0x00, 0x00);

    EXPECT_EQ(cpu.A, 0xFF);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
    EXPECT_TRUE(cpu.Status.C);
}

TEST_F(CPU6502_SBCFixture, SBC_IM_CanAffectZeroFlag) {
    cpu.Status.C = 1;
    SBC_IM_DoSubtractValue(0x00, 0x00);

    EXPECT_EQ(cpu.A, 0x00);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    EXPECT_FALSE(cpu.Status.C);
}

TEST_F(CPU6502_SBCFixture, SBC_IM_StatusFlagTest_1) {
    SBC_IM_DoSubtractValue(0x50, 0x10);

    EXPECT_EQ(cpu.A, 0x3f);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.V);
}

TEST_F(CPU6502_SBCFixture, SBC_IM_StatusFlagTest_2) {
    SBC_IM_DoSubtractValue(0x50, 0x50);

    EXPECT_EQ(cpu.A, 0xFF);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_TRUE(cpu.Status.V);
}

TEST_F(CPU6502_SBCFixture, SBC_IM_StatusFlagTest_3) {
    SBC_IM_DoSubtractValue(0x50, 0x90);

    EXPECT_EQ(cpu.A, 0xbf);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.V);
}

TEST_F(CPU6502_SBCFixture, SBC_IM_StatusFlagTest_4) {
    SBC_IM_DoSubtractValue(0x50, 0xd0);

    EXPECT_EQ(cpu.A, 0x7f);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.V);
}

TEST_F(CPU6502_SBCFixture, SBC_IM_StatusFlagTest_5) {
    SBC_IM_DoSubtractValue(0xd0, 0x10);

    EXPECT_EQ(cpu.A, 0xbf);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.V);
}

TEST_F(CPU6502_SBCFixture, SBC_IM_StatusFlagTest_6) {
    SBC_IM_DoSubtractValue(0xd0, 0x50);

    EXPECT_EQ(cpu.A, 0x7f);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.V);
}

TEST_F(CPU6502_SBCFixture, SBC_IM_StatusFlagTest_7) {
    SBC_IM_DoSubtractValue(0xd0, 0x90);

    EXPECT_EQ(cpu.A, 0x3f);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_TRUE(cpu.Status.V);
}

TEST_F(CPU6502_SBCFixture, SBC_IM_StatusFlagTest_8) {
    SBC_IM_DoSubtractValue(0xd0, 0xd0);

    EXPECT_EQ(cpu.A, 0xFF);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.V);
}

TEST_F(CPU6502_SBCFixture, SBC_IM_StatusFlagTest_9) {
    SBC_IM_DoSubtractValue(0x80, 0xFF);

    EXPECT_EQ(cpu.A, 0x80);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.V);
}

TEST_F(CPU6502_SBCFixture, SBC_ZP_CanSubtractValue) {
    // given:
    cpu.A = 0x42;
    mem[0xFFFC] = SBC_ZP;
    mem[0xFFFD] = 0x42;
    mem[0x0042] = 0x02;

    cyclesExpected = 3;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x3f);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}

TEST_F(CPU6502_SBCFixture, SBC_ZPX_CanSubtractValue) {
    // given:
    cpu.A = 0x42;
    cpu.X = 0x15;
    mem[0xFFFC] = SBC_ZPX;
    mem[0xFFFD] = 0x42;
    mem[(mem[0xFFFD] + cpu.X) & 0xFF] = 0x02;
    // store this value in targetRegister register
    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x3f);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}

TEST_F(CPU6502_SBCFixture, SBC_ABS_CanSubtractValue) {
    // given:
    cpu.A = 0x42;
    mem[0xFFFC] = SBC_ABS;
    mem[0xFFFD] = 0x80;
    mem[0xFFFE] = 0x44;
    mem[0x4480] = 0x02;

    cyclesExpected = 4;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x3f);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}

TEST_F(CPU6502_SBCFixture, SBC_ABSX_CanSubtractValue) {
    // given:
    cpu.A = 0x42;
    cpu.X = 0x15;
    mem[0xFFFC] = SBC_ABSX;
    mem[0xFFFD] = 0x02;
    mem[0xFFFE] = 0x44;
    mem[0x4402 + cpu.X] = 0x02;

    cyclesExpected = IsPageCrossed(0x4402 + cpu.X, 0x4402) ? 5 : 4;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x3f);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}

TEST_F(CPU6502_SBCFixture, SBC_ABSY_CanSubtractValue) {
    // given:
    cpu.A = 0x42;
    cpu.Y = 0x15;
    mem[0xFFFC] = SBC_ABSY;
    mem[0xFFFD] = 0x02;
    mem[0xFFFE] = 0x44;
    mem[0x4402 + cpu.Y] = 0x02;

    cyclesExpected = IsPageCrossed(0x4402 + cpu.Y, 0x4402) ? 5 : 4;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x3f);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}


TEST_F(CPU6502_SBCFixture, SBC_INDX_CanSubtractValue) {
    // given:
    cpu.A = 0x42;
    cpu.X = 0x04;
    mem[0xFFFC] = CPU6502_OpCodes::SBC_INDX;
    mem[0xFFFD] = 0x02;
    mem[0x0006] = 0x00;
    mem[0x0007] = 0x80;
    mem[0x8000] = 0x02;

    cyclesExpected = 6;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x3f);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}

TEST_F(CPU6502_SBCFixture, SBC_INDY_CanSubtractValue) {
    // given:
    cpu.A = 0x42;
    cpu.Y = 0x04;
    mem[0xFFFC] = CPU6502_OpCodes::SBC_INDY;
    mem[0xFFFD] = 0x02;
    mem[0x0002] = 0x00;
    mem[0x0003] = 0x80;
    mem[0x8004] = 0x02;

    cyclesExpected = 5;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x3f);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}

TEST_F(CPU6502_SBCFixture, SBC_INDY_CanSubtractValue_WithExtraCycleOnPageCrossing) {
    // given:
    cpu.A = 0x42;
    cpu.Y = 0xFF;
    mem[0xFFFC] = CPU6502_OpCodes::SBC_INDY;
    mem[0xFFFD] = 0x02;
    mem[0x0002] = 0x02;
    mem[0x0003] = 0x80;
    mem[0x8101] = 0x02;

    cyclesExpected = 6;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x3f);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}
