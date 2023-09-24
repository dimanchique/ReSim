#include "Operations/CPU6502_CM_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void ExecuteCMP(CPU6502 &cpu, const BYTE& targetRegister, const BYTE memoryValue) {
    const BYTE comparedValue = targetRegister - memoryValue;
    cpu.Status.UpdateStatus(comparedValue, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.Status.SetStatusFlagValue(CPU6502_Status_C, targetRegister >= memoryValue);
}

void CPU6502_CM_IM(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE &targetRegister) {
    const ValueAddressRequest Data = cpu.GetImmediateAddressValue(cycles, memory);
    ExecuteCMP(cpu, targetRegister, Data.Value);
}

void CPU6502_CM_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE &targetRegister) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(cycles, memory);
    ExecuteCMP(cpu, targetRegister, Data.Value);
}

void CPU6502_CM_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE &targetRegister, BYTE affectingRegister) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(cycles, memory, affectingRegister);
    ExecuteCMP(cpu, targetRegister, Data.Value);
}

void CPU6502_CM_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE &targetRegister) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(cycles, memory);
    ExecuteCMP(cpu, targetRegister, Data.Value);
}

void CPU6502_CM_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu, BYTE &targetRegister, BYTE affectingRegister) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(cycles, memory, affectingRegister);
    ExecuteCMP(cpu, targetRegister, Data.Value);
}
