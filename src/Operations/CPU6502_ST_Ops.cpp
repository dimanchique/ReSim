#include "Operations/CPU6502_ST_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_ST_ZP(S32& Cycles, Memory &memory, CPU6502 &cpu, BYTE& TargetRegister) {
    BYTE ZeroPageAddress = cpu.FetchByte(Cycles, memory);
    TargetRegister = cpu.ReadByte(Cycles, ZeroPageAddress, memory);
    cpu.LoadRegisterSetStatus(TargetRegister);
}

void CPU6502_ST_ABS(S32& Cycles, Memory &memory, CPU6502 &cpu, BYTE& TargetRegister) {
    WORD AbsAddress = cpu.FetchWord(Cycles, memory);
    TargetRegister = cpu.ReadByte(Cycles, AbsAddress, memory);
    cpu.LoadRegisterSetStatus(TargetRegister);
}