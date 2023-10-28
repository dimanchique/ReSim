#include "Operations/CPU6502_BIT_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_BIT_ZP(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetZeroPageValue(memory);
    ExecuteBIT(cpu, Data);
}

void CPU6502_BIT_ABS(Memory &memory, CPU6502 &cpu) {
    const BYTE Data = cpu.GetAbsValue(memory);
    ExecuteBIT(cpu, Data);
}
