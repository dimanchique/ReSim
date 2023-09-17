#include "CPU6502_T_Tests.h"

class CPU6502_TXAFixture : public CPU6502_TFixture{};

TEST_F(CPU6502_TXAFixture, TXA_IMPL_CanTransferValue){
    cpu.X = 0x14;
    T_IMPL_CanTransferValue(TXA_IMPL, cpu.X, cpu.A);
}

TEST_F(CPU6502_TXAFixture, TXA_IMPL_CanAffectNegativeFlag){
    T_IMPL_CanAffectNegativeFlag(TXA_IMPL, cpu.X, cpu.A);
}

TEST_F(CPU6502_TXAFixture, TXA_IMPL_CanAffectZeroFlag){
    T_IMPL_CanAffectZeroFlag(TXA_IMPL, cpu.X, cpu.A);
}
