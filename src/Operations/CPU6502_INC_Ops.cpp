#include "Operations/CPU6502_INC_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_INC_ZP(Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(memory);
    GenericINC(memory, cpu, Data.Value, Data.Address);
}

void CPU6502_INC_ZPX(Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(memory, cpu.X);
    GenericINC(memory, cpu, Data.Value, Data.Address);
}

void CPU6502_INC_ABS(Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(memory);
    GenericINC(memory, cpu, Data.Value, Data.Address);
}

void CPU6502_INC_ABSX(Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(memory, cpu.X);
    GenericINC(memory, cpu, Data.Value, Data.Address);
    cpu.cycles++; // extra cycle required
}

void CPU6502_INX_IMPL(Memory &memory, CPU6502 &cpu) {
    cpu.X++;
    cpu.cycles++;
    cpu.Status.UpdateStatusByValue(cpu.X, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_INY_IMPL(Memory &memory, CPU6502 &cpu) {
    cpu.Y++;
    cpu.cycles++;
    cpu.Status.UpdateStatusByValue(cpu.Y, CPU6502_Status_Z | CPU6502_Status_N);
}
