#include "Operations/CPU6502_ROR_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_ROR_ACC(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const bool Carry = cpu.A & 1;
    cpu.A >>= 1;
    cpu.A |= cpu.Status.C << 7;
    CPU6502::DoTick(cycles);
    cpu.Status.UpdateStatusByValue(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.C = Carry;
}

void CPU6502_ROR_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(cycles, memory);
    ExecuteROR(cycles, memory, cpu, Data.Value, Data.Address);
}

void CPU6502_ROR_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(cycles, memory, cpu.X);
    ExecuteROR(cycles, memory, cpu, Data.Value, Data.Address);
}

void CPU6502_ROR_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(cycles, memory);
    ExecuteROR(cycles, memory, cpu, Data.Value, Data.Address);
}

void CPU6502_ROR_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(cycles, memory, cpu.X);
    ExecuteROR(cycles, memory, cpu, Data.Value, Data.Address);
    CPU6502::DoTick(cycles); // extra cycle required
}
