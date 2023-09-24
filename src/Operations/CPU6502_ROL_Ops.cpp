#include "Operations/CPU6502_ROL_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void ExecuteROL(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE memoryValue, const WORD address) {
    const bool Carry = memoryValue & (1 << 7);
    memoryValue <<= 1;
    memoryValue |= cpu.Status.C;
    CPU6502::DoTick(cycles);
    CPU6502::WriteByte(cycles, memory, memoryValue, address);
    cpu.Status.UpdateStatus(memoryValue, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.C = Carry;
}

void CPU6502_ROL_ACC(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const bool Carry = cpu.A & (1 << 7);
    cpu.A <<= 1;
    cpu.A |= cpu.Status.C;
    CPU6502::DoTick(cycles);
    cpu.Status.UpdateStatus(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.C = Carry;
}

void CPU6502_ROL_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(cycles, memory);
    ExecuteROL(cycles, memory, cpu, Data.Value, Data.Address);
}

void CPU6502_ROL_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(cycles, memory, cpu.X);
    ExecuteROL(cycles, memory, cpu, Data.Value, Data.Address);
}

void CPU6502_ROL_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(cycles, memory);
    ExecuteROL(cycles, memory, cpu, Data.Value, Data.Address);
}

void CPU6502_ROL_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(cycles, memory, cpu.X);
    ExecuteROL(cycles, memory, cpu, Data.Value, Data.Address);
    CPU6502::DoTick(cycles); // extra cycle required
}
