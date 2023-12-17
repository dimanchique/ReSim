#include "MOS6502_T_Tests.h"

class MOS6502_TYAFixture : public MOS6502_TFixture {};

TEST_F(MOS6502_TYAFixture, TYA_IMPL_CanTransferValue) {
    cpu.Y = 0x14;
    T_IMPL_CanTransferValue(TYA_IMPL, cpu.Y, cpu.A);
}

TEST_F(MOS6502_TYAFixture, TAY_IMPL_CanAffectNegativeFlag) {
    T_IMPL_CanAffectNegativeFlag(TYA_IMPL, cpu.Y, cpu.A);
}

TEST_F(MOS6502_TYAFixture, TYA_IMPL_CanAffectZeroFlag) {
    T_IMPL_CanAffectZeroFlag(TYA_IMPL, cpu.Y, cpu.A);
}
