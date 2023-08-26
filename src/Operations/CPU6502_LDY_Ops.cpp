#include "Operations/CPU6502_LD_Ops.h"
#include "Operations/CPU6502_LDY_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_LDY_IM(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_IM(Cycles, memory, cpu, cpu.Y);
}

void CPU6502_LDY_ZP(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ZP(Cycles, memory, cpu, cpu.Y);
}

void CPU6502_LDY_ZPX(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ZP(Cycles, memory, cpu, cpu.Y, cpu.X);
}

void CPU6502_LDY_ABS(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ABS(Cycles, memory, cpu, cpu.Y);
}

void CPU6502_LDY_ABSX(S32& Cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_LD_ABS(Cycles, memory, cpu, cpu.Y, cpu.X);
}
