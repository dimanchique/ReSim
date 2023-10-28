#include "Operations/CPU6502_ASL_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_ASL_ACC(Memory &memory, CPU6502 &cpu) {
    const bool Carry = cpu.A & (1 << 7);
    cpu.A <<= 1;
    cpu.cycles++;
    cpu.Status.UpdateStatusByValue(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.C = Carry;
}

void CPU6502_ASL_ZP(Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(memory);
    ExecuteASL(memory, cpu, Data.Value, Data.Address);
}

void CPU6502_ASL_ZPX(Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(memory, cpu.X);
    ExecuteASL(memory, cpu, Data.Value, Data.Address);
}

void CPU6502_ASL_ABS(Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(memory);
    ExecuteASL(memory, cpu, Data.Value, Data.Address);
}

void CPU6502_ASL_ABSX(Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(memory, cpu.X);
    ExecuteASL(memory, cpu, Data.Value, Data.Address);
    cpu.cycles++; // extra cycle required
}
