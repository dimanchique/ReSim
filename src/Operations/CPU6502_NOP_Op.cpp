#include "Operations/CPU6502_NOP_Op.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_NOP_IMPL(U32 &Cycles, Memory &Memory, CPU6502 &CPU) {
    CPU6502::DoTick(Cycles);
}
