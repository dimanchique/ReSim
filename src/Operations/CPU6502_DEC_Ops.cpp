#include "Operations/CPU6502_DEC_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_DEC_ZP(Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(memory);
    ExecuteDEC(memory, cpu, Data.Value, Data.Address);
}

void CPU6502_DEC_ZPX(Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(memory, cpu.X);
    ExecuteDEC(memory, cpu, Data.Value, Data.Address);
}

void CPU6502_DEC_ABS(Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(memory);
    ExecuteDEC(memory, cpu, Data.Value, Data.Address);
}

void CPU6502_DEC_ABSX(Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(memory, cpu.X);
    ExecuteDEC(memory, cpu, Data.Value, Data.Address);
    cpu.cycles++; // extra cycle required
}

void CPU6502_DEX_IMPL(Memory &memory, CPU6502 &cpu) {
    cpu.X--;
    cpu.cycles++;
    cpu.Status.UpdateStatusByValue(cpu.X, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_DEY_IMPL(Memory &memory, CPU6502 &cpu) {
    cpu.Y--;
    cpu.cycles++;
    cpu.Status.UpdateStatusByValue(cpu.Y, CPU6502_Status_Z | CPU6502_Status_N);
}
