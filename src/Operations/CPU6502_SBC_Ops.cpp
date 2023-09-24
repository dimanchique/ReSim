#include "Operations/CPU6502_SBC_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void ExecuteSBC(CPU6502 &cpu, const BYTE Operand) {
    const bool AreSignBitsTheSame = !((cpu.A ^ Operand) & CPU6502_Status_N);
    const WORD Sub = cpu.A - Operand - (1 - cpu.Status.C);
    cpu.A = Sub;
    cpu.Status.UpdateStatus(cpu.A, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.SetStatusFlagValue(CPU6502_Status_C, Sub > 0xFF);
    cpu.Status.SetStatusFlagValue(CPU6502_Status_V, AreSignBitsTheSame && ((cpu.A ^ Operand) & CPU6502_Status_N));
}

void CPU6502_SBC_IM(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetImmediateAddressValue(cycles, memory);
    ExecuteSBC(cpu, Data.Value);
}

void CPU6502_SBC_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(cycles, memory);
    ExecuteSBC(cpu, Data.Value);
}

void CPU6502_SBC_ZPX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(cycles, memory, cpu.X);
    ExecuteSBC(cpu, Data.Value);
}

void CPU6502_SBC_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(cycles, memory);
    ExecuteSBC(cpu, Data.Value);
}

void CPU6502_SBC_ABSX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(cycles, memory, cpu.X);
    ExecuteSBC(cpu, Data.Value);
}

void CPU6502_SBC_ABSY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(cycles, memory, cpu.Y);
    ExecuteSBC(cpu, Data.Value);
}

void CPU6502_SBC_INDX(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetIndXAddressValue(cycles, memory);
    ExecuteSBC(cpu, Data.Value);
}

void CPU6502_SBC_INDY(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetIndYAddressValue(cycles, memory);
    ExecuteSBC(cpu, Data.Value);
}
