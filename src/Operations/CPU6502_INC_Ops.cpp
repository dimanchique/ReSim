#include "Operations/CPU6502_INC_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_INC_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(cycles, memory);
    ExecuteINC(cycles, memory, cpu, Data.Value, Data.Address);
}

void CPU6502_INC_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(cycles, memory, cpu.X);
    ExecuteINC(cycles, memory, cpu, Data.Value, Data.Address);
}

void CPU6502_INC_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(cycles, memory);
    ExecuteINC(cycles, memory, cpu, Data.Value, Data.Address);
}

void CPU6502_INC_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(cycles, memory, cpu.X);
    ExecuteINC(cycles, memory, cpu, Data.Value, Data.Address);
    DoTick(cycles); // extra cycle required
}

void CPU6502_INX_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    cpu.X++;
    DoTick(cycles);
    cpu.Status.UpdateStatusByValue(cpu.X, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_INY_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    cpu.Y++;
    DoTick(cycles);
    cpu.Status.UpdateStatusByValue(cpu.Y, CPU6502_Status_Z | CPU6502_Status_N);
}
