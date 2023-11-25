#include "Operations/CPU6502_BIT_Ops.h"
#include "CPU6502.h"

void CPU6502_BIT_ZP(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.GetZeroPageValue(memory);
    GenericBIT(cpu, value);
}

void CPU6502_BIT_ABS(Memory &memory, CPU6502 &cpu) {
    const BYTE value = cpu.GetAbsValue(memory);
    GenericBIT(cpu, value);
}
