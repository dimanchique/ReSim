#include "MOS6502_T_Tests.h"

class MOS6502_TSXFixture : public MOS6502_TFixture {};

TEST_F(MOS6502_TSXFixture, TSX_IMPL_CanTransferValue) {
    cpu.SP = 0x14;
    T_IMPL_CanTransferValue(TSX_IMPL, cpu.SP, cpu.X);
}

TEST_F(MOS6502_TSXFixture, TSX_IMPL_CanAffectNegativeFlag) {
    T_IMPL_CanAffectNegativeFlag(TSX_IMPL, cpu.SP, cpu.X);
}

TEST_F(MOS6502_TSXFixture, TSX_IMPL_CanAffectZeroFlag) {
    T_IMPL_CanAffectZeroFlag(TSX_IMPL, cpu.SP, cpu.X);
}
