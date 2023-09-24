#include "Operations/CPU6502_ORA_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void ExecuteORA(CPU6502 &cpu, const BYTE value) {
    cpu.A |= value;
    cpu.Status.UpdateStatus(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_ORA_IM(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetImmediateAddressValue(cycles, memory);
    ExecuteORA(cpu, Data.Value);
}

void CPU6502_ORA_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(cycles, memory);
    ExecuteORA(cpu, Data.Value);
}

void CPU6502_ORA_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(cycles, memory, cpu.X);
    ExecuteORA(cpu, Data.Value);
}

void CPU6502_ORA_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(cycles, memory);
    ExecuteORA(cpu, Data.Value);
}

void CPU6502_ORA_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE affectingRegister) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(cycles, memory, affectingRegister);
    ExecuteORA(cpu, Data.Value);
}

void CPU6502_ORA_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_ORA_ABS(cycles, memory, cpu, cpu.X);
}

void CPU6502_ORA_ABSY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_ORA_ABS(cycles, memory, cpu, cpu.Y);
}

void CPU6502_ORA_INDX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetIndXAddressValue(cycles, memory);
    ExecuteORA(cpu, Data.Value);
}

void CPU6502_ORA_INDY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetIndYAddressValue(cycles, memory);
    ExecuteORA(cpu, Data.Value);
}
