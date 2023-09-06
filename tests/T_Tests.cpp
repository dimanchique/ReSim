#include "CPU6502_T_Tests.h"

void CPU6502_TFixture::T_IMPL_CanTransferValue(CPU6502_OpCodes OpCode, BYTE& SourceRegister, BYTE& DestinationRegister){
    //given:
    //SourceRegister = 0x2F; <---------------- this value should be loaded by target test
    DestinationRegister = 0x0;
    mem[0xFFFC] = OpCode;

    //when:
    const U32 NumCycles = 2;

    // when:
    U32 CNT = cpu.Run(NumCycles, mem);

    // then:
    EXPECT_EQ(DestinationRegister, SourceRegister);
    EXPECT_EQ(CNT, NumCycles);
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

class CPU6502_TAXFixture : public CPU6502_TFixture{};

TEST_F(CPU6502_TAXFixture, TAX_IMPL_CanTransferValue){
    cpu.A = 0x14;
    T_IMPL_CanTransferValue(TAX_IMPL, cpu.A, cpu.X);
}

TEST_F(CPU6502_TAXFixture, TAX_IMPL_CanAffectNegativeFlag){
    T_IMPL_CanAffectNegativeFlag(TAX_IMPL, cpu.A, cpu.X);
}

TEST_F(CPU6502_TAXFixture, TAX_IMPL_CanAffectZeroFlag){
    T_IMPL_CanAffectZeroFlag(TAX_IMPL, cpu.A, cpu.X);
}

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

class CPU6502_TAYFixture : public CPU6502_TFixture{};

TEST_F(CPU6502_TAYFixture, TAY_IMPL_CanTransferValue){
    cpu.A = 0x14;
    T_IMPL_CanTransferValue(TAY_IMPL, cpu.A, cpu.Y);
}

TEST_F(CPU6502_TAYFixture, TAY_IMPL_CanAffectNegativeFlag){
    T_IMPL_CanAffectNegativeFlag(TAY_IMPL, cpu.A, cpu.Y);
}

TEST_F(CPU6502_TAYFixture, TAY_IMPL_CanAffectZeroFlag){
    T_IMPL_CanAffectZeroFlag(TAY_IMPL, cpu.A, cpu.Y);
}

class CPU6502_TYAFixture : public CPU6502_TFixture{};

TEST_F(CPU6502_TYAFixture, TYA_IMPL_CanTransferValue){
    cpu.Y = 0x14;
    T_IMPL_CanTransferValue(TYA_IMPL, cpu.Y, cpu.A);
}

TEST_F(CPU6502_TYAFixture, TAY_IMPL_CanAffectNegativeFlag){
    T_IMPL_CanAffectNegativeFlag(TYA_IMPL, cpu.Y, cpu.A);
}

TEST_F(CPU6502_TYAFixture, TYA_IMPL_CanAffectZeroFlag){
    T_IMPL_CanAffectZeroFlag(TYA_IMPL, cpu.Y, cpu.A);
}

class CPU6502_TSXFixture : public CPU6502_TFixture{};

TEST_F(CPU6502_TSXFixture, TSX_IMPL_CanTransferValue){
    cpu.SP = 0x14;
    T_IMPL_CanTransferValue(TSX_IMPL, cpu.SP, cpu.X);
}

TEST_F(CPU6502_TSXFixture, TSX_IMPL_CanAffectNegativeFlag){
    T_IMPL_CanAffectNegativeFlag(TSX_IMPL, cpu.SP, cpu.X);
}

TEST_F(CPU6502_TSXFixture, TSX_IMPL_CanAffectZeroFlag){
    T_IMPL_CanAffectZeroFlag(TSX_IMPL, cpu.SP, cpu.X);
}

class CPU6502_TXSFixture : public CPU6502_TFixture{};

TEST_F(CPU6502_TXSFixture, TXS_IMPL_CanTransferValue){
    cpu.X = 0x14;
    T_IMPL_CanTransferValue(TXS_IMPL, cpu.X, cpu.SP);
}
