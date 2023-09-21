#include "Operations/CPU6502_BIT_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_BIT_ZP(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    const BYTE ZeroPageAddress = CPU.FetchByte(Cycles, Memory);
    BYTE MemoryValue = CPU.ReadByte(Cycles, Memory, ZeroPageAddress);
    BYTE Value = CPU.A & MemoryValue;
    CPU.Status.Z = Value == 0;
    CPU.Status.V = (MemoryValue >> 6) & 1;
    CPU.Status.N = (MemoryValue >> 7) & 1;
}

void CPU6502_BIT_ABS(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    const WORD AbsAddress = CPU.FetchWord(Cycles, Memory);
    BYTE MemoryValue = CPU.ReadByte(Cycles, Memory, AbsAddress);
    BYTE Value = CPU.A & MemoryValue;
    CPU.Status.Z = Value == 0;
    CPU.Status.V = (MemoryValue >> 6) & 1;
    CPU.Status.N = (MemoryValue >> 7) & 1;
}
