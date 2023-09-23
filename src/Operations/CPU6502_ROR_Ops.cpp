#include "Operations/CPU6502_ROR_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_ROR_ACC(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const bool Carry = cpu.A & 1;
    cpu.A >>= 1;
    cpu.A |= cpu.Status.C << 7;
    CPU6502::DoTick(cycles);
    cpu.Status.UpdateStatus(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.C = Carry;
}

void CPU6502_ROR_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE ZeroPageAddress = cpu.FetchByte(cycles, memory);
    auto memoryValue = CPU6502::ReadByte(cycles, memory, ZeroPageAddress);
    const bool Carry = memoryValue & 1;
    memoryValue >>= 1;
    memoryValue |= cpu.Status.C << 7;
    CPU6502::DoTick(cycles);
    cpu.WriteByte(cycles, memory, memoryValue, ZeroPageAddress);
    cpu.Status.UpdateStatus(memoryValue, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.C = Carry;
}

void CPU6502_ROR_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    BYTE ZeroPageAddress = cpu.FetchByte(cycles, memory);
    ZeroPageAddress += cpu.X;
    CPU6502::DoTick(cycles);
    auto memoryValue = CPU6502::ReadByte(cycles, memory, ZeroPageAddress);
    const bool Carry = memoryValue & 1;
    memoryValue >>= 1;
    memoryValue |= cpu.Status.C << 7;
    CPU6502::DoTick(cycles);
    cpu.WriteByte(cycles, memory, memoryValue, ZeroPageAddress);
    cpu.Status.UpdateStatus(memoryValue, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.C = Carry;
}

void CPU6502_ROR_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const WORD AbsAddress = cpu.FetchWord(cycles, memory);
    auto memoryValue = CPU6502::ReadByte(cycles, memory, AbsAddress);
    const bool Carry = memoryValue & 1;
    memoryValue >>= 1;
    memoryValue |= cpu.Status.C << 7;
    CPU6502::DoTick(cycles);
    cpu.WriteByte(cycles, memory, memoryValue, AbsAddress);
    cpu.Status.UpdateStatus(memoryValue, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.C = Carry;
}

void CPU6502_ROR_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE affectingRegister) {
    const WORD AbsAddress = cpu.FetchWord(cycles, memory);
    const WORD AffectedAbsAddress = AbsAddress + affectingRegister;
    auto memoryValue = CPU6502::ReadByte(cycles, memory, AffectedAbsAddress);
    const bool Carry = memoryValue & 1;
    memoryValue >>= 1;
    memoryValue |= cpu.Status.C << 7;
    CPU6502::DoTick(cycles);
    cpu.WriteByte(cycles, memory, memoryValue, AffectedAbsAddress);
    cpu.Status.UpdateStatus(memoryValue, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.C = Carry;
}

void CPU6502_ROR_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_ROR_ABS(cycles, memory, cpu, cpu.X);
    CPU6502::DoTick(cycles);
}
