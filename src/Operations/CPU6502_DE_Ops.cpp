#include "Operations/CPU6502_DE_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_DEX_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.X--;
    Cycles -= 2;
    CPU.SetStatusRegisterValue(CPU.X, CPU6502_Status_Z | CPU6502_Status_N);
}

void CPU6502_DEY_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.Y--;
    Cycles -= 2;
    CPU.SetStatusRegisterValue(CPU.Y, CPU6502_Status_Z | CPU6502_Status_N);
}
