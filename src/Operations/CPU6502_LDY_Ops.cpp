#include "Operations/CPU6502_LD_Ops.h"
#include "Operations/CPU6502_LDY_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_LDY_IM(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_LD_IM(Cycles, Memory, CPU, CPU.Y);
}

void CPU6502_LDY_ZP(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_LD_ZP(Cycles, Memory, CPU, CPU.Y);
}

void CPU6502_LDY_ZPX(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_LD_ZP(Cycles, Memory, CPU, CPU.Y, CPU.X);
}

void CPU6502_LDY_ABS(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_LD_ABS(Cycles, Memory, CPU, CPU.Y);
}

void CPU6502_LDY_ABSX(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_LD_ABS(Cycles, Memory, CPU, CPU.Y, CPU.X);
}
