#include "Operations/CPU6502_BIT_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_BIT_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE ZeroPageAddress = cpu.FetchByte(cycles, memory);
    BYTE memoryValue = CPU6502::ReadByte(cycles, memory, ZeroPageAddress);
    BYTE value = cpu.A & memoryValue;
    cpu.Status.Z = value == 0;
    cpu.Status.V = (memoryValue >> 6) & 1;
    cpu.Status.N = (memoryValue >> 7) & 1;
}

void CPU6502_BIT_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const WORD AbsAddress = cpu.FetchWord(cycles, memory);
    BYTE memoryValue = CPU6502::ReadByte(cycles, memory, AbsAddress);
    BYTE value = cpu.A & memoryValue;
    cpu.Status.Z = value == 0;
    cpu.Status.V = (memoryValue >> 6) & 1;
    cpu.Status.N = (memoryValue >> 7) & 1;
}
