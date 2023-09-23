#include "Operations/CPU6502_CM_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_CM_IM(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE& targetRegister) {
    const BYTE memoryValue = cpu.FetchByte(cycles, memory);
    const BYTE comparedValue = targetRegister - memoryValue;
    cpu.Status.UpdateStatus(comparedValue, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.SetStatusFlagValue(CPU6502_Status_C, targetRegister >= memoryValue);
}

void CPU6502_CM_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE& targetRegister) {
    const BYTE ZeroPageAddress = cpu.FetchByte(cycles, memory);
    const BYTE memoryValue = CPU6502::ReadByte(cycles, memory, ZeroPageAddress);
    const BYTE comparedValue = targetRegister - memoryValue;
    cpu.Status.UpdateStatus(comparedValue, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.SetStatusFlagValue(CPU6502_Status_C, targetRegister >= memoryValue);
}

void CPU6502_CM_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE& targetRegister, BYTE affectingRegister) {
    BYTE ZeroPageAddress = cpu.FetchByte(cycles, memory);
    ZeroPageAddress += affectingRegister;
    CPU6502::DoTick(cycles);
    const BYTE memoryValue = CPU6502::ReadByte(cycles, memory, ZeroPageAddress);
    const BYTE comparedValue = targetRegister - memoryValue;
    cpu.Status.UpdateStatus(comparedValue, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.SetStatusFlagValue(CPU6502_Status_C, targetRegister >= memoryValue);
}

void CPU6502_CM_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE& targetRegister) {
    const WORD AbsAddress = cpu.FetchWord(cycles, memory);
    const BYTE memoryValue = CPU6502::ReadByte(cycles, memory, AbsAddress);
    const BYTE comparedValue = targetRegister - memoryValue;
    cpu.Status.UpdateStatus(comparedValue, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.SetStatusFlagValue(CPU6502_Status_C, targetRegister >= memoryValue);
}

void CPU6502_CM_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE& targetRegister, BYTE affectingRegister) {
    const WORD AbsAddress = cpu.FetchWord(cycles, memory);
    const WORD AffectedAbsAddress = AbsAddress + affectingRegister;
    if(CPU6502::isPageCrossed(AffectedAbsAddress, AbsAddress))
        CPU6502::DoTick(cycles);
    const BYTE memoryValue = CPU6502::ReadByte(cycles, memory, AffectedAbsAddress);
    const BYTE comparedValue = targetRegister - memoryValue;
    cpu.Status.UpdateStatus(comparedValue, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.SetStatusFlagValue(CPU6502_Status_C, targetRegister >= memoryValue);
}
