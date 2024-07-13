#include "MOS6502/MOS6502.h"
#include "MOS6502/MOS6502_OpHelpers.h"

void MOS6502::Reset(Memory &memory, const WORD resetVector) noexcept {
    PC = resetVector;
    SP = 0xFF;

    Status = 0;
    A = X = Y = 0;
    cycles = 0;

    memory.Reset(STOP_OPCODE);
}

U32 MOS6502::Run(Memory &memory) {
    bool DecodeSuccess;

    do {
        const BYTE opCode = FetchByte(memory);
        DecodeSuccess = DecodeInstruction(opCode, memory, *this);
    } while (DecodeSuccess);

    PC--; //revert extra PC increment for last instruction fetching
    return cycles;
}