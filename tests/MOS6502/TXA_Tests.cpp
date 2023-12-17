#include "MOS6502_T_Tests.h"

class MOS6502_TXAFixture : public MOS6502_TFixture {};

TEST_F(MOS6502_TXAFixture, TXA_IMPL_CanTransferValue) {
    cpu.X = 0x14;
    T_IMPL_CanTransferValue(TXA_IMPL, cpu.X, cpu.A);
}

TEST_F(MOS6502_TXAFixture, TXA_IMPL_CanAffectNegativeFlag) {
    T_IMPL_CanAffectNegativeFlag(TXA_IMPL, cpu.X, cpu.A);
}

TEST_F(MOS6502_TXAFixture, TXA_IMPL_CanAffectZeroFlag) {
    T_IMPL_CanAffectZeroFlag(TXA_IMPL, cpu.X, cpu.A);
}
