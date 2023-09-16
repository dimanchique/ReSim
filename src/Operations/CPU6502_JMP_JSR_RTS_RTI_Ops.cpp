#include "Operations/CPU6502_JMP_JSR_RTS_RTI_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_JMP_ABS(U32 &Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.PC = CPU.FetchWord(Cycles, Memory);
}

void CPU6502_JMP_IND(U32 &Cycles, Memory &Memory, CPU6502 &CPU){
    const WORD JumpAddress = CPU.FetchWord(Cycles, Memory);
    CPU.PC = CPU.ReadWord(Cycles, Memory, JumpAddress);
}

void CPU6502_JSR_ABS(U32 &Cycles, Memory &Memory, CPU6502 &CPU){
    const WORD JumpAddress = CPU.FetchWord(Cycles, Memory);
    CPU.PushProgramCounterToStack(Cycles, Memory);
    CPU.PC = JumpAddress;
    Cycles++;
}

void CPU6502_RTS_IMPL(U32 &Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.PC = CPU.PopAddressFromStack(Cycles, Memory);
    Cycles++;
}

void CPU6502_RTI_IMPL(U32 &Cycles, Memory &Memory, CPU6502 &CPU){

}
