#include "Operations/CPU6502_NOP_Op.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_NOP_IMPL(U32 &cycles, Memory &memory, CPU6502 &cpu) {
    CPU6502::DoTick(cycles);
}
