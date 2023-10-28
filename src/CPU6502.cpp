#include "CPU6502.h"
#include "Memory.h"
#include "CPU6502_OpHelpers.h"

void CPU6502::Reset(Memory &memory, WORD ResetVector) noexcept {
    PC = ResetVector;
    SP = 0xFF;                                          // with 0x0100 offset

    Status = 0;
    A = X = Y = 0;
    cycles = 0;

    memory.Reset();
}

U32 CPU6502::Run(Memory &memory) {
    bool FetchSuccess;
    do {
        BYTE Instruction = FetchByte(memory);
        cycles--;             //leaving only instruction cycles here
        FetchSuccess = FetchCommand(Instruction, memory, *this);

        if (FetchSuccess)
            cycles++;

    } while (FetchSuccess);

    PC--;                           //revert extra PC increment for last instruction fetching
    return cycles;
}
