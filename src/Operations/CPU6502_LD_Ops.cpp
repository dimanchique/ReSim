#include "Operations/CPU6502_LD_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_LD_IM(S32& Cycles, Memory &Memory, CPU6502 &CPU, BYTE& TargetRegister) {
    TargetRegister = CPU.FetchByte(Cycles, Memory);
    CPU.LoadRegisterSetStatus(TargetRegister);
}

void CPU6502_LD_ZP(S32& Cycles, Memory &Memory, CPU6502 &CPU, BYTE& TargetRegister) {
    const BYTE ZeroPageAddress = CPU.FetchByte(Cycles, Memory);
    TargetRegister = CPU.ReadByte(Cycles, Memory, ZeroPageAddress);
    CPU.LoadRegisterSetStatus(TargetRegister);
}

void CPU6502_LD_ZP(S32& Cycles, Memory &Memory, CPU6502 &CPU, BYTE& TargetRegister, BYTE AffectingRegister) {
    BYTE ZeroPageAddress = CPU.FetchByte(Cycles, Memory);
    ZeroPageAddress += AffectingRegister;
    TargetRegister = CPU.ReadByte(Cycles, Memory, ZeroPageAddress);
    CPU.LoadRegisterSetStatus(TargetRegister);
    Cycles--;
}

void CPU6502_LD_ABS(S32& Cycles, Memory &Memory, CPU6502 &CPU, BYTE& TargetRegister) {
    const WORD AbsAddress = CPU.FetchWord(Cycles, Memory);
    TargetRegister = CPU.ReadByte(Cycles, Memory, AbsAddress);
    CPU.LoadRegisterSetStatus(TargetRegister);
}

void CPU6502_LD_ABS(S32& Cycles, Memory &Memory, CPU6502 &CPU, BYTE& TargetRegister, BYTE AffectingRegister) {
    const WORD AbsAddress = CPU.FetchWord(Cycles, Memory);
    const WORD AffectedAbsAddress = AbsAddress + AffectingRegister;
    TargetRegister = CPU.ReadByte(Cycles, Memory, AffectedAbsAddress);
    if(AffectedAbsAddress - AbsAddress >= 0xFF)
        Cycles--;
    CPU.LoadRegisterSetStatus(TargetRegister);
}
