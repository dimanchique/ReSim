#include "I8080/I8080.h"
#include "I8080/I8080_OpHelpers.h"

void I8080::Reset(Memory &memory, const WORD resetVector) noexcept {
    PC = resetVector;
    SP = 0xFFFF;

    // Status value is not defined after reset
    // Accumulator and general-purpose registers are not defined after reset and may contain arbitrary values.
    cycles = 0;

    memory.Reset();
}

U32 I8080::Run(Memory &memory) {
    bool DecodeSuccess;
    BYTE Instruction;

    do {
        Instruction = FetchByte(memory);
        DecodeSuccess = DecodeCommand(Instruction, memory, *this);
        cycles++;

        if (!DecodeSuccess)
            cycles -= 4;

    } while (DecodeSuccess);

    PC--;                   //revert extra PC increment for last instruction fetching
    return cycles;
}