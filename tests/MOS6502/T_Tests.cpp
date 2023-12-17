#include "MOS6502_T_Tests.h"

void MOS6502_TFixture::T_IMPL_CanTransferValue(MOS6502_OpCodes opcode, BYTE &sourceRegister, BYTE &destinationRegister) {
    //given:
    destinationRegister = 0x0;
    mem[0xFFFC] = opcode;

    cyclesExpected = 2;

    // when:
    cyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(destinationRegister, sourceRegister);
    CheckCyclesCount();
}

void MOS6502_TFixture::T_IMPL_CanAffectNegativeFlag(MOS6502_OpCodes opcode, BYTE &sourceRegister, BYTE &destinationRegister) {
    sourceRegister = 0x80;
    T_IMPL_CanTransferValue(opcode, sourceRegister, destinationRegister);
    EXPECT_TRUE(cpu.Status.N);
}

void MOS6502_TFixture::T_IMPL_CanAffectZeroFlag(MOS6502_OpCodes opcode, BYTE &sourceRegister, BYTE &destinationRegister) {
    sourceRegister = 0x0;
    T_IMPL_CanTransferValue(opcode, sourceRegister, destinationRegister);
    EXPECT_TRUE(cpu.Status.Z);
}
