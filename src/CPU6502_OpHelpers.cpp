#include <CPU6502_OpHelpers.h>
#include <Operations/CPU6502_LDA_Ops.h>
#include <Operations/CPU6502_LDX_Ops.h>
#include <Operations/CPU6502_LDY_Ops.h>
#include <Operations/CPU6502_STA_Ops.h>
#include <Operations/CPU6502_STX_Ops.h>
#include <Operations/CPU6502_STY_Ops.h>
#include <CPU6502.h>
#include <Memory.h>
#include <cstdio>
#include "Operations/CPU6502_T_Ops.h"

void DumpStack(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    std::printf("Illegal instruction called\n");
    std::printf("Runtime information:\n");
    std::printf("\tCycles left: %d\n", Cycles);
    std::printf("\tProgram Counter: 0x%04x\n", CPU.PC);
    std::printf("\tStack Pointer: 0x%04x\n", CPU.SP + 0x100);
    std::printf("\tStatus Register: %d%d%d%d%d%d%d\n", CPU.C, CPU.Z, CPU.I, CPU.D, CPU.B, CPU.V, CPU.N);
    std::printf("\t                 CZIDBVN\n");
}

void CPU6502_NOOP(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    DumpStack(Cycles, Memory, CPU);
    throw -1;
}

void CPU6502_JSR_ABS(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    const WORD JumpAddress = CPU.FetchWord(Cycles, Memory);
    CPU.WriteWord(Cycles, Memory, CPU.PC - 1, CPU.SP);
    CPU.PC = JumpAddress;
    CPU.SP += 2;
    Cycles--;
}

void CPU6502_CLC_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.C = 0;
    Cycles -= 2;
}

void CPU6502_CLD_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.D = 0;
    Cycles -= 2;
}

void CPU6502_CLI_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.I = 0;
    Cycles -= 2;
}

void CPU6502_CLV_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.V = 0;
    Cycles -= 2;
}

void CPU6502_DEX_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.X--;
    Cycles -= 2;
    CPU.LoadRegisterSetStatus(CPU.X);
}

void CPU6502_DEY_IMPL(S32& Cycles, Memory &Memory, CPU6502 &CPU){
    CPU.Y--;
    Cycles -= 2;
    CPU.LoadRegisterSetStatus(CPU.Y);
}

using OpSignature = void (*)(S32 &, Memory &, CPU6502 &);
const static OpSignature Ops[] = {
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_JSR_ABS,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_STA_INDX,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_STY_ZP,
        CPU6502_STA_ZP,
        CPU6502_STX_ZP,
        CPU6502_NOOP,
        CPU6502_DEY_IMPL,
        CPU6502_NOOP,
        CPU6502_TXA_IMPL,
        CPU6502_NOOP,
        CPU6502_STY_ABS,
        CPU6502_STA_ABS,
        CPU6502_STX_ABS,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_STA_INDY,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_STY_ZPX,
        CPU6502_STA_ZPX,
        CPU6502_STX_ZPY,
        CPU6502_NOOP,
        CPU6502_TYA_IMPL,
        CPU6502_STA_ABSY,
        CPU6502_TXS_IMPL,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_STA_ABSX,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_LDY_IM,
        CPU6502_LDA_INDX,
        CPU6502_LDX_IM,
        CPU6502_NOOP,
        CPU6502_LDY_ZP,
        CPU6502_LDA_ZP,
        CPU6502_LDX_ZP,
        CPU6502_NOOP,
        CPU6502_TAY_IMPL,
        CPU6502_LDA_IM,
        CPU6502_TAX_IMPL,
        CPU6502_NOOP,
        CPU6502_LDY_ABS,
        CPU6502_LDA_ABS,
        CPU6502_LDX_ABS,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_LDA_INDY,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_LDY_ZPX,
        CPU6502_LDA_ZPX,
        CPU6502_LDX_ZPY,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_LDA_ABSY,
        CPU6502_TSX_IMPL,
        CPU6502_NOOP,
        CPU6502_LDY_ABSX,
        CPU6502_LDA_ABSX,
        CPU6502_LDX_ABSY,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_DEX_IMPL,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP
};

void FetchCommand(S32& Cycles, const BYTE OpCode, Memory &Memory, CPU6502 &CPU) {
    Ops[OpCode](Cycles, Memory, CPU);
}