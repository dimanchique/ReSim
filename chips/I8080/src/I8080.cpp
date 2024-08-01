#include "I8080/I8080.h"
#include "I8080/I8080_OpHelpers.h"

void I8080::Reset(Memory &memory, const WORD resetVector) noexcept {
    PC = resetVector;
    SP = 0xFFFF;
    Status = 0;
    Status.NU1 = 1; // this flag is immutable

    // Status value is not defined after reset
    // Accumulator and general-purpose registers are not defined after reset and may contain arbitrary values.
    cycles = 0;

    memory.Reset(STOP_OPCODE);
}

U32 I8080::Run(Memory &memory) {
    bool decodeSuccess;

    do {
        const BYTE opCode = FetchByte(memory);
        decodeSuccess = DecodeInstruction(opCode, memory, *this);
    } while (decodeSuccess);

    PC--; // revert extra PC increment for last instruction fetching
    return cycles;
}