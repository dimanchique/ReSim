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

BYTE CPU6502::FetchByte(Memory& memory){
    BYTE Data = memory[PC++];
    return Data;
}

WORD CPU6502::FetchWord(Memory& memory){
    // 6502 is little endian
    WORD Data = memory[PC++];
    Data |= (memory[PC++] << 8);
    return Data;
}

void CPU6502::WriteWord(WORD Value, U32 ADDR, Memory& memory){
    memory[ADDR]      =  Value & 0xFF;
    memory[ADDR + 1]  = (Value >> 8);
}

BYTE CPU6502::ReadByte(BYTE ADDR, Memory& memory) const {
    BYTE Data = memory[ADDR];
    return Data;
}

WORD CPU6502::Run(Memory& memory){
    WORD CNT = 0;
    while(PC != memory.GetSize()) {
        BYTE Instruction = FetchByte(memory);
        const auto res = FetchCommand(Instruction, memory, *this);
        if (!res)
            break;
        CNT++;
    }
    return CNT;
}
