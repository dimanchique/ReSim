#include "I8086.h"
#include "I8086_OpHelpers.h"

void I8086::Reset() noexcept {
    PC = 0x0000;
    CS = 0xFFFF;
    DS = 0x0000;
    SS = 0x0000;
    ES = 0x0000;
    Status.Value = 0;

    // Accumulator and general-purpose registers are not defined after reset and may contain arbitrary values.
    cycles = 0;
}

bool I8086::Step() {
    const BYTE opCode = Fetch<BYTE>();
    return DecodeInstruction(opCode, *this);
}


// I8086 sync tick system will be integrated when cycles count system will be implemented
U32 I8086::Run() {
    bool decodeSuccess;

    do {
        decodeSuccess = Step();
    } while (decodeSuccess);

    cycles -= 3;    // revert false fetch cycles
    PC--;           // revert extra PC increment for last instruction fetching
    return cycles;
}
