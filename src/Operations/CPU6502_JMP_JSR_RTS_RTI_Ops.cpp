#include "Operations/CPU6502_JMP_JSR_RTS_RTI_Ops.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502_JMP_ABS(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.PC = CPU.FetchWord(Cycles, Memory);
}

void CPU6502_JMP_IND(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    const WORD JumpAddress = CPU.FetchWord(Cycles, Memory);
    CPU.PC = CPU.ReadWord(Cycles, Memory, JumpAddress);
    Cycles--;
}

void CPU6502_JSR_ABS(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    const WORD JumpAddress = CPU.FetchWord(Cycles, Memory);
    CPU.PushProgramCounterToStack(Cycles, Memory);
    CPU.PC = JumpAddress;
    Cycles--;
}

void CPU6502_RTS_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.PC = CPU.PopAddressFromStack(Cycles, Memory);
    Cycles -= 2;
}

void CPU6502_RTI_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){

}
