#include "Operations/CPU6502_LD_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_LD_IM(U32 &Cycles, Memory &Memory, CPU6502 &CPU, BYTE& TargetRegister) {
    TargetRegister = CPU.FetchByte(Cycles, Memory);
    CPU.Status.UpdateStatus(TargetRegister, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_LD_ZP(U32 &Cycles, Memory &Memory, CPU6502 &CPU, BYTE& TargetRegister) {
    const BYTE ZeroPageAddress = CPU.FetchByte(Cycles, Memory);
    TargetRegister = CPU6502::ReadByte(Cycles, Memory, ZeroPageAddress);
    CPU.Status.UpdateStatus(TargetRegister, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_LD_ZP(U32 &Cycles, Memory &Memory, CPU6502 &CPU, BYTE& TargetRegister, BYTE AffectingRegister) {
    BYTE ZeroPageAddress = CPU.FetchByte(Cycles, Memory);
    ZeroPageAddress += AffectingRegister;
    CPU6502::DoTick(Cycles);
    TargetRegister = CPU6502::ReadByte(Cycles, Memory, ZeroPageAddress);
    CPU.Status.UpdateStatus(TargetRegister, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_LD_ABS(U32 &Cycles, Memory &Memory, CPU6502 &CPU, BYTE& TargetRegister) {
    const WORD AbsAddress = CPU.FetchWord(Cycles, Memory);
    TargetRegister = CPU6502::ReadByte(Cycles, Memory, AbsAddress);
    CPU.Status.UpdateStatus(TargetRegister, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_LD_ABS(U32 &Cycles, Memory &Memory, CPU6502 &CPU, BYTE& TargetRegister, BYTE AffectingRegister) {
    const WORD AbsAddress = CPU.FetchWord(Cycles, Memory);
    const WORD AffectedAbsAddress = AbsAddress + AffectingRegister;
    if(CPU6502::isPageCrossed(AffectedAbsAddress, AbsAddress))
        CPU6502::DoTick(Cycles);
    TargetRegister = CPU6502::ReadByte(Cycles, Memory, AffectedAbsAddress);
    CPU.Status.UpdateStatus(TargetRegister, CPU6502_Status_Z | CPU6502_Status_N);
}
