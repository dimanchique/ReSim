#include "Operations/CPU6502_ASL_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_ASL_ACC(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const bool Carry = cpu.A & (1 << 7);
    cpu.A <<= 1;
    CPU6502::DoTick(cycles);
    cpu.Status.UpdateStatus(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.C = Carry;
}

void CPU6502_ASL_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(cycles, memory);
    ExecuteASL(cycles, memory, cpu, Data.Value, Data.Address);
}

void CPU6502_ASL_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(cycles, memory, cpu.X);
    ExecuteASL(cycles, memory, cpu, Data.Value, Data.Address);
}

void CPU6502_ASL_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(cycles, memory);
    ExecuteASL(cycles, memory, cpu, Data.Value, Data.Address);
}

void CPU6502_ASL_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(cycles, memory, cpu.X);
    ExecuteASL(cycles, memory, cpu, Data.Value, Data.Address);
    CPU6502::DoTick(cycles); // extra cycle required
}
