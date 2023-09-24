#include "Operations/CPU6502_AND_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void ExecuteAND(CPU6502 &cpu, const BYTE value) {
    cpu.A &= value;
    cpu.Status.UpdateStatus(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_AND_IM(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetImmediateAddressValue(cycles, memory);
    ExecuteAND(cpu, Data.Value);
}

void CPU6502_AND_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(cycles, memory);
    ExecuteAND(cpu, Data.Value);
}

void CPU6502_AND_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(cycles, memory, cpu.X);
    ExecuteAND(cpu, Data.Value);
}

void CPU6502_AND_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(cycles, memory);
    ExecuteAND(cpu, Data.Value);
}

void CPU6502_AND_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE affectingRegister) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(cycles, memory, affectingRegister);
    ExecuteAND(cpu, Data.Value);
}

void CPU6502_AND_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_AND_ABS(cycles, memory, cpu, cpu.X);
}

void CPU6502_AND_ABSY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_AND_ABS(cycles, memory, cpu, cpu.Y);
}

void CPU6502_AND_INDX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetIndXAddressValue(cycles, memory);
    ExecuteAND(cpu, Data.Value);
}

void CPU6502_AND_INDY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetIndYAddressValue(cycles, memory);
    ExecuteAND(cpu, Data.Value);
}
