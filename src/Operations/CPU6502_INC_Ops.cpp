#include "Operations/CPU6502_INC_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_INC_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu){
    const BYTE ZeroPageAddress = cpu.FetchByte(cycles, memory);
    BYTE memoryValue = CPU6502::ReadByte(cycles, memory, ZeroPageAddress);
    memoryValue++;
    CPU6502::DoTick(cycles);
    cpu.WriteByte(cycles, memory, memoryValue, ZeroPageAddress);
    cpu.Status.UpdateStatus(memoryValue, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_INC_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu){
    BYTE ZeroPageAddress = cpu.FetchByte(cycles, memory);
    ZeroPageAddress += cpu.X;
    CPU6502::DoTick(cycles);
    BYTE memoryValue = CPU6502::ReadByte(cycles, memory, ZeroPageAddress);
    memoryValue++;
    CPU6502::DoTick(cycles);
    cpu.WriteByte(cycles, memory, memoryValue, ZeroPageAddress);
    cpu.Status.UpdateStatus(memoryValue, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_INC_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu){
    const WORD AbsAddress = cpu.FetchWord(cycles, memory);
    BYTE memoryValue = CPU6502::ReadByte(cycles, memory, AbsAddress);
    memoryValue++;
    CPU6502::DoTick(cycles);
    cpu.WriteByte(cycles, memory, memoryValue, AbsAddress);
    cpu.Status.UpdateStatus(memoryValue, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_INC_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu){
    const WORD AbsAddress = cpu.FetchWord(cycles, memory);
    const WORD AffectedAbsAddress = AbsAddress + cpu.X;
    CPU6502::DoTick(cycles);
    BYTE memoryValue = CPU6502::ReadByte(cycles, memory, AffectedAbsAddress);
    memoryValue++;
    CPU6502::DoTick(cycles);
    cpu.WriteByte(cycles, memory, memoryValue, AffectedAbsAddress);
    cpu.Status.UpdateStatus(memoryValue, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_INX_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu){
    cpu.X++;
    CPU6502::DoTick(cycles);
    cpu.Status.UpdateStatus(cpu.X, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_INY_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu){
    cpu.Y++;
    CPU6502::DoTick(cycles);
    cpu.Status.UpdateStatus(cpu.Y, CPU6502_Status_Z | CPU6502_Status_N);
}
