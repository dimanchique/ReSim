#include <cstdio>
#include "CPU6502.h"
#include "Memory.h"
#include "CPU6502_OpHelpers.h"

void CPU6502::Reset(Memory &memory) {
    PC = 0xFFFC;
    SP = 0x0100;

    // I think it may be garbage
    //A = X = Y = 0;
    C = Z = I = D = B = V = N = 0;

    memory.Reset();
}

BYTE CPU6502::FetchByte(S32 &Cycles, Memory &memory) {
    BYTE Data = memory[PC++];
    Cycles--;
    return Data;
}

WORD CPU6502::FetchWord(S32 &Cycles, Memory &memory) {
    // 6502 is little endian so LMB and MMB are swapped
    WORD Data = memory[PC++];
    Data |= (memory[PC++] << 8);

    Cycles -= 2;
    return Data;
}

void CPU6502::WriteWord(S32 &Cycles, WORD Value, U32 ADDR, Memory &memory) {
    memory[ADDR] = Value & 0xFF;
    memory[ADDR + 1] = (Value >> 8);
    Cycles -= 2;
}

BYTE CPU6502::ReadByte(S32 &Cycles, WORD ADDR, Memory &memory) const {
    BYTE Data = memory[ADDR];
    Cycles--;
    return Data;
}

WORD CPU6502::ReadWord(S32 &Cycles, WORD ADDR, Memory &memory) const {
    BYTE Lo = ReadByte(Cycles, ADDR, memory);
    BYTE Hi = ReadByte(Cycles, ADDR + 1, memory);
    return Lo | (Hi << 8);
}

S32 CPU6502::Run(S32 Cycles, Memory &memory) {
    const S32 CyclesRequested = Cycles;

    while (Cycles > 0) {
        BYTE Instruction = FetchByte(Cycles, memory);
        const auto res = FetchCommand(Cycles, Instruction, memory, *this);
        if (!res) {
            std::printf("Can't handle instruction 0x%x\n", Instruction);
            throw -1;
        }
    }

    const S32 NumCyclesUsed = CyclesRequested - Cycles;
    return NumCyclesUsed;
}

void CPU6502::LoadRegisterSetStatus(BYTE &Register) {
    Z = (Register == 0);
    N = (Register & 0b10000000) > 0;
}