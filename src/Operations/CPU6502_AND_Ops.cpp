#include "Operations/CPU6502_AND_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_AND_IM(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    cpu.A &= cpu.FetchByte(cycles, memory);
    cpu.Status.UpdateStatus(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_AND_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE ZeroPageAddress = cpu.FetchByte(cycles, memory);
    cpu.A &= CPU6502::ReadByte(cycles, memory, ZeroPageAddress);
    cpu.Status.UpdateStatus(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_AND_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    BYTE ZeroPageAddress = cpu.FetchByte(cycles, memory);
    ZeroPageAddress += cpu.X;
    CPU6502::DoTick(cycles);
    cpu.A &= CPU6502::ReadByte(cycles, memory, ZeroPageAddress);
    cpu.Status.UpdateStatus(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_AND_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const WORD AbsAddress = cpu.FetchWord(cycles, memory);
    cpu.A &= CPU6502::ReadByte(cycles, memory, AbsAddress);
    cpu.Status.UpdateStatus(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_AND_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE affectingRegister) {
    const WORD AbsAddress = cpu.FetchWord(cycles, memory);
    const WORD AffectedAbsAddress = AbsAddress + affectingRegister;
    if(CPU6502::isPageCrossed(AffectedAbsAddress, AbsAddress))
        CPU6502::DoTick(cycles);
    cpu.A &= CPU6502::ReadByte(cycles, memory, AffectedAbsAddress);
    cpu.Status.UpdateStatus(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_AND_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_AND_ABS(cycles, memory, cpu, cpu.X);
}

void CPU6502_AND_ABSY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_AND_ABS(cycles, memory, cpu, cpu.Y);
}


void CPU6502_AND_INDX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    BYTE ZeroPageAddress = cpu.FetchByte(cycles, memory) + cpu.X;
    const WORD EffectiveAddress = CPU6502::ReadWord(cycles, memory, ZeroPageAddress);
    cpu.A &= CPU6502::ReadByte(cycles, memory, EffectiveAddress);
    cpu.Status.UpdateStatus(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
    CPU6502::DoTick(cycles);
}

void CPU6502_AND_INDY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    BYTE ZeroPageAddress = cpu.FetchByte(cycles, memory);
    const WORD EffectiveAddress = CPU6502::ReadWord(cycles, memory, ZeroPageAddress);
    const WORD EffectiveAddressY = EffectiveAddress + cpu.Y;
    cpu.A &= CPU6502::ReadByte(cycles, memory, EffectiveAddressY);
    if(CPU6502::isPageCrossed(EffectiveAddressY, EffectiveAddress))
        CPU6502::DoTick(cycles);
    cpu.Status.UpdateStatus(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
}
