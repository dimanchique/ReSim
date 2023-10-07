#include "CPU6502_T_Tests.h"

class CPU6502_TXSFixture : public CPU6502_TFixture {};

TEST_F(CPU6502_TXSFixture, TXS_IMPL_CanTransferValue) {
    cpu.X = 0x14;
    T_IMPL_CanTransferValue(TXS_IMPL, cpu.X, cpu.SP);
}
