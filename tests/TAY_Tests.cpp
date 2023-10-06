#include "CPU6502_T_Tests.h"

class CPU6502_TAYFixture : public CPU6502_TFixture {};

TEST_F(CPU6502_TAYFixture, TAY_IMPL_CanTransferValue) {
    cpu.A = 0x14;
    T_IMPL_CanTransferValue(TAY_IMPL, cpu.A, cpu.Y);
}

TEST_F(CPU6502_TAYFixture, TAY_IMPL_CanAffectNegativeFlag) {
    T_IMPL_CanAffectNegativeFlag(TAY_IMPL, cpu.A, cpu.Y);
}

TEST_F(CPU6502_TAYFixture, TAY_IMPL_CanAffectZeroFlag) {
    T_IMPL_CanAffectZeroFlag(TAY_IMPL, cpu.A, cpu.Y);
}
