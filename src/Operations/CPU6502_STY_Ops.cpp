#include "Operations/CPU6502_ST_Ops.h"
#include "Operations/CPU6502_STY_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_STY_ZP(S32& Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_ST_ZP(Cycles, Memory, CPU, CPU.Y);
}

void CPU6502_STY_ZPX(S32& Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_ST_ZP(Cycles, Memory, CPU, CPU.Y, CPU.X);
}

void CPU6502_STY_ABS(S32& Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502_ST_ABS(Cycles, Memory, CPU, CPU.Y);
}
