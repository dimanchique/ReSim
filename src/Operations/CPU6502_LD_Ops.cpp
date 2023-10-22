#include "Operations/CPU6502_LD_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_LD_IM(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE &targetRegister) {
    const ValueAddressRequest Data = cpu.GetImmediateAddressValue(cycles, memory);
    ExecuteLD(cpu, targetRegister, Data.Value);
}

void CPU6502_LD_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE &targetRegister) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(cycles, memory);
    ExecuteLD(cpu, targetRegister, Data.Value);
}

void CPU6502_LD_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE &targetRegister, BYTE affectingRegister) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(cycles, memory, affectingRegister);
    ExecuteLD(cpu, targetRegister, Data.Value);
}

void CPU6502_LD_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE &targetRegister) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(cycles, memory);
    ExecuteLD(cpu, targetRegister, Data.Value);
}

void CPU6502_LD_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE &targetRegister, BYTE affectingRegister) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(cycles, memory, affectingRegister);
    ExecuteLD(cpu, targetRegister, Data.Value);
}
