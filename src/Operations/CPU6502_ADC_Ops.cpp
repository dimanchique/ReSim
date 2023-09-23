#include "Operations/CPU6502_ADC_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void FinishSumOperation(CPU6502 &cpu, const BYTE Operand){
    const bool AreSignBitsTheSame = !((cpu.A ^ Operand) & CPU6502_Status_N);
    WORD Sum = cpu.A + Operand + cpu.Status.C;
    cpu.A = Sum;
    cpu.Status.UpdateStatus(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.SetStatusFlagValue(CPU6502_Status_C, Sum > 0xFF);
    cpu.Status.SetStatusFlagValue(CPU6502_Status_V, AreSignBitsTheSame && ((cpu.A ^ Operand) & CPU6502_Status_N));
}

void CPU6502_ADC_IM(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Operand = cpu.FetchByte(cycles, memory);
    FinishSumOperation(cpu, Operand);
}

void CPU6502_ADC_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE ZeroPageAddress = cpu.FetchByte(cycles, memory);
    const BYTE Operand = CPU6502::ReadByte(cycles, memory, ZeroPageAddress);
    FinishSumOperation(cpu, Operand);
}

void CPU6502_ADC_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    BYTE ZeroPageAddress = cpu.FetchByte(cycles, memory);
    ZeroPageAddress += cpu.X;
    CPU6502::DoTick(cycles);
    const BYTE Operand = CPU6502::ReadByte(cycles, memory, ZeroPageAddress);
    FinishSumOperation(cpu, Operand);
}

void CPU6502_ADC_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const WORD AbsAddress = cpu.FetchWord(cycles, memory);
    const BYTE Operand = CPU6502::ReadByte(cycles, memory, AbsAddress);
    FinishSumOperation(cpu, Operand);
}

void CPU6502_ADC_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE affectingRegister) {
    const WORD AbsAddress = cpu.FetchWord(cycles, memory);
    const WORD AffectedAbsAddress = AbsAddress + affectingRegister;
    if(CPU6502::isPageCrossed(AffectedAbsAddress, AbsAddress))
        CPU6502::DoTick(cycles);
    const BYTE Operand = CPU6502::ReadByte(cycles, memory, AffectedAbsAddress);
    FinishSumOperation(cpu, Operand);
}

void CPU6502_ADC_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_ADC_ABS(cycles, memory, cpu, cpu.X);
}

void CPU6502_ADC_ABSY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_ADC_ABS(cycles, memory, cpu, cpu.Y);
}


void CPU6502_ADC_INDX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    BYTE ZeroPageAddress = cpu.FetchByte(cycles, memory) + cpu.X;
    CPU6502::DoTick(cycles);
    const WORD EffectiveAddress = CPU6502::ReadWord(cycles, memory, ZeroPageAddress);
    const BYTE Operand = CPU6502::ReadByte(cycles, memory, EffectiveAddress);
    FinishSumOperation(cpu, Operand);
}

void CPU6502_ADC_INDY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    BYTE ZeroPageAddress = cpu.FetchByte(cycles, memory);
    const WORD EffectiveAddress = CPU6502::ReadWord(cycles, memory, ZeroPageAddress);
    const WORD EffectiveAddressY = EffectiveAddress + cpu.Y;
    const BYTE Operand = CPU6502::ReadByte(cycles, memory, EffectiveAddressY);
    if(CPU6502::isPageCrossed(EffectiveAddressY, EffectiveAddress))
        CPU6502::DoTick(cycles);
    FinishSumOperation(cpu, Operand);
}
