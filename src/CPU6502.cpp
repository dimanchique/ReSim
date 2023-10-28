#include "CPU6502.h"
#include "Memory.h"
#include "CPU6502_OpHelpers.h"

void CPU6502::Reset(Memory &memory, WORD resetVector) noexcept {
    PC = resetVector;
    SP = 0xFF;

    Status = 0;
    A = X = Y = 0;
    cycles = 0;

    memory.Reset();
}

U32 CPU6502::Run(Memory &memory) {
    bool DecodeSuccess;
    BYTE Instruction;

    do {
        Instruction = FetchByte(memory);
        cycles--;           //leaving only instruction cycles here
        DecodeSuccess = DecodeCommand(Instruction, memory, *this);

        if (DecodeSuccess)
            cycles++;

    } while (DecodeSuccess);

    PC--;                   //revert extra PC increment for last instruction fetching
    return cycles;
}
