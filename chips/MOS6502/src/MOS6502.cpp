#include "MOS6502/MOS6502.h"
#include "MOS6502/MOS6502_OpHelpers.h"

void MOS6502::Reset(Memory &memory) noexcept {
    SP = 0xFF;

    Status = 0;
    A = X = Y = 0;
    cycles = 0;

    memory.Reset();
}

U32 MOS6502::Run(Memory &memory) {
    PC = (memory[0xFFFD] << 8) | memory[0xFFFC];

    bool DecodeSuccess;

    do {
        const BYTE opCode = FetchByte(memory);
        DecodeSuccess = DecodeInstruction(opCode, memory, *this);
    } while (DecodeSuccess);

    cycles--;       // revert fetch cycle
    PC--;           //revert extra PC increment for last instruction fetching
    return cycles;
}