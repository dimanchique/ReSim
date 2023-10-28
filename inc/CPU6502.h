#pragma once
#include <cstring>
#include "Types.h"
#include "Memory.h"
#include "CPU6502_Status.h"

#define PAGE_SIZE 0xFF
#define IsPageCrossed(src, dst) ((src ^ dst) >= PAGE_SIZE)

struct CPU6502 {

//  Registers
    WORD PC;                // Program Counter
    BYTE SP;                // Stack Pointer
    BYTE A;                 // Accumulator
    BYTE X;                 // X Index
    BYTE Y;                 // Y Index
    CPU6502_Status Status;

    U32 cycles;

//  Functions
    void Reset(Memory& memory, WORD ResetVector = 0xFFFC) noexcept;

    U32 Run(Memory &memory);

    inline BYTE FetchByte(const Memory &memory){
        BYTE Data = memory[PC++];
        cycles++;
        return Data;
    }

    inline WORD FetchWord(const Memory &memory){
        BYTE Lo = ReadByte(memory, PC++);
        BYTE Hi = ReadByte(memory, PC++);
        return Lo | (Hi << 8);
    }

    inline BYTE ReadByte(const Memory &memory, WORD address){
        BYTE Data = memory[address];
        cycles++;
        return Data;
    }

    inline WORD ReadWord(const Memory &memory, WORD address){
        BYTE Lo = ReadByte(memory, address);
        BYTE Hi = ReadByte(memory, address + 1);
        return Lo | (Hi << 8);
    }

    inline void WriteByte(Memory &memory, BYTE value, U32 address){
        memory[address] = value;
        cycles++;
    }

    inline  void WriteWord(Memory &memory, WORD value, U32 address){
        memory[address] = value & 0xFF;
        cycles++;
        memory[address + 1] = (value >> 8);
        cycles++;
    }

    inline void PushProgramCounterToStack(Memory &memory){
        PushWordToStack(memory, PC - 1);
    }

    inline WORD PopAddressFromStack(Memory &memory){
        return PopWordFromStack(memory) + 1;
    }

    inline void PushStatusToStack(Memory &memory){
        WriteByte(memory, Status, StackPointerToAddress());
        SP--;
        cycles++;
    }

    inline void PopStatusFromStack(Memory &memory){
        SP++;
        cycles++;
        Status = ReadByte(memory, StackPointerToAddress());
        cycles++;
    }

    inline void PushByteToStack(Memory &memory, BYTE value){
        WriteByte(memory, value, StackPointerToAddress());
        SP--;
        cycles++;
    }

    inline BYTE PopByteFromStack(Memory &memory){
        SP++;
        cycles++;
        const BYTE value = ReadByte(memory, StackPointerToAddress());
        cycles++;
        return value;
    }

    inline void PushWordToStack(Memory &memory, WORD value){
        WriteWord(memory, value, StackPointerToAddress() - 1);
        SP -= 2;
    }

    inline WORD PopWordFromStack(Memory &memory){
        WORD value = ReadWord(memory, StackPointerToAddress() + 1);
        cycles++;
        SP += 2;
        cycles++;
        return value;
    }

    inline BYTE GetZeroPageValue(Memory &memory){
        const BYTE TargetAddress = FetchByte(memory);
        return ReadByte(memory, TargetAddress);
    }

    inline ValueAddressRequest GetZeroPageAddressValue(Memory &memory){
        const BYTE TargetAddress = FetchByte(memory);
        const BYTE Value = ReadByte(memory, TargetAddress);
        return {Value, TargetAddress};
    }

    inline WORD GetZeroPageAddress(Memory &memory, BYTE offsetAddress){
        BYTE TargetAddress = FetchByte(memory);
        cycles++;
        return TargetAddress + offsetAddress;
    }

    inline BYTE GetZeroPageValue(Memory &memory, BYTE offsetAddress){
        const BYTE TargetAddress = GetZeroPageAddress(memory, offsetAddress);
        return ReadByte(memory, TargetAddress);
    }

    inline ValueAddressRequest GetZeroPageAddressValue(Memory &memory, BYTE offsetAddress){
        const BYTE TargetAddress = GetZeroPageAddress(memory, offsetAddress);
        const BYTE Value = ReadByte(memory, TargetAddress);
        return {Value, TargetAddress};
    }

    inline BYTE GetAbsValue(Memory &memory){
        const WORD TargetAddress = FetchWord(memory);
        return ReadByte(memory, TargetAddress);
    }

    inline ValueAddressRequest GetAbsAddressValue(Memory &memory){
        const WORD TargetAddress = FetchWord(memory);
        const BYTE Value = ReadByte(memory, TargetAddress);
        return {Value, TargetAddress};
    }

    inline WORD GetAbsAddress(Memory &memory, BYTE offsetAddress){
        const WORD AbsAddress = FetchWord(memory);
        const WORD TargetAddress = AbsAddress + offsetAddress;
        if (IsPageCrossed(TargetAddress, AbsAddress))
            cycles++;
        return TargetAddress;
    }

    inline BYTE GetAbsValue(Memory &memory, BYTE offsetAddress){
        const WORD TargetAddress = GetAbsAddress(memory, offsetAddress);
        return ReadByte(memory, TargetAddress);;
    }

    inline ValueAddressRequest GetAbsAddressValue(Memory &memory, BYTE offsetAddress){
        const WORD TargetAddress = GetAbsAddress(memory, offsetAddress);
        const BYTE Value = ReadByte(memory, TargetAddress);
        return {Value, TargetAddress};
    }

    inline WORD GetIndXAddress(Memory &memory){
        BYTE TargetAddress = FetchByte(memory) + X;
        cycles++;
        return ReadWord(memory, TargetAddress);
    }

    inline BYTE GetIndXAddressValue(Memory &memory){
        const WORD TargetAddress = GetIndXAddress(memory);
        return ReadByte(memory, TargetAddress);
    }

    inline WORD GetIndYAddress(Memory &memory){
        BYTE ZeroPageAddress = FetchByte(memory);
        const WORD EffectiveAddress = ReadWord(memory, ZeroPageAddress);
        const WORD TargetAddress = EffectiveAddress + Y;
        if (IsPageCrossed(TargetAddress, EffectiveAddress))
            cycles++;
        return TargetAddress;
    }

    inline BYTE GetIndYAddressValue(Memory &memory){
        const WORD TargetAddress = GetIndYAddress(memory);
        return ReadByte(memory, TargetAddress);;
    }
    
    [[nodiscard]] inline WORD StackPointerToAddress() const noexcept {
        return 0x100 + SP;
    }
};
