#include "CPU6502_ST_Tests.h"

class CPU6502_STYFixture : public CPU6502_STFixture{};

TEST_F(CPU6502_STYFixture, STY_ZP_CanStoreValue){
    ST_ZP_CanStoreValue(STY_ZP, cpu.Y);
}

TEST_F(CPU6502_STYFixture, STY_ZPX_CanStoreValue){
    cpu.X = 0x0F;
    ST_ZP_CanStoreValue(STY_ZPX, cpu.Y, cpu.X);
}

TEST_F(CPU6502_STYFixture, STY_ABS_CanStoreValue){
    ST_ABS_CanStoreValue(STY_ABS, cpu.Y);
}
