#include "Operations/CPU6502_CM_Ops.h"
#include "Operations/CPU6502_CPX_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_CPX_IM(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_CM_IM(cycles, memory, cpu, cpu.X);
}

void CPU6502_CPX_ZP(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_CM_ZP(cycles, memory, cpu, cpu.X);
}

void CPU6502_CPX_ABS(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502_CM_ABS(cycles, memory, cpu, cpu.X);
}
