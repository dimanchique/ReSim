#include "CPU6502_INC_Tests.h"

class CPU6502_INCMFixture : public CPU6502_INCFixture{};

TEST_F(CPU6502_INCMFixture, INC_ZP_CanAffectMemory){
    INC_ZP_CanAffectValue(INC_ZP, 0x9);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(CPU6502_INCMFixture, INC_ZP_CanAffectZeroFlag){
    INC_ZP_CanAffectValue(INC_ZP, 0xFF);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(CPU6502_INCMFixture, INC_ZP_CanAffectNegativeFlag){
    INC_ZP_CanAffectValue(INC_ZP, 0xFE);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(CPU6502_INCMFixture, INC_ZPX_CanAffectMemory){
    cpu.X = 0x2;
    INC_ZP_CanAffectValue(INC_ZPX, 0x9, cpu.X);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(CPU6502_INCMFixture, INC_ZPX_CanAffectZeroFlag){
    cpu.X = 0x2;
    INC_ZP_CanAffectValue(INC_ZPX, 0xFF, cpu.X);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(CPU6502_INCMFixture, INC_ZPX_CanAffectNegativeFlag){
    cpu.X = 0x2;
    INC_ZP_CanAffectValue(INC_ZPX, 0xFE, cpu.X);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(CPU6502_INCMFixture, INC_ABS_CanAffectMemory){
    INC_ABS_CanAffectValue(INC_ABS, 0x9);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(CPU6502_INCMFixture, INC_ABS_CanAffectZeroFlag){
    INC_ABS_CanAffectValue(INC_ABS, 0xFF);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(CPU6502_INCMFixture, INC_ABS_CanAffectNegativeFlag){
    INC_ABS_CanAffectValue(INC_ABS, 0xFE);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(CPU6502_INCMFixture, INC_ABSX_CanAffectMemory){
    cpu.X = 0x4;
    INC_ABS_CanAffectValue(INC_ABSX, 0x9, cpu.X);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(CPU6502_INCMFixture, INC_ABSX_CanAffectZeroFlag){
    cpu.X = 0x4;
    INC_ABS_CanAffectValue(INC_ABSX, 0xFF, cpu.X);
    EXPECT_TRUE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
}

TEST_F(CPU6502_INCMFixture, INC_ABSX_CanAffectNegativeFlag){
    cpu.X = 0x4;
    INC_ABS_CanAffectValue(INC_ABSX, 0xFE, cpu.X);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_TRUE(cpu.Status.N);
}
