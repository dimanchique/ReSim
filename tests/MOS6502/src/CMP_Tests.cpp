#include "MOS6502_CM_Tests.h"

class MOS6502_CMPFixture : public MOS6502_CMFixture {};

TEST_F(MOS6502_CMPFixture, CMP_IM_CanCompare) {
    CM_IM_CanCompare(CMP_IM, cpu.A, 0x10, 0x4);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
}

TEST_F(MOS6502_CMPFixture, CMP_IM_CanAffectZeroFlag) {
    CM_IM_CanCompare(CMP_IM, cpu.A, 0x10, 0x10);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(MOS6502_CMPFixture, CMP_IM_CanAffectNegativeFlag) {
    CM_IM_CanCompare(CMP_IM, cpu.A, 0x10, 0x11);
    EXPECT_FALSE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(MOS6502_CMPFixture, CMP_ZP_CanCompare) {
    CM_ZP_CanCompare(CMP_ZP, cpu.A, 0x10, 0x4);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
}

TEST_F(MOS6502_CMPFixture, CMP_ZPX_CanCompare) {
    cpu.X = 0x5;
    CM_ZP_CanCompare(CMP_ZPX, cpu.A, 0x10, 0x4, cpu.X);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
}

TEST_F(MOS6502_CMPFixture, CMP_ABS_CanCompare) {
    CM_ABS_CanCompare(CMP_ABS, cpu.A, 0x10, 0x4);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
}

TEST_F(MOS6502_CMPFixture, CMP_ABSX_CanCompare) {
    cpu.X = 0x01;
    CM_ABS_CanCompare(CMP_ABSX, cpu.A, 0x10, 0x4, cpu.X);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
}

TEST_F(MOS6502_CMPFixture, CMP_ABSX_CanCompare_WithExtraCycleOnPageCrossing) {
    cpu.X = 0xFF;
    CM_ABS_CanCompare(CMP_ABSX, cpu.A, 0x10, 0x4, cpu.X);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
}

TEST_F(MOS6502_CMPFixture, CMP_ABSY_CanCompare) {
    cpu.Y = 0x01;
    CM_ABS_CanCompare(CMP_ABSY, cpu.A, 0x10, 0x4, cpu.Y);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
}

TEST_F(MOS6502_CMPFixture, CMP_ABSY_CanCompare_WithExtraCycleOnPageCrossing) {
    cpu.Y = 0xFF;
    CM_ABS_CanCompare(CMP_ABSY, cpu.A, 0x10, 0x4, cpu.Y);
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
}

TEST_F(MOS6502_CMPFixture, CMP_INDX_CanCompare) {
    // given:
    cpu.A = 0x10;
    cpu.X = 0x04;
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0xFF;
    mem[0xFF00] = CMP_INDX;
    mem[0xFF01] = 0x02;
    mem[0xFF02] = STOP_OPCODE;
    mem[0x0006] = 0x00;
    mem[0x0007] = 0x80;
    mem[0x8000] = 0x4;

    cyclesExpected = 6;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
    CheckCyclesCount();
}

TEST_F(MOS6502_CMPFixture, CMP_INDY_CanCompare) {
    // given:
    cpu.A = 0x10;
    cpu.Y = 0x04;
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0xFF;
    mem[0xFF00] = CMP_INDY;
    mem[0xFF01] = 0x02;
    mem[0xFF02] = STOP_OPCODE;
    mem[0x0002] = 0x00;
    mem[0x0003] = 0x80;
    mem[0x8004] = 0x4;

    cyclesExpected = 5;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
    CheckCyclesCount();
}

TEST_F(MOS6502_CMPFixture, CMP_INDY_CanCompare_WithExtraCycleOnPageCrossing) {
    // given:
    cpu.A = 0x10;
    cpu.Y = 0xFF;
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0xFF;
    mem[0xFF00] = CMP_INDY;
    mem[0xFF01] = 0x02;
    mem[0xFF02] = STOP_OPCODE;
    mem[0x0002] = 0x02;
    mem[0x0003] = 0x80;
    mem[0x8101] = 0x4;

    cyclesExpected = 6;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_TRUE(cpu.Status.C);
    EXPECT_FALSE(cpu.Status.Z);
    CheckCyclesCount();
}
