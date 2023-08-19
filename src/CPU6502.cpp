#include "CPU6502_OpHelpers.h"
#include "CPU6502.h"
#include "Memory.h"

void CPU6502::Reset(Memory& memory){
    PC = 0xFFFC;
    SP = 0x0100;

    A = X = Y = 0;
    C = Z = I = D = B = V = N = 0;

    memory.Reset();
}

BYTE CPU6502::FetchByte(S32& Cycles, Memory& memory){
    BYTE Data = memory[PC++];
    Cycles--;
    return Data;
}

WORD CPU6502::FetchWord(S32& Cycles, Memory& memory){
    // 6502 is little endian
    WORD Data = memory[PC++];
    Data |= (memory[PC++] << 8);

    Cycles -= 2;
    return Data;
}

void CPU6502::WriteWord(S32& Cycles, WORD Value, U32 ADDR, Memory& memory){
    memory[ADDR]      =  Value & 0xFF;
    memory[ADDR + 1]  = (Value >> 8);
    Cycles -= 2;
}

BYTE CPU6502::ReadByte(S32& Cycles, BYTE ADDR, Memory& memory) const {
    BYTE Data = memory[ADDR];
    Cycles--;
    return Data;
}

S32 CPU6502::Run(S32 Cycles, Memory& memory){
    const S32 CyclesRequested = Cycles;
    while(Cycles > 0) {
        BYTE Instruction = FetchByte(Cycles, memory);
        const auto res = FetchCommand(Cycles, Instruction, memory, *this);
        if (!res)
            break;
    }

    const S32 NumCyclesUsed = CyclesRequested - Cycles;
    return NumCyclesUsed;
}
