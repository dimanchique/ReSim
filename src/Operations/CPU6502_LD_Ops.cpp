#include "Operations/CPU6502_LD_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_LD_IM(S32& Cycles, Memory &memory, CPU6502 &cpu, BYTE& TargetRegister) {
    TargetRegister = cpu.FetchByte(Cycles, memory);
    cpu.LoadRegisterSetStatus(TargetRegister);
}

void CPU6502_LD_ZP(S32& Cycles, Memory &memory, CPU6502 &cpu, BYTE& TargetRegister) {
    BYTE ZeroPageAddress = cpu.FetchByte(Cycles, memory);
    TargetRegister = cpu.ReadByte(Cycles, ZeroPageAddress, memory);
    cpu.LoadRegisterSetStatus(TargetRegister);
}

void CPU6502_LD_ABS(S32& Cycles, Memory &memory, CPU6502 &cpu, BYTE& TargetRegister) {
    WORD AbsAddress = cpu.FetchWord(Cycles, memory);
    TargetRegister = cpu.ReadByte(Cycles, AbsAddress, memory);
    cpu.LoadRegisterSetStatus(TargetRegister);
}