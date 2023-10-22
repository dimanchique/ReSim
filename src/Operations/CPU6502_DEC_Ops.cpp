#include "Operations/CPU6502_DEC_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_DEC_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(cycles, memory);
    ExecuteDEC(cycles, memory, cpu, Data.Value, Data.Address);
}

void CPU6502_DEC_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(cycles, memory, cpu.X);
    ExecuteDEC(cycles, memory, cpu, Data.Value, Data.Address);
}

void CPU6502_DEC_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(cycles, memory);
    ExecuteDEC(cycles, memory, cpu, Data.Value, Data.Address);
}

void CPU6502_DEC_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(cycles, memory, cpu.X);
    ExecuteDEC(cycles, memory, cpu, Data.Value, Data.Address);
    CPU6502::DoTick(cycles); // extra cycle required
}

void CPU6502_DEX_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    cpu.X--;
    CPU6502::DoTick(cycles);
    cpu.Status.UpdateStatus(cpu.X, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_DEY_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    cpu.Y--;
    CPU6502::DoTick(cycles);
    cpu.Status.UpdateStatus(cpu.Y, CPU6502_Status_Z | CPU6502_Status_N);
}
