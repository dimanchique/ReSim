#include "Operations/CPU6502_ST_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_ST_ZP(S32& Cycles, Memory &memory, CPU6502 &cpu, BYTE& TargetRegister) {
    BYTE ZeroPageAddress = cpu.FetchByte(Cycles, memory);
    memory.WriteByte(Cycles, TargetRegister, ZeroPageAddress);
}

void CPU6502_ST_ZP(S32& Cycles, Memory &memory, CPU6502 &cpu, BYTE& TargetRegister, BYTE AffectingRegister){
    BYTE ZeroPageAddress = cpu.FetchByte(Cycles, memory);
    ZeroPageAddress += AffectingRegister;
    Cycles--;
    memory.WriteByte(Cycles, TargetRegister, ZeroPageAddress);
}

void CPU6502_ST_ABS(S32& Cycles, Memory &memory, CPU6502 &cpu, BYTE& TargetRegister) {
    WORD AbsAddress = cpu.FetchWord(Cycles, memory);
    memory.WriteByte(Cycles, TargetRegister, AbsAddress);
}

void CPU6502_ST_ABS(S32& Cycles, Memory &memory, CPU6502 &cpu, BYTE& TargetRegister, BYTE AffectingRegister) {
    WORD AbsAddress = cpu.FetchWord(Cycles, memory);
    WORD AffectedAbsAddress = AbsAddress + AffectingRegister;
    memory.WriteByte(Cycles, TargetRegister, AffectedAbsAddress);
}
