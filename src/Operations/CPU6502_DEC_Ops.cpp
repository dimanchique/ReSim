#include "Operations/CPU6502_DEC_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_DEC_ZP(U32 &Cycles, Memory &Memory, CPU6502 &CPU){
    const BYTE ZeroPageAddress = CPU.FetchByte(Cycles, Memory);
    BYTE MemoryValue = CPU.ReadByte(Cycles, Memory, ZeroPageAddress);
    MemoryValue--;
    CPU6502::DoTick(Cycles);
    CPU.WriteByte(Cycles, Memory, MemoryValue, ZeroPageAddress);
    CPU.SetStatusValue(MemoryValue, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_DEC_ZPX(U32 &Cycles, Memory &Memory, CPU6502 &CPU){
    BYTE ZeroPageAddress = CPU.FetchByte(Cycles, Memory);
    ZeroPageAddress += CPU.X;
    CPU6502::DoTick(Cycles);
    BYTE MemoryValue = CPU.ReadByte(Cycles, Memory, ZeroPageAddress);
    MemoryValue--;
    CPU6502::DoTick(Cycles);
    CPU.WriteByte(Cycles, Memory, MemoryValue, ZeroPageAddress);
    CPU.SetStatusValue(MemoryValue, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_DEC_ABS(U32 &Cycles, Memory &Memory, CPU6502 &CPU){
    const WORD AbsAddress = CPU.FetchWord(Cycles, Memory);
    BYTE MemoryValue = CPU.ReadByte(Cycles, Memory, AbsAddress);
    MemoryValue--;
    CPU6502::DoTick(Cycles);
    CPU.WriteByte(Cycles, Memory, MemoryValue, AbsAddress);
    CPU.SetStatusValue(MemoryValue, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_DEC_ABSX(U32 &Cycles, Memory &Memory, CPU6502 &CPU){
    const WORD AbsAddress = CPU.FetchWord(Cycles, Memory);
    const WORD AffectedAbsAddress = AbsAddress + CPU.X;
    CPU6502::DoTick(Cycles);
    BYTE MemoryValue = CPU.ReadByte(Cycles, Memory, AffectedAbsAddress);
    MemoryValue--;
    CPU6502::DoTick(Cycles);
    CPU.WriteByte(Cycles, Memory, MemoryValue, AffectedAbsAddress);
    CPU.SetStatusValue(MemoryValue, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_DEX_IMPL(U32 &Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.X--;
    CPU6502::DoTick(Cycles);
    CPU.SetStatusValue(CPU.X, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_DEY_IMPL(U32 &Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.Y--;
    CPU6502::DoTick(Cycles);
    CPU.SetStatusValue(CPU.Y, CPU6502_Status_Z | CPU6502_Status_N);
}
