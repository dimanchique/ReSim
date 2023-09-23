#include "Operations/CPU6502_ST_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_ST_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE& targetRegister) {
    const BYTE ZeroPageAddress = cpu.FetchByte(cycles, memory);
    CPU6502::WriteByte(cycles, memory, targetRegister, ZeroPageAddress);
}

void CPU6502_ST_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE& targetRegister, BYTE affectingRegister){
    const BYTE ZeroPageAddress = cpu.FetchByte(cycles, memory);
    const BYTE AffectedZeroPage = ZeroPageAddress + affectingRegister;
    CPU6502::DoTick(cycles);
    CPU6502::WriteByte(cycles, memory, targetRegister, AffectedZeroPage);
}

void CPU6502_ST_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE& targetRegister) {
    const WORD AbsAddress = cpu.FetchWord(cycles, memory);
    CPU6502::WriteByte(cycles, memory, targetRegister, AbsAddress);
}

void CPU6502_ST_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE& targetRegister, BYTE affectingRegister) {
    WORD AbsAddress = cpu.FetchWord(cycles, memory);
    AbsAddress = AbsAddress + affectingRegister;
    CPU6502::DoTick(cycles);
    CPU6502::WriteByte(cycles, memory, targetRegister, AbsAddress);
}
