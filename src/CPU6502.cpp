#include "CPU6502.h"
#include "Memory.h"
#include "CPU6502_OpHelpers.h"

void CPU6502::Reset(Memory &memory, WORD resetVector) {
    PC = resetVector;
    SP = 0xFF;                                          // with 0x0100 offset

    Status = 0;
    A = X = Y = 0;

    memory.Reset();
}

U32 CPU6502::Run(Memory &memory) {
    U32 cyclesPassed = 0;

    bool FetchSuccess;
    do {
        BYTE Instruction = FetchByte(cyclesPassed, memory);
        cyclesPassed--;             //leaving only instruction cycles here
        FetchSuccess = FetchCommand(cyclesPassed, Instruction, memory, *this);
        if (FetchSuccess)
            cyclesPassed++;
    } while (FetchSuccess);

    PC--;                           //revert extra PC increment for last instruction fetching

    return cyclesPassed;
}

BYTE CPU6502::FetchByte(U32 &cycles, const Memory &memory) {
    BYTE Data = memory[PC++];
    CPU6502::DoTick(cycles);
    return Data;
}

WORD CPU6502::FetchWord(U32 &cycles, const Memory &memory) {
    BYTE Lo = ReadByte(cycles, memory, PC++);
    BYTE Hi = ReadByte(cycles, memory, PC++);
    return Lo | (Hi << 8);
}

BYTE CPU6502::ReadByte(U32 &cycles, const Memory &memory, WORD ADDR) {
    BYTE Data = memory[ADDR];
    CPU6502::DoTick(cycles);
    return Data;
}

WORD CPU6502::ReadWord(U32 &cycles, const Memory &memory, WORD ADDR) {
    BYTE Lo = ReadByte(cycles, memory, ADDR);
    BYTE Hi = ReadByte(cycles, memory, ADDR + 1);
    return Lo | (Hi << 8);
}

void CPU6502::WriteByte(U32 &cycles, Memory &memory, BYTE value, U32 ADDR) {
    memory[ADDR] = value;
    cycles++;
}

void CPU6502::WriteWord(U32 &cycles, Memory &memory, WORD value, U32 ADDR) {
    memory[ADDR] = value & 0xFF;
    CPU6502::DoTick(cycles);
    memory[ADDR + 1] = (value >> 8);
    CPU6502::DoTick(cycles);
}

void CPU6502::PushProgramCounterToStack(U32 &cycles, Memory &memory) {
    PushWordToStack(cycles, memory, PC - 1);
}

WORD CPU6502::PullAddressFromStack(U32 &cycles, Memory &memory) {
    return PullWordFromStack(cycles, memory) + 1;
}

void CPU6502::PushStatusToStack(U32 &cycles, Memory &memory) {
    WriteByte(cycles, memory, Status, StackPointerToAddress());
    SP--;
    CPU6502::DoTick(cycles);
}

void CPU6502::PullStatusFromStack(U32 &cycles, Memory &memory) {
    SP++;
    CPU6502::DoTick(cycles);
    Status = ReadByte(cycles, memory, StackPointerToAddress());
    CPU6502::DoTick(cycles);
}

void CPU6502::PushByteToStack(U32 &cycles, Memory &memory, BYTE value) {
    WriteByte(cycles, memory, value, StackPointerToAddress());
    SP--;
    CPU6502::DoTick(cycles);
}

BYTE CPU6502::PullByteFromStack(U32 &cycles, Memory &memory) {
    SP++;
    CPU6502::DoTick(cycles);
    const BYTE value = ReadByte(cycles, memory, StackPointerToAddress());
    CPU6502::DoTick(cycles);
    return value;
}

void CPU6502::PushWordToStack(U32 &cycles, Memory &memory, WORD value) {
    WriteWord(cycles, memory, value, StackPointerToAddress() - 1);
    SP -= 2;
}

WORD CPU6502::PullWordFromStack(U32 &cycles, Memory &memory) {
    WORD value = ReadWord(cycles, memory, StackPointerToAddress() + 1);
    CPU6502::DoTick(cycles);
    SP += 2;
    CPU6502::DoTick(cycles);
    return value;
}

ValueAddressRequest CPU6502::GetImmediateAddressValue(U32 &cycles, Memory &memory) {
    const BYTE Value = FetchByte(cycles, memory);
    return {Value, PC};
}

BYTE CPU6502::GetZeroPageAddress(U32 &cycles, Memory &memory) {
    return FetchByte(cycles, memory);
}

ValueAddressRequest CPU6502::GetZeroPageAddressValue(U32 &cycles, Memory &memory) {
    const BYTE TargetAddress = GetZeroPageAddress(cycles, memory);
    const BYTE Value = CPU6502::ReadByte(cycles, memory, TargetAddress);
    return {Value, TargetAddress};
}

WORD CPU6502::GetZeroPageAddress(U32 &cycles, Memory &memory, BYTE offsetAddress) {
    BYTE TargetAddress = FetchByte(cycles, memory);
    CPU6502::DoTick(cycles);
    return TargetAddress + offsetAddress;
}

ValueAddressRequest CPU6502::GetZeroPageAddressValue(U32 &cycles, Memory &memory, BYTE offsetAddress) {
    const BYTE TargetAddress = GetZeroPageAddress(cycles, memory, offsetAddress);
    const BYTE Value = CPU6502::ReadByte(cycles, memory, TargetAddress);
    return {Value, TargetAddress};
}

WORD CPU6502::GetAbsAddress(U32 &cycles, Memory &memory) {
    return FetchWord(cycles, memory);
}

ValueAddressRequest CPU6502::GetAbsAddressValue(U32 &cycles, Memory &memory) {
    const WORD TargetAddress = GetAbsAddress(cycles, memory);
    const BYTE Value = CPU6502::ReadByte(cycles, memory, TargetAddress);
    return {Value, TargetAddress};
}

WORD CPU6502::GetAbsAddress(U32 &cycles, Memory &memory, BYTE offsetAddress) {
    const WORD AbsAddress = FetchWord(cycles, memory);
    const WORD TargetAddress = AbsAddress + offsetAddress;
    if (CPU6502::isPageCrossed(TargetAddress, AbsAddress))
        CPU6502::DoTick(cycles);
    return TargetAddress;
}

ValueAddressRequest CPU6502::GetAbsAddressValue(U32 &cycles, Memory &memory, BYTE offsetAddress) {
    const WORD TargetAddress = GetAbsAddress(cycles, memory, offsetAddress);
    const BYTE Value = CPU6502::ReadByte(cycles, memory, TargetAddress);
    return {Value, TargetAddress};
}

WORD CPU6502::GetIndXAddress(U32 &cycles, Memory &memory) {
    BYTE TargetAddress = FetchByte(cycles, memory) + X;
    CPU6502::DoTick(cycles);
    return CPU6502::ReadWord(cycles, memory, TargetAddress);
}

ValueAddressRequest CPU6502::GetIndXAddressValue(U32 &cycles, Memory &memory) {
    const WORD TargetAddress = GetIndXAddress(cycles, memory);
    const BYTE Value = CPU6502::ReadByte(cycles, memory, TargetAddress);
    return {Value, TargetAddress};
}

WORD CPU6502::GetIndYAddress(U32 &cycles, Memory &memory) {
    BYTE ZeroPageAddress = FetchByte(cycles, memory);
    const WORD EffectiveAddress = CPU6502::ReadWord(cycles, memory, ZeroPageAddress);
    const WORD TargetAddress = EffectiveAddress + Y;
    if (CPU6502::isPageCrossed(TargetAddress, EffectiveAddress))
        CPU6502::DoTick(cycles);
    return TargetAddress;
}

ValueAddressRequest CPU6502::GetIndYAddressValue(U32 &cycles, Memory &memory) {
    const WORD TargetAddress = GetIndYAddress(cycles, memory);
    const BYTE Value = CPU6502::ReadByte(cycles, memory, TargetAddress);
    return {Value, TargetAddress};
}
