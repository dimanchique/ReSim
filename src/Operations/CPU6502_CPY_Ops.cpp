#include "Operations/CPU6502_CM_Ops.h"
#include "Operations/CPU6502_CPY_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_CPY_IM(Memory &memory, CPU6502 &cpu) {
    CPU6502_CM_IM(memory, cpu, cpu.Y);
}

void CPU6502_CPY_ZP(Memory &memory, CPU6502 &cpu) {
    CPU6502_CM_ZP(memory, cpu, cpu.Y);
}

void CPU6502_CPY_ABS(Memory &memory, CPU6502 &cpu) {
    CPU6502_CM_ABS(memory, cpu, cpu.Y);
}
