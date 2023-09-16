#include "CPU6502.h"
#include "Memory.h"
#include "CPU6502_OpHelpers.h"

void CPU6502::Reset(Memory &Memory) {
    Reset(0xFFFC, Memory);
}

void CPU6502::Reset(WORD ResetVector, Memory &Memory) {
    PC = ResetVector;
    SP = 0xFF;                                          // with 0x0100 offset

    Status = 0;
    A = X = Y = 0;

    Memory.Reset();
}

BYTE CPU6502::FetchByte(U32 &Cycles, const Memory &Memory) {
    BYTE Data = Memory[PC++];
    Cycles++;
    return Data;
}

WORD CPU6502::FetchWord(U32 &Cycles, const Memory &Memory) {
    BYTE Lo = ReadByte(Cycles, Memory, PC++);
    BYTE Hi = ReadByte(Cycles, Memory, PC++);
    return Lo | (Hi << 8);
}

BYTE CPU6502::ReadByte(U32 &Cycles, const Memory &Memory, const WORD ADDR) const {
    BYTE Data = Memory[ADDR];
    Cycles++;
    return Data;
}

WORD CPU6502::ReadWord(U32 &Cycles, const Memory &Memory, const WORD ADDR) const {
    BYTE Lo = ReadByte(Cycles, Memory, ADDR);
    BYTE Hi = ReadByte(Cycles, Memory, ADDR + 1);
    return Lo | (Hi << 8);
}

void CPU6502::WriteByte(U32 &Cycles, Memory &Memory, const BYTE Value, const U32 ADDR){
    Memory[ADDR] = Value;
    Cycles++;
}

void CPU6502::WriteWord(U32 &Cycles, Memory &Memory, const WORD Value, const U32 ADDR){
    Memory[ADDR] = Value & 0xFF;
    Memory[ADDR + 1] = (Value >> 8);
    Cycles += 2;
}

void CPU6502::PushProgramCounterToStack(U32 &Cycles, Memory &Memory) {
    PushWordToStack(Cycles, Memory, PC - 1);
}

WORD CPU6502::PopAddressFromStack(U32 &Cycles, Memory &Memory) {
    return PullWordFromStack(Cycles, Memory) + 1;
}

void CPU6502::PushByteToStack(U32 &Cycles, Memory &Memory, BYTE Value) {
    WriteByte(Cycles, Memory, Value, StackPointerToAddress());
    SP--;
    Cycles++;
}

void CPU6502::PushWordToStack(U32 &Cycles, Memory &Memory, WORD Value) {
    WriteWord(Cycles, Memory, Value, StackPointerToAddress() - 1);
    SP -= 2;
}

BYTE CPU6502::PullByteFromStack(U32 &Cycles, Memory &Memory) {
    SP++;
    Cycles++;
    const auto Value = ReadByte(Cycles, Memory, StackPointerToAddress());
    Cycles++;
    return Value;
}

WORD CPU6502::PullWordFromStack(U32 &Cycles, Memory &Memory) {
    WORD Value = ReadWord(Cycles, Memory, StackPointerToAddress() + 1);
    SP += 2;
    Cycles += 2;
    return Value;
}

U32 CPU6502::Run(Memory &Memory) {
    U32 CyclesPassed = 0;

    bool FetchSuccess;
    do {
        BYTE Instruction = FetchByte(CyclesPassed, Memory);
        CyclesPassed--; //leaving only instruction cycles here
        FetchSuccess = FetchCommand(CyclesPassed, Instruction, Memory, *this);
        if (FetchSuccess)
            CyclesPassed++;
    } while (FetchSuccess);

    PC--;               //revert extra PC increment for last instruction fetching

    return CyclesPassed;
}
