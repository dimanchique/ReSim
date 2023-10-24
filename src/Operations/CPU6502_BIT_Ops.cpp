#include "Operations/CPU6502_BIT_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_BIT_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetZeroPageValue(cycles, memory);
    ExecuteBIT(cpu, Data);
}

void CPU6502_BIT_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetAbsValue(cycles, memory);
    ExecuteBIT(cpu, Data);
}
