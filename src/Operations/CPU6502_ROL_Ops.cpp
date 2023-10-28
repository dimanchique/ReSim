#include "Operations/CPU6502_ROL_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_ROL_ACC(Memory &memory, CPU6502 &cpu) {
    const bool Carry = cpu.A & (1 << 7);
    cpu.A <<= 1;
    cpu.A |= cpu.Status.C;
    cpu.cycles++;
    cpu.Status.UpdateStatusByValue(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.C = Carry;
}

void CPU6502_ROL_ZP(Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(memory);
    ExecuteROL(memory, cpu, Data.Value, Data.Address);
}

void CPU6502_ROL_ZPX(Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(memory, cpu.X);
    ExecuteROL(memory, cpu, Data.Value, Data.Address);
}

void CPU6502_ROL_ABS(Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(memory);
    ExecuteROL(memory, cpu, Data.Value, Data.Address);
}

void CPU6502_ROL_ABSX(Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(memory, cpu.X);
    ExecuteROL(memory, cpu, Data.Value, Data.Address);
    cpu.cycles++; // extra cycle required
}
