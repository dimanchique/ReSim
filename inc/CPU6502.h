#pragma once
#include <cstring>
#include "Types.h"
#include "Memory.h"
#include "CPU6502_Status.h"

struct CPU6502 {

//  Registers
    WORD PC;                // Program Counter
    BYTE SP;                // Stack Pointer
    BYTE A;                 // Accumulator
    BYTE X;                 // X Index
    BYTE Y;                 // Y Index
    CPU6502_Status Status;

//  Functions
    void Reset(Memory& memory, WORD ResetVector = 0xFFFC) noexcept;

    U32 Run(Memory &memory);

    inline BYTE FetchByte(U32 &cycles, const Memory &memory){
        BYTE Data = memory[PC++];
        CPU6502::DoTick(cycles);
        return Data;
    }

    inline WORD FetchWord(U32 &cycles, const Memory &memory){
        BYTE Lo = ReadByte(cycles, memory, PC++);
        BYTE Hi = ReadByte(cycles, memory, PC++);
        return Lo | (Hi << 8);
    }

    inline static BYTE ReadByte(U32 &cycles, const Memory &memory, WORD address){
        BYTE Data = memory[address];
        CPU6502::DoTick(cycles);
        return Data;
    }

    inline static WORD ReadWord(U32 &cycles, const Memory &memory, WORD address){
        BYTE Lo = ReadByte(cycles, memory, address);
        BYTE Hi = ReadByte(cycles, memory, address + 1);
        return Lo | (Hi << 8);
    }

    inline static void WriteByte(U32 &cycles, Memory &memory, BYTE value, U32 address){
        memory[address] = value;
        cycles++;
    }

    inline static void WriteWord(U32 &cycles, Memory &memory, WORD value, U32 address){
        memory[address] = value & 0xFF;
        CPU6502::DoTick(cycles);
        memory[address + 1] = (value >> 8);
        CPU6502::DoTick(cycles);
    }

    inline void PushProgramCounterToStack(U32 &cycles, Memory &memory){
        PushWordToStack(cycles, memory, PC - 1);
    }

    inline WORD PullAddressFromStack(U32 &cycles, Memory &memory){
        return PullWordFromStack(cycles, memory) + 1;
    }

    inline void PushStatusToStack(U32 &cycles, Memory &memory){
        WriteByte(cycles, memory, Status, StackPointerToAddress());
        SP--;
        CPU6502::DoTick(cycles);
    }

    inline void PullStatusFromStack(U32 &cycles, Memory &memory){
        SP++;
        CPU6502::DoTick(cycles);
        Status = ReadByte(cycles, memory, StackPointerToAddress());
        CPU6502::DoTick(cycles);
    }

    inline void PushByteToStack(U32 &cycles, Memory &memory, BYTE value){
        WriteByte(cycles, memory, value, StackPointerToAddress());
        SP--;
        CPU6502::DoTick(cycles);
    }

    inline BYTE PullByteFromStack(U32 &cycles, Memory &memory){
        SP++;
        CPU6502::DoTick(cycles);
        const BYTE value = ReadByte(cycles, memory, StackPointerToAddress());
        CPU6502::DoTick(cycles);
        return value;
    }

    inline void PushWordToStack(U32 &cycles, Memory &memory, WORD value){
        WriteWord(cycles, memory, value, StackPointerToAddress() - 1);
        SP -= 2;
    }

    inline WORD PullWordFromStack(U32 &cycles, Memory &memory){
        WORD value = ReadWord(cycles, memory, StackPointerToAddress() + 1);
        CPU6502::DoTick(cycles);
        SP += 2;
        CPU6502::DoTick(cycles);
        return value;
    }

    inline ValueAddressRequest GetImmediateAddressValue(U32 &cycles, Memory &memory){
        const BYTE Value = FetchByte(cycles, memory);
        return {Value, PC};
    }

    inline BYTE GetZeroPageAddress(U32 &cycles, Memory &memory){
        return FetchByte(cycles, memory);
    }

    inline ValueAddressRequest GetZeroPageAddressValue(U32 &cycles, Memory &memory){
        const BYTE TargetAddress = GetZeroPageAddress(cycles, memory);
        const BYTE Value = CPU6502::ReadByte(cycles, memory, TargetAddress);
        return {Value, TargetAddress};
    }

    inline WORD GetZeroPageAddress(U32 &cycles, Memory &memory, BYTE offsetAddress){
        BYTE TargetAddress = FetchByte(cycles, memory);
        CPU6502::DoTick(cycles);
        return TargetAddress + offsetAddress;
    }

    inline ValueAddressRequest GetZeroPageAddressValue(U32 &cycles, Memory &memory, BYTE offsetAddress){
        const BYTE TargetAddress = GetZeroPageAddress(cycles, memory, offsetAddress);
        const BYTE Value = CPU6502::ReadByte(cycles, memory, TargetAddress);
        return {Value, TargetAddress};
    }

    inline WORD GetAbsAddress(U32 &cycles, Memory &memory){
        return FetchWord(cycles, memory);
    }

    inline ValueAddressRequest GetAbsAddressValue(U32 &cycles, Memory &memory){
        const WORD TargetAddress = GetAbsAddress(cycles, memory);
        const BYTE Value = CPU6502::ReadByte(cycles, memory, TargetAddress);
        return {Value, TargetAddress};
    }

    inline WORD GetAbsAddress(U32 &cycles, Memory &memory, BYTE offsetAddress){
        const WORD AbsAddress = FetchWord(cycles, memory);
        const WORD TargetAddress = AbsAddress + offsetAddress;
        if (CPU6502::IsPageCrossed(TargetAddress, AbsAddress))
            CPU6502::DoTick(cycles);
        return TargetAddress;
    }

    inline ValueAddressRequest GetAbsAddressValue(U32 &cycles, Memory &memory, BYTE offsetAddress){
        const WORD TargetAddress = GetAbsAddress(cycles, memory, offsetAddress);
        const BYTE Value = CPU6502::ReadByte(cycles, memory, TargetAddress);
        return {Value, TargetAddress};
    }

    inline WORD GetIndXAddress(U32 &cycles, Memory &memory){
        BYTE TargetAddress = FetchByte(cycles, memory) + X;
        CPU6502::DoTick(cycles);
        return CPU6502::ReadWord(cycles, memory, TargetAddress);
    }

    inline ValueAddressRequest GetIndXAddressValue(U32 &cycles, Memory &memory){
        const WORD TargetAddress = GetIndXAddress(cycles, memory);
        const BYTE Value = CPU6502::ReadByte(cycles, memory, TargetAddress);
        return {Value, TargetAddress};
    }

    inline WORD GetIndYAddress(U32 &cycles, Memory &memory){
        BYTE ZeroPageAddress = FetchByte(cycles, memory);
        const WORD EffectiveAddress = CPU6502::ReadWord(cycles, memory, ZeroPageAddress);
        const WORD TargetAddress = EffectiveAddress + Y;
        if (CPU6502::IsPageCrossed(TargetAddress, EffectiveAddress))
            CPU6502::DoTick(cycles);
        return TargetAddress;
    }

    inline ValueAddressRequest GetIndYAddressValue(U32 &cycles, Memory &memory){
        const WORD TargetAddress = GetIndYAddress(cycles, memory);
        const BYTE Value = CPU6502::ReadByte(cycles, memory, TargetAddress);
        return {Value, TargetAddress};
    }

    inline static void DoTick(U32 &cycles, U32 count = 1) noexcept {
        cycles += count;
    }

    inline static bool IsPageCrossed(WORD src, WORD dest) noexcept {
        return (src ^ dest) >= PAGE_SIZE;
    }

    [[nodiscard]] inline WORD StackPointerToAddress() const noexcept {
        return 0x100 | SP;
    }
};
