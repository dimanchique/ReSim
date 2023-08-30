#include "Operations/CPU6502_ST_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_ST_ZP(S32& Cycles, Memory &memory, CPU6502 &cpu, BYTE& TargetRegister) {
    BYTE ZeroPageAddress = cpu.FetchByte(Cycles, memory);
    cpu.WriteByte(Cycles, TargetRegister, ZeroPageAddress, memory);
}

void CPU6502_ST_ZP(S32& Cycles, Memory &memory, CPU6502 &cpu, BYTE& TargetRegister, BYTE AffectingRegister){
    BYTE ZeroPageAddress = cpu.FetchByte(Cycles, memory);
    ZeroPageAddress += AffectingRegister;
    Cycles--;
    cpu.WriteByte(Cycles, TargetRegister, ZeroPageAddress, memory);
}

void CPU6502_ST_ABS(S32& Cycles, Memory &memory, CPU6502 &cpu, BYTE& TargetRegister) {
    WORD AbsAddress = cpu.FetchWord(Cycles, memory);
    cpu.WriteByte(Cycles, TargetRegister, AbsAddress, memory);
}

void CPU6502_ST_ABS(S32& Cycles, Memory &memory, CPU6502 &cpu, BYTE& TargetRegister, BYTE AffectingRegister) {
    WORD AbsAddress = cpu.FetchWord(Cycles, memory);
    WORD AffectedAbsAddress = AbsAddress + AffectingRegister;
    cpu.WriteByte(Cycles, TargetRegister, AffectedAbsAddress, memory);
}