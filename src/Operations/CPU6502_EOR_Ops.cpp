#include "Operations/CPU6502_EOR_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void ExecuteEOR(CPU6502 &cpu, const BYTE value) {
    cpu.A ^= value;
    cpu.Status.UpdateStatus(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_EOR_IM(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetImmediateAddressValue(cycles, memory);
    ExecuteEOR(cpu, Data.Value);
}

void CPU6502_EOR_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(cycles, memory);
    ExecuteEOR(cpu, Data.Value);
}

void CPU6502_EOR_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(cycles, memory, cpu.X);
    ExecuteEOR(cpu, Data.Value);
}

void CPU6502_EOR_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(cycles, memory);
    ExecuteEOR(cpu, Data.Value);
}

void CPU6502_EOR_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE affectingRegister) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(cycles, memory, affectingRegister);
    ExecuteEOR(cpu, Data.Value);
}

void CPU6502_EOR_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_EOR_ABS(cycles, memory, cpu, cpu.X);
}

void CPU6502_EOR_ABSY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_EOR_ABS(cycles, memory, cpu, cpu.Y);
}

void CPU6502_EOR_INDX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetIndXAddressValue(cycles, memory);
    ExecuteEOR(cpu, Data.Value);
}

void CPU6502_EOR_INDY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetIndYAddressValue(cycles, memory);
    ExecuteEOR(cpu, Data.Value);
}
