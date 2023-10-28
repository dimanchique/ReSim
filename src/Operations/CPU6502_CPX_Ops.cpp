#include "Operations/CPU6502_CM_Ops.h"
#include "Operations/CPU6502_CPX_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_CPX_IM(Memory &memory, CPU6502 &cpu) {
    CPU6502_CM_IM(memory, cpu, cpu.X);
}

void CPU6502_CPX_ZP(Memory &memory, CPU6502 &cpu) {
    CPU6502_CM_ZP(memory, cpu, cpu.X);
}

void CPU6502_CPX_ABS(Memory &memory, CPU6502 &cpu) {
    CPU6502_CM_ABS(memory, cpu, cpu.X);
}
