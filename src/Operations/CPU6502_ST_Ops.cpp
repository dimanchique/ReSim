#include "Operations/CPU6502_ST_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_ST_ZP(S32& Cycles, Memory &Memory, CPU6502 &CPU, BYTE& TargetRegister) {
    const BYTE ZeroPageAddress = CPU.FetchByte(Cycles, Memory);
    CPU.WriteByte(Cycles, Memory, TargetRegister, ZeroPageAddress);
}

void CPU6502_ST_ZP(S32& Cycles, Memory &Memory, CPU6502 &CPU, BYTE& TargetRegister, BYTE AffectingRegister){
    const BYTE ZeroPageAddress = CPU.FetchByte(Cycles, Memory) + AffectingRegister;
    CPU.WriteByte(Cycles, Memory, TargetRegister, ZeroPageAddress);
    Cycles--;
}

void CPU6502_ST_ABS(S32& Cycles, Memory &Memory, CPU6502 &CPU, BYTE& TargetRegister) {
    const WORD AbsAddress = CPU.FetchWord(Cycles, Memory);
    CPU.WriteByte(Cycles, Memory, TargetRegister, AbsAddress);
}

void CPU6502_ST_ABS(S32& Cycles, Memory &Memory, CPU6502 &CPU, BYTE& TargetRegister, BYTE AffectingRegister) {
    const WORD AffectedAbsAddress = CPU.FetchWord(Cycles, Memory) + AffectingRegister;
    CPU.WriteByte(Cycles, Memory, TargetRegister, AffectedAbsAddress);
}
