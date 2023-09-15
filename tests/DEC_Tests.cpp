#include "CPU6502_DE_Tests.h"

class CPU6502_DECFixture : public CPU6502_DEFixture{};

TEST_F(CPU6502_DECFixture, DEC_ZP_CanAffectMemory){
    DE_ZP_CanAffectValue(DEC_ZP, 0x9);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(CPU6502_DECFixture, DEC_ZP_CanAffectZeroFlag){
    DE_ZP_CanAffectValue(DEC_ZP, 0x1);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(CPU6502_DECFixture, DEC_ZP_CanAffectNegativeFlag){
    DE_ZP_CanAffectValue(DEC_ZP, 0x0);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(CPU6502_DECFixture, DEC_ZPX_CanAffectMemory){
    cpu.X = 0x2;
    DE_ZP_CanAffectValue(DEC_ZPX, 0x9, cpu.X);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(CPU6502_DECFixture, DEC_ZPX_CanAffectZeroFlag){
    cpu.X = 0x2;
    DE_ZP_CanAffectValue(DEC_ZPX, 0x1, cpu.X);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(CPU6502_DECFixture, DEC_ZPX_CanAffectNegativeFlag){
    cpu.X = 0x2;
    DE_ZP_CanAffectValue(DEC_ZPX, 0x0, cpu.X);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(CPU6502_DECFixture, DEC_ABS_CanAffectMemory){
    DE_ABS_CanAffectValue(DEC_ABS, 0x9);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(CPU6502_DECFixture, DEC_ABS_CanAffectZeroFlag){
    DE_ABS_CanAffectValue(DEC_ABS, 0x1);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(CPU6502_DECFixture, DEC_ABS_CanAffectNegativeFlag){
    DE_ABS_CanAffectValue(DEC_ABS, 0x0);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(CPU6502_DECFixture, DEC_ABSX_CanAffectMemory){
    cpu.X = 0x4;
    DE_ABS_CanAffectValue(DEC_ABSX, 0x9, cpu.X);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(CPU6502_DECFixture, DEC_ABSX_CanAffectZeroFlag){
    cpu.X = 0x4;
    DE_ABS_CanAffectValue(DEC_ABSX, 0x1, cpu.X);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(CPU6502_DECFixture, DEC_ABSX_CanAffectNegativeFlag){
    cpu.X = 0x4;
    DE_ABS_CanAffectValue(DEC_ABSX, 0x0, cpu.X);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
}
