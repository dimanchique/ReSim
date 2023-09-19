#include "Operations/CPU6502_EOR_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_EOR_IM(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU.A ^= CPU.FetchByte(Cycles, Memory);
    CPU.SetStatusValue(CPU.A, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_EOR_ZP(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    const BYTE ZeroPageAddress = CPU.FetchByte(Cycles, Memory);
    CPU.A ^= CPU.ReadByte(Cycles, Memory, ZeroPageAddress);
    CPU.SetStatusValue(CPU.A, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_EOR_ZPX(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    BYTE ZeroPageAddress = CPU.FetchByte(Cycles, Memory);
    ZeroPageAddress += CPU.X;
    CPU6502::DoTick(Cycles);
    CPU.A ^= CPU.ReadByte(Cycles, Memory, ZeroPageAddress);
    CPU.SetStatusValue(CPU.A, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_EOR_ABS(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    const WORD AbsAddress = CPU.FetchWord(Cycles, Memory);
    CPU.A ^= CPU.ReadByte(Cycles, Memory, AbsAddress);
    CPU.SetStatusValue(CPU.A, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_EOR_ABS(U32 &Cycles, Memory &Memory, CPU6502 &CPU, BYTE AffectingRegister) {
    const WORD AbsAddress = CPU.FetchWord(Cycles, Memory);
    const WORD AffectedAbsAddress = AbsAddress + AffectingRegister;
    if(AffectedAbsAddress - AbsAddress >= 0xFF)
        CPU6502::DoTick(Cycles);
    CPU.A ^= CPU.ReadByte(Cycles, Memory, AffectedAbsAddress);
    CPU.SetStatusValue(CPU.A, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_EOR_ABSX(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_EOR_ABS(Cycles, Memory, CPU, CPU.X);
}

void CPU6502_EOR_ABSY(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_EOR_ABS(Cycles, Memory, CPU, CPU.Y);
}


void CPU6502_EOR_INDX(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    BYTE ZeroPageAddress = CPU.FetchByte(Cycles, Memory) + CPU.X;
    const WORD EffectiveAddress = CPU.ReadWord(Cycles, Memory, ZeroPageAddress);
    CPU.A ^= CPU.ReadByte(Cycles, Memory, EffectiveAddress);
    CPU.SetStatusValue(CPU.A, CPU6502_Status_Z | CPU6502_Status_N);
    CPU6502::DoTick(Cycles);
}

void CPU6502_EOR_INDY(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    BYTE ZeroPageAddress = CPU.FetchByte(Cycles, Memory);
    const WORD EffectiveAddress = CPU.ReadWord(Cycles, Memory, ZeroPageAddress);
    const WORD EffectiveAddressY = EffectiveAddress + CPU.Y;
    CPU.A ^= CPU.ReadByte(Cycles, Memory, EffectiveAddressY);
    if(EffectiveAddressY - EffectiveAddress >= 0xFF)
        CPU6502::DoTick(Cycles);
    CPU.SetStatusValue(CPU.A, CPU6502_Status_Z | CPU6502_Status_N);
}
