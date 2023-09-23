#include "CPU6502_T_Tests.h"

void CPU6502_TFixture::T_IMPL_CanTransferValue(CPU6502_OpCodes opcode, BYTE& sourceRegister, BYTE& destinationRegister){
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

void CPU6502_TFixture::T_IMPL_CanAffectNegativeFlag(CPU6502_OpCodes opcode, BYTE& sourceRegister, BYTE& destinationRegister){
    sourceRegister = 0x80;
    T_IMPL_CanTransferValue(opcode, sourceRegister, destinationRegister);
    EXPECT_TRUE(cpu.Status.N);
}

void CPU6502_TFixture::T_IMPL_CanAffectZeroFlag(CPU6502_OpCodes opcode, BYTE& sourceRegister, BYTE& destinationRegister){
    sourceRegister = 0x0;
    T_IMPL_CanTransferValue(opcode, sourceRegister, destinationRegister);
    EXPECT_TRUE(cpu.Status.Z);
}
