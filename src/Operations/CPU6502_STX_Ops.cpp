#include "Operations/CPU6502_ST_Ops.h"
#include "Operations/CPU6502_STX_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_STX_ZP(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_ST_ZP(Cycles, Memory, CPU, CPU.X);
}

void CPU6502_STX_ZPY(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_ST_ZP(Cycles, Memory, CPU, CPU.X, CPU.Y);
}

void CPU6502_STX_ABS(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_ST_ABS(Cycles, Memory, CPU, CPU.X);
}
