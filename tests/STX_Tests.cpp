#include "CPU6502_ST_Tests.h"

class CPU6502_STXFixture : public CPU6502_STFixture{};

TEST_F(CPU6502_STXFixture, STX_ZP_CanStoreValue){
    ST_ZP_CanStoreValue(STX_ZP, cpu.X);
}

TEST_F(CPU6502_STXFixture, STX_ZPY_CanStoreValue){
    cpu.Y = 0x0F;
    ST_ZP_CanStoreValue(STX_ZPY, cpu.X, cpu.Y);
}

TEST_F(CPU6502_STXFixture, STX_ABS_CanStoreValue){
    ST_ABS_CanStoreValue(STX_ABS, cpu.X);
}
