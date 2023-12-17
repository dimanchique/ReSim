#include "MOS6502_DEC_Tests.h"

class MOS6502_DECMFixture : public MOS6502_DECFixture {};

TEST_F(MOS6502_DECMFixture, DEC_ZP_CanAffectMemory) {
    DEC_ZP_CanAffectValue(DEC_ZP, 0x9);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(MOS6502_DECMFixture, DEC_ZP_CanAffectZeroFlag) {
    DEC_ZP_CanAffectValue(DEC_ZP, 0x1);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(MOS6502_DECMFixture, DEC_ZP_CanAffectNegativeFlag) {
    DEC_ZP_CanAffectValue(DEC_ZP, 0x0);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(MOS6502_DECMFixture, DEC_ZPX_CanAffectMemory) {
    cpu.X = 0x2;
    DEC_ZP_CanAffectValue(DEC_ZPX, 0x9, cpu.X);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(MOS6502_DECMFixture, DEC_ZPX_CanAffectZeroFlag) {
    cpu.X = 0x2;
    DEC_ZP_CanAffectValue(DEC_ZPX, 0x1, cpu.X);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(MOS6502_DECMFixture, DEC_ZPX_CanAffectNegativeFlag) {
    cpu.X = 0x2;
    DEC_ZP_CanAffectValue(DEC_ZPX, 0x0, cpu.X);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(MOS6502_DECMFixture, DEC_ABS_CanAffectMemory) {
    DEC_ABS_CanAffectValue(DEC_ABS, 0x9);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(MOS6502_DECMFixture, DEC_ABS_CanAffectZeroFlag) {
    DEC_ABS_CanAffectValue(DEC_ABS, 0x1);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(MOS6502_DECMFixture, DEC_ABS_CanAffectNegativeFlag) {
    DEC_ABS_CanAffectValue(DEC_ABS, 0x0);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(MOS6502_DECMFixture, DEC_ABSX_CanAffectMemory) {
    cpu.X = 0x4;
    DEC_ABS_CanAffectValue(DEC_ABSX, 0x9, cpu.X);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(MOS6502_DECMFixture, DEC_ABSX_CanAffectZeroFlag) {
    cpu.X = 0x4;
    DEC_ABS_CanAffectValue(DEC_ABSX, 0x1, cpu.X);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(MOS6502_DECMFixture, DEC_ABSX_CanAffectNegativeFlag) {
    cpu.X = 0x4;
    DEC_ABS_CanAffectValue(DEC_ABSX, 0x0, cpu.X);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
}
