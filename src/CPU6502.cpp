#include "CPU6502.h"
#include "Memory.h"
#include "CPU6502_OpHelpers.h"

void CPU6502::Reset(Memory &memory, WORD ResetVector) noexcept {
    PC = ResetVector;
    SP = 0xFF;                                          // with 0x0100 offset

    Status = 0;
    A = X = Y = 0;

    memory.Reset();
}

U32 CPU6502::Run(Memory &memory) {
    U32 cyclesPassed = 0;

    bool FetchSuccess;
    do {
        BYTE Instruction = FetchByte(cyclesPassed, memory);
        cyclesPassed--;             //leaving only instruction cycles here
        FetchSuccess = FetchCommand(cyclesPassed, Instruction, memory, *this);

        if (FetchSuccess)
            cyclesPassed++;
    } while (FetchSuccess);

    PC--;                           //revert extra PC increment for last instruction fetching

    return cyclesPassed;
}
