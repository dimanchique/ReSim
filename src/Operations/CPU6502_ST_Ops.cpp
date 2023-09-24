#include "Operations/CPU6502_ST_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_ST_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE &targetRegister) {
    const BYTE TargetAddress = cpu.GetZeroPageAddress(cycles, memory);
    CPU6502::WriteByte(cycles, memory, targetRegister, TargetAddress);
}

void CPU6502_ST_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE &targetRegister, BYTE affectingRegister) {
    const BYTE TargetAddress = cpu.GetZeroPageAddress(cycles, memory, affectingRegister);
    CPU6502::WriteByte(cycles, memory, targetRegister, TargetAddress);
}

void CPU6502_ST_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE &targetRegister) {
    const WORD TargetAddress = cpu.GetAbsAddress(cycles, memory);
    CPU6502::WriteByte(cycles, memory, targetRegister, TargetAddress);
}

void CPU6502_ST_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE &targetRegister, BYTE affectingRegister) {
    const WORD TargetAddress = cpu.GetAbsAddress(cycles, memory, affectingRegister);
    CPU6502::WriteByte(cycles, memory, targetRegister, TargetAddress);
    CPU6502::DoTick(cycles); // extra cycle required
}
