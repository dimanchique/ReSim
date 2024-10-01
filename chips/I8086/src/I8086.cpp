#include "I8086/I8086.h"
#include "I8086/I8086_OpHelpers.h"

void I8086::Reset(Memory &memory) noexcept {
    PC = 0x0000;
    CS = 0xFFFF;
    DS = 0x0000;
    SS = 0x0000;
    ES = 0x0000;
    Status = 0;
    Status.NU1 = 1; // this flag is immutable

    // Status value is not defined after reset
    // Accumulator and general-purpose registers are not defined after reset and may contain arbitrary values.
    cycles = 0;

    memory.Reset();
}

U32 I8086::Run(Memory &memory) {
    bool decodeSuccess;

    do {
        const BYTE opCode = Fetch<BYTE>(memory);
        decodeSuccess = DecodeInstruction(opCode, memory, *this);
    } while (decodeSuccess);

    cycles -= 3;    // revert false fetch cycles
    PC--;           // revert extra PC increment for last instruction fetching
    return cycles;
}