#include "MOS6502_T_Tests.h"

class MOS6502_TSXFixture : public MOS6502_TFixture {};

TEST_F(MOS6502_TSXFixture, TSX_IMPL_CanTransferValue) {
    T_IMPL_CanTransferValue(TSX_IMPL, cpu.SP, cpu.X);
}
