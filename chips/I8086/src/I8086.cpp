#include "I8086.h"
#include "I8086_OpCodes_Main.h"
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
    // Reset segment to default (DS) before each instruction fetch.
    // Segment override prefixes (ES/CS/SS/DS at 0x26/0x2E/0x36/0x3E)
    // will change this for the following instruction only.
    currentSegment = &DS;

    // ---- segment override prefixes -------------------------------------------
    // Consume any number of consecutive prefix bytes; only the last one wins.
    BYTE opCode;
    do {
        opCode = Fetch<BYTE>();
        // segment override opCodes has pattern 001xx110
        // so we're using value 11100111 as a filter mask for fast search
        // if opCode & 11100111 equals I8086_OpCodes_Main::ES (which is 00100110)
        // then we detect segment override opCode
        if ((opCode & 0b11100111) == I8086_OpCodes_Main::ES)
            PerformSegmentOverriding(opCode);
        else break;
    } while (true);

    // opCode is now a regular (non-prefix) instruction → dispatch.
    return DecodeInstruction(opCode, *this);
}

void I8086::PerformSegmentOverriding(BYTE opCode) {
    WORD *newSegment = nullptr;
    switch (opCode) {
        case I8086_OpCodes_Main::ES: newSegment = &ES; break;
        case I8086_OpCodes_Main::CS: newSegment = &CS; break;
        case I8086_OpCodes_Main::SS: newSegment = &SS; break;
        case I8086_OpCodes_Main::DS: newSegment = &DS; break;
        default: break;
    }
    if (newSegment) {
        currentSegment = newSegment;
        cycles += 2;
    }
}


// I8086 sync tick system will be integrated when cycles count system will be implemented
U32 I8086::Run() {
    bool decodeSuccess;

    do {
        decodeSuccess = Step();
    } while (decodeSuccess && !stop_requested);

    cycles -= 3;    // revert false fetch cycles
    PC--;           // revert extra PC increment for last instruction fetching
    return cycles;
}
