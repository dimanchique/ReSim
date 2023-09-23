#include "Operations/CPU6502_LD_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_LD_IM(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE& targetRegister) {
    targetRegister = cpu.FetchByte(cycles, memory);
    cpu.Status.UpdateStatus(targetRegister, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_LD_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE& targetRegister) {
    const BYTE ZeroPageAddress = cpu.FetchByte(cycles, memory);
    targetRegister = CPU6502::ReadByte(cycles, memory, ZeroPageAddress);
    cpu.Status.UpdateStatus(targetRegister, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_LD_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE& targetRegister, BYTE affectingRegister) {
    BYTE ZeroPageAddress = cpu.FetchByte(cycles, memory);
    ZeroPageAddress += affectingRegister;
    CPU6502::DoTick(cycles);
    targetRegister = CPU6502::ReadByte(cycles, memory, ZeroPageAddress);
    cpu.Status.UpdateStatus(targetRegister, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_LD_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE& targetRegister) {
    const WORD AbsAddress = cpu.FetchWord(cycles, memory);
    targetRegister = CPU6502::ReadByte(cycles, memory, AbsAddress);
    cpu.Status.UpdateStatus(targetRegister, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_LD_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE& targetRegister, BYTE affectingRegister) {
    const WORD AbsAddress = cpu.FetchWord(cycles, memory);
    const WORD AffectedAbsAddress = AbsAddress + affectingRegister;
    if(CPU6502::isPageCrossed(AffectedAbsAddress, AbsAddress))
        CPU6502::DoTick(cycles);
    targetRegister = CPU6502::ReadByte(cycles, memory, AffectedAbsAddress);
    cpu.Status.UpdateStatus(targetRegister, CPU6502_Status_Z | CPU6502_Status_N);
}
