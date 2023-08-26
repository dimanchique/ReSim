#include "CPU6502_LD_Tests.h"

class CPU6502_LDXFixture : public CPU6502_LDFixture{};

TEST_F(CPU6502_LDXFixture, LDX_IM_CanLoadValue){
    LD_IM_CanLoadValue(CPU6502_OpCodes::LDX_IM, cpu.X);
}

TEST_F(CPU6502_LDXFixture, LDX_IM_CanAffectZeroFlag){
    LD_IM_CanAffectZeroFlag(CPU6502_OpCodes::LDX_IM);
}

TEST_F(CPU6502_LDXFixture, LDX_IM_CanAffectNegativeFlag){
    LD_IM_CanAffectNegativeFlag(CPU6502_OpCodes::LDX_IM);
}

TEST_F(CPU6502_LDXFixture, LDX_ZP_CanLoadValue){
    LD_ZP_CanLoadValue(CPU6502_OpCodes::LDX_ZP, cpu.X);
}

TEST_F(CPU6502_LDXFixture, LDX_ZPY_CanLoadValue){
    cpu.Y = 0x5;
    LD_ZP_CanLoadValue(CPU6502_OpCodes::LDX_ZPY, cpu.X, cpu.Y);
}

TEST_F(CPU6502_LDXFixture, LDX_ZPY_CanLoadValue_WithWrap){
    cpu.Y = 0xFF;
    LD_ZP_CanLoadValue(CPU6502_OpCodes::LDX_ZPY, cpu.X, cpu.Y);
}

TEST_F(CPU6502_LDXFixture, LDX_ABS_CanLoadValue){
    LD_ABS_CanLoadValue(CPU6502_OpCodes::LDX_ABS, cpu.X);
}

TEST_F(CPU6502_LDXFixture, LDX_ABSY_CanLoadValue){
    cpu.Y = 0x01;
    LD_ABS_CanLoadValue(CPU6502_OpCodes::LDX_ABSY, cpu.X, cpu.Y);
}

TEST_F(CPU6502_LDXFixture, LDX_ABSY_CanLoadValue_WithExtraCycleOnPageCrossing){
    cpu.Y = 0xFF;
    LD_ABS_CanLoadValue(CPU6502_OpCodes::LDX_ABSY, cpu.X, cpu.Y);
}
