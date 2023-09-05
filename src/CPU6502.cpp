#include "CPU6502.h"
#include "Memory.h"
#include "CPU6502_OpHelpers.h"

void CPU6502::Reset(Memory &Memory) {
    Reset(0xFFFC, Memory);
}

void CPU6502::Reset(WORD ResetVector, Memory &Memory) {
    PC = ResetVector;
    SP = 0xFF;                                          // with 0x0100 offset

    C = Z = I = D = B = V = N = 0;
    A = X = Y = 0;

    Memory.Reset();
}

void CPU6502::SoftReset(Memory &Memory) {
    SoftReset(0xFFFC, Memory);
}

void CPU6502::SoftReset(WORD ResetVector, Memory &Memory) {
    PC = ResetVector;
    SP = 0xFF;                                          // with 0x0100 offset

    C = Z = I = D = B = V = N = 0;
    A = X = Y = 0;
}

BYTE CPU6502::FetchByte(S32 &Cycles, const Memory &Memory) {
    BYTE Data = Memory[PC++];
    Cycles--;
    return Data;
}

WORD CPU6502::FetchWord(S32 &Cycles, const Memory &Memory) {
    BYTE Lo = ReadByte(Cycles, Memory, PC++);
    BYTE Hi = ReadByte(Cycles, Memory, PC++);
    return Lo | (Hi << 8);
}

BYTE CPU6502::ReadByte(S32 &Cycles, const Memory &Memory, const WORD ADDR) const {
    BYTE Data = Memory[ADDR];
    Cycles--;
    return Data;
}

WORD CPU6502::ReadWord(S32 &Cycles, const Memory &Memory, const WORD ADDR) const {
    BYTE Lo = ReadByte(Cycles, Memory, ADDR);
    BYTE Hi = ReadByte(Cycles, Memory, ADDR + 1);
    return Lo | (Hi << 8);
}

void CPU6502::WriteByte(S32 &Cycles, Memory &Memory, const BYTE Value, const U32 ADDR){
    Memory[ADDR] = Value;
    Cycles --;
}

void CPU6502::WriteWord(S32 &Cycles, Memory &Memory, const WORD Value, const U32 ADDR){
    Memory[ADDR] = Value & 0xFF;
    Memory[ADDR + 1] = (Value >> 8);
    Cycles -= 2;
}

void CPU6502::PushProgramCounterToStack(S32 &Cycles, Memory &Memory) {
    WriteWord(Cycles, Memory, PC - 1, StackPointerToAddress() - 1);
    SP -= 2;
}

WORD CPU6502::PopAddressFromStack(S32 &Cycles, Memory &Memory) {
    WORD ValueFromStack = ReadWord(Cycles, Memory, StackPointerToAddress() + 1);
    SP += 2;
    Cycles--;
    return ValueFromStack + 1;
}

S32 CPU6502::Run(S32 Cycles, Memory &Memory) {
    const S32 CyclesRequested = Cycles;

    while (Cycles > 0) {
        BYTE Instruction = FetchByte(Cycles, Memory);
        FetchCommand(Cycles, Instruction, Memory, *this);
    }

    return CyclesRequested - Cycles;
}

void CPU6502::SetStatusRegisterValue(BYTE &Register, BYTE CheckArgs) {
    if(CheckArgs & CPU6502_Status_Z)
        Z = (Register == 0);
    if(CheckArgs & CPU6502_Status_N)
        N = (Register & 0b10000000) > 0;
}
