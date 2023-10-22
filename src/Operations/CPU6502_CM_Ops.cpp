#include "Operations/CPU6502_CM_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_CM_IM(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE &targetRegister) {
    const ValueAddressRequest Data = cpu.GetImmediateAddressValue(cycles, memory);
    ExecuteCM(cpu, targetRegister, Data.Value);
}

void CPU6502_CM_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE &targetRegister) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(cycles, memory);
    ExecuteCM(cpu, targetRegister, Data.Value);
}

void CPU6502_CM_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE &targetRegister, BYTE affectingRegister) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(cycles, memory, affectingRegister);
    ExecuteCM(cpu, targetRegister, Data.Value);
}

void CPU6502_CM_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE &targetRegister) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(cycles, memory);
    ExecuteCM(cpu, targetRegister, Data.Value);
}

void CPU6502_CM_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE &targetRegister, BYTE affectingRegister) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(cycles, memory, affectingRegister);
    ExecuteCM(cpu, targetRegister, Data.Value);
}
