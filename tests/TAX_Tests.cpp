#include "CPU6502_T_Tests.h"

class CPU6502_TAXFixture : public CPU6502_TFixture {};

TEST_F(CPU6502_TAXFixture, TAX_IMPL_CanTransferValue) {
    cpu.A = 0x14;
    T_IMPL_CanTransferValue(TAX_IMPL, cpu.A, cpu.X);
}

TEST_F(CPU6502_TAXFixture, TAX_IMPL_CanAffectNegativeFlag) {
    T_IMPL_CanAffectNegativeFlag(TAX_IMPL, cpu.A, cpu.X);
}

TEST_F(CPU6502_TAXFixture, TAX_IMPL_CanAffectZeroFlag) {
    T_IMPL_CanAffectZeroFlag(TAX_IMPL, cpu.A, cpu.X);
}
