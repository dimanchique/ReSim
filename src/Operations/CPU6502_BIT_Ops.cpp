#include "Operations/CPU6502_BIT_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_BIT_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetZeroPageAddressValue(cycles, memory);
    ExecuteBIT(cpu, Data.Value);
}

void CPU6502_BIT_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const ValueAddressRequest Data = cpu.GetAbsAddressValue(cycles, memory);
    ExecuteBIT(cpu, Data.Value);
}
