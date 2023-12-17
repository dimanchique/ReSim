#include "MOS6502_T_Tests.h"

class MOS6502_TXSFixture : public MOS6502_TFixture {};

TEST_F(MOS6502_TXSFixture, TXS_IMPL_CanTransferValue) {
    cpu.X = 0x14;
    T_IMPL_CanTransferValue(TXS_IMPL, cpu.X, cpu.SP);
}
