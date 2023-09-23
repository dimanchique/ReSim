#pragma once

#include <cstring>
#include "Types.h"
#include "Memory.h"
#include "CPU6502_Status.h"

struct CPU6502 {
//**********************************************************
//                          Registers
//**********************************************************
    WORD PC;                // Program Counter
    BYTE SP;                // Stack Pointer
    BYTE A;                 // Accumulator
    BYTE X;                 // X Index
    BYTE Y;                 // Y Index
    CPU6502_Status Status;
//**********************************************************
//                          Functions
//**********************************************************
    void Reset(Memory &memory);
    void Reset(WORD ResetVector, Memory& memory);

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

    inline static BYTE ReadByte(U32 &cycles, const Memory &memory, WORD ADDR){
        BYTE Data = memory[ADDR];
        CPU6502::DoTick(cycles);
        return Data;
    }

    inline static WORD ReadWord(U32 &cycles, const Memory &memory, WORD ADDR){
        BYTE Lo = ReadByte(cycles, memory, ADDR);
        BYTE Hi = ReadByte(cycles, memory, ADDR + 1);
        return Lo | (Hi << 8);
    }

    inline static void WriteByte(U32 &cycles, Memory &memory, BYTE value, U32 ADDR){
        memory[ADDR] = value;
        cycles++;
    }

    inline static void WriteWord(U32 &cycles, Memory &memory, WORD value, U32 ADDR){
        memory[ADDR] = value & 0xFF;
        CPU6502::DoTick(cycles);
        memory[ADDR + 1] = (value >> 8);
        CPU6502::DoTick(cycles);
    }

    void PushProgramCounterToStack(U32 &cycles, Memory &memory){
        PushWordToStack(cycles, memory, PC - 1);
    }

    WORD PopAddressFromStack(U32 &cycles, Memory &memory){
        return PullWordFromStack(cycles, memory) + 1;
    }

    inline void PushByteToStack(U32 &cycles, Memory &memory, BYTE value){
        WriteByte(cycles, memory, value, StackPointerToAddress());
        SP--;
        CPU6502::DoTick(cycles);
    }

    inline void PushWordToStack(U32 &cycles, Memory &memory, WORD value){
        WriteWord(cycles, memory, value, StackPointerToAddress() - 1);
        SP -= 2;
    }

    inline BYTE PullByteFromStack(U32 &cycles, Memory &memory){
        SP++;
        CPU6502::DoTick(cycles);
        const BYTE value = ReadByte(cycles, memory, StackPointerToAddress());
        CPU6502::DoTick(cycles);
        return value;
    }

    inline WORD PullWordFromStack(U32 &cycles, Memory &memory){
        WORD value = ReadWord(cycles, memory, StackPointerToAddress() + 1);
        CPU6502::DoTick(cycles);
        SP += 2;
        CPU6502::DoTick(cycles);
        return value;
    }

    inline static void DoTick(U32 &cycles, U32 Count = 1) {
        cycles += Count;
    }

    inline static bool isPageCrossed(WORD src, WORD dest){
        return (src ^ dest) >= PAGE_SIZE;
    }

    [[nodiscard]] inline WORD StackPointerToAddress() const {
        return 0x100 | SP;
    }
};
