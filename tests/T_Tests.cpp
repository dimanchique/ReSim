#include "CPU6502_T_Tests.h"

void CPU6502_TFixture::T_IMPL_CanTransferValue(CPU6502_OpCodes OpCode, BYTE& SourceRegister, BYTE& DestinationRegister){
    //given:
    DestinationRegister = 0x0;
    mem[0xFFFC] = OpCode;

    CyclesExpected = 2;

    // when:
    CyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(DestinationRegister, SourceRegister);
    CheckCyclesCount();
}

void CPU6502_TFixture::T_IMPL_CanAffectNegativeFlag(CPU6502_OpCodes OpCode, BYTE& SourceRegister, BYTE& DestinationRegister){
    SourceRegister = 0x80;
    T_IMPL_CanTransferValue(OpCode, SourceRegister, DestinationRegister);
    EXPECT_TRUE(cpu.Status.N);
}

void CPU6502_TFixture::T_IMPL_CanAffectZeroFlag(CPU6502_OpCodes OpCode, BYTE& SourceRegister, BYTE& DestinationRegister){
    SourceRegister = 0x0;
    T_IMPL_CanTransferValue(OpCode, SourceRegister, DestinationRegister);
    EXPECT_TRUE(cpu.Status.Z);
}
