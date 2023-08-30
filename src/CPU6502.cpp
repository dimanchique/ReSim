#include <cstdio>
#include "CPU6502.h"
#include "Memory.h"
#include "CPU6502_OpHelpers.h"

void CPU6502::Reset(Memory &memory) {
    PC = 0xFFFC;
    SP = 0x0000;                                        // with 0x0100 offset

    A = X = Y = 0;
    C = Z = I = D = B = V = N = 0;

    memory.Reset();
}

BYTE CPU6502::FetchByte(S32 &Cycles, const Memory &memory) {
    BYTE Data = memory[PC++];
    Cycles--;
    return Data;
}

WORD CPU6502::FetchWord(S32 &Cycles, const Memory &memory) {
    WORD Data = memory.ReadWord(Cycles, PC++);          // Read WORD
    PC++;                                               // Don't forget extra increment
    return Data;
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