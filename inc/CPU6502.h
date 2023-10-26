#pragma once
#include <cstring>
#include "Types.h"
#include "Memory.h"
#include "CPU6502_Status.h"

#define PAGE_SIZE 0xFF
#define DoTick(x) ++x
#define IsPageCrossed(src, dst) ((src ^ dst) >= PAGE_SIZE)

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
        DoTick(cycles);
        return Data;
    }

    inline WORD FetchWord(U32 &cycles, const Memory &memory){
        BYTE Lo = ReadByte(cycles, memory, PC++);
        BYTE Hi = ReadByte(cycles, memory, PC++);
        return Lo | (Hi << 8);
    }

    inline static BYTE ReadByte(U32 &cycles, const Memory &memory, WORD address){
        BYTE Data = memory[address];
        DoTick(cycles);
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
        DoTick(cycles);
        memory[address + 1] = (value >> 8);
        DoTick(cycles);
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
        DoTick(cycles);
    }

    inline void PullStatusFromStack(U32 &cycles, Memory &memory){
        SP++;
        DoTick(cycles);
        Status = ReadByte(cycles, memory, StackPointerToAddress());
        DoTick(cycles);
    }

    inline void PushByteToStack(U32 &cycles, Memory &memory, BYTE value){
        WriteByte(cycles, memory, value, StackPointerToAddress());
        SP--;
        DoTick(cycles);
    }

    inline BYTE PullByteFromStack(U32 &cycles, Memory &memory){
        SP++;
        DoTick(cycles);
        const BYTE value = ReadByte(cycles, memory, StackPointerToAddress());
        DoTick(cycles);
        return value;
    }

    inline void PushWordToStack(U32 &cycles, Memory &memory, WORD value){
        WriteWord(cycles, memory, value, StackPointerToAddress() - 1);
        SP -= 2;
    }

    inline WORD PullWordFromStack(U32 &cycles, Memory &memory){
        WORD value = ReadWord(cycles, memory, StackPointerToAddress() + 1);
        DoTick(cycles);
        SP += 2;
        DoTick(cycles);
        return value;
    }

    inline BYTE GetZeroPageValue(U32 &cycles, Memory &memory){
        const BYTE TargetAddress = FetchByte(cycles, memory);
        return CPU6502::ReadByte(cycles, memory, TargetAddress);
    }

    inline ValueAddressRequest GetZeroPageAddressValue(U32 &cycles, Memory &memory){
        const BYTE TargetAddress = FetchByte(cycles, memory);
        const BYTE Value = CPU6502::ReadByte(cycles, memory, TargetAddress);
        return {Value, TargetAddress};
    }

    inline WORD GetZeroPageAddress(U32 &cycles, Memory &memory, BYTE offsetAddress){
        BYTE TargetAddress = FetchByte(cycles, memory);
        DoTick(cycles);
        return TargetAddress + offsetAddress;
    }

    inline BYTE GetZeroPageValue(U32 &cycles, Memory &memory, BYTE offsetAddress){
        const BYTE TargetAddress = GetZeroPageAddress(cycles, memory, offsetAddress);
        return CPU6502::ReadByte(cycles, memory, TargetAddress);
    }

    inline ValueAddressRequest GetZeroPageAddressValue(U32 &cycles, Memory &memory, BYTE offsetAddress){
        const BYTE TargetAddress = GetZeroPageAddress(cycles, memory, offsetAddress);
        const BYTE Value = CPU6502::ReadByte(cycles, memory, TargetAddress);
        return {Value, TargetAddress};
    }

    inline WORD GetAbsAddress(U32 &cycles, Memory &memory){
        return FetchWord(cycles, memory);
    }

    inline BYTE GetAbsValue(U32 &cycles, Memory &memory){
        const WORD TargetAddress = GetAbsAddress(cycles, memory);
        return CPU6502::ReadByte(cycles, memory, TargetAddress);
    }

    inline ValueAddressRequest GetAbsAddressValue(U32 &cycles, Memory &memory){
        const WORD TargetAddress = GetAbsAddress(cycles, memory);
        const BYTE Value = CPU6502::ReadByte(cycles, memory, TargetAddress);
        return {Value, TargetAddress};
    }

    inline WORD GetAbsAddress(U32 &cycles, Memory &memory, BYTE offsetAddress){
        const WORD AbsAddress = FetchWord(cycles, memory);
        const WORD TargetAddress = AbsAddress + offsetAddress;
        if (IsPageCrossed(TargetAddress, AbsAddress))
            DoTick(cycles);
        return TargetAddress;
    }

    inline BYTE GetAbsValue(U32 &cycles, Memory &memory, BYTE offsetAddress){
        const WORD TargetAddress = GetAbsAddress(cycles, memory, offsetAddress);
        return CPU6502::ReadByte(cycles, memory, TargetAddress);
    }

    inline ValueAddressRequest GetAbsAddressValue(U32 &cycles, Memory &memory, BYTE offsetAddress){
        const WORD TargetAddress = GetAbsAddress(cycles, memory, offsetAddress);
        const BYTE Value = CPU6502::ReadByte(cycles, memory, TargetAddress);
        return {Value, TargetAddress};
    }

    inline WORD GetIndXAddress(U32 &cycles, Memory &memory){
        BYTE TargetAddress = FetchByte(cycles, memory) + X;
        DoTick(cycles);
        return CPU6502::ReadWord(cycles, memory, TargetAddress);
    }

    inline BYTE GetIndXAddressValue(U32 &cycles, Memory &memory){
        const WORD TargetAddress = GetIndXAddress(cycles, memory);
        return CPU6502::ReadByte(cycles, memory, TargetAddress);
    }

    inline WORD GetIndYAddress(U32 &cycles, Memory &memory){
        BYTE ZeroPageAddress = FetchByte(cycles, memory);
        const WORD EffectiveAddress = CPU6502::ReadWord(cycles, memory, ZeroPageAddress);
        const WORD TargetAddress = EffectiveAddress + Y;
        if (IsPageCrossed(TargetAddress, EffectiveAddress))
            DoTick(cycles);
        return TargetAddress;
    }

    inline BYTE GetIndYAddressValue(U32 &cycles, Memory &memory){
        const WORD TargetAddress = GetIndYAddress(cycles, memory);
        return CPU6502::ReadByte(cycles, memory, TargetAddress);
    }
    
    [[nodiscard]] inline WORD StackPointerToAddress() const noexcept {
        return 0x100 | SP;
    }
};
