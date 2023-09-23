#include "Operations/CPU6502_ROR_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_ROR_ACC(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    const bool Carry = CPU.A & 1;
    CPU.A >>= 1;
    CPU.A |= CPU.Status.C << 7;
    CPU6502::DoTick(Cycles);
    CPU.Status.UpdateStatus(CPU.A, CPU6502_Status_Z | CPU6502_Status_N);
    CPU.Status.C = Carry;
}

void CPU6502_ROR_ZP(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    const BYTE ZeroPageAddress = CPU.FetchByte(Cycles, Memory);
    auto MemoryValue = CPU.ReadByte(Cycles, Memory, ZeroPageAddress);
    const bool Carry = MemoryValue & 1;
    MemoryValue >>= 1;
    MemoryValue |= CPU.Status.C << 7;
    CPU6502::DoTick(Cycles);
    CPU.WriteByte(Cycles, Memory, MemoryValue, ZeroPageAddress);
    CPU.Status.UpdateStatus(MemoryValue, CPU6502_Status_Z | CPU6502_Status_N);
    CPU.Status.C = Carry;
}

void CPU6502_ROR_ZPX(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    BYTE ZeroPageAddress = CPU.FetchByte(Cycles, Memory);
    ZeroPageAddress += CPU.X;
    CPU6502::DoTick(Cycles);
    auto MemoryValue = CPU.ReadByte(Cycles, Memory, ZeroPageAddress);
    const bool Carry = MemoryValue & 1;
    MemoryValue >>= 1;
    MemoryValue |= CPU.Status.C << 7;
    CPU6502::DoTick(Cycles);
    CPU.WriteByte(Cycles, Memory, MemoryValue, ZeroPageAddress);
    CPU.Status.UpdateStatus(MemoryValue, CPU6502_Status_Z | CPU6502_Status_N);
    CPU.Status.C = Carry;
}

void CPU6502_ROR_ABS(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    const WORD AbsAddress = CPU.FetchWord(Cycles, Memory);
    auto MemoryValue = CPU.ReadByte(Cycles, Memory, AbsAddress);
    const bool Carry = MemoryValue & 1;
    MemoryValue >>= 1;
    MemoryValue |= CPU.Status.C << 7;
    CPU6502::DoTick(Cycles);
    CPU.WriteByte(Cycles, Memory, MemoryValue, AbsAddress);
    CPU.Status.UpdateStatus(MemoryValue, CPU6502_Status_Z | CPU6502_Status_N);
    CPU.Status.C = Carry;
}

void CPU6502_ROR_ABS(U32 &Cycles, Memory &Memory, CPU6502 &CPU, BYTE AffectingRegister) {
    const WORD AbsAddress = CPU.FetchWord(Cycles, Memory);
    const WORD AffectedAbsAddress = AbsAddress + AffectingRegister;
    auto MemoryValue = CPU.ReadByte(Cycles, Memory, AffectedAbsAddress);
    const bool Carry = MemoryValue & 1;
    MemoryValue >>= 1;
    MemoryValue |= CPU.Status.C << 7;
    CPU6502::DoTick(Cycles);
    CPU.WriteByte(Cycles, Memory, MemoryValue, AffectedAbsAddress);
    CPU.Status.UpdateStatus(MemoryValue, CPU6502_Status_Z | CPU6502_Status_N);
    CPU.Status.C = Carry;
}

void CPU6502_ROR_ABSX(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_ROR_ABS(Cycles, Memory, CPU, CPU.X);
    CPU6502::DoTick(Cycles);
}
