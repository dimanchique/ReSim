#pragma once

#include <cstring>
#include "Types.h"
#include "CPU6502_Status.h"

struct Memory;

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
    void Reset(Memory &Memory);
    void Reset(WORD ResetVector, Memory& Memory);

    BYTE FetchByte(U32 &Cycles, const Memory &Memory);
    WORD FetchWord(U32 &Cycles, const Memory &Memory);

    static BYTE ReadByte(U32 &Cycles, const Memory &Memory, WORD ADDR) ;
    static WORD ReadWord(U32 &Cycles, const Memory &Memory, WORD ADDR) ;

    static void WriteByte(U32 &Cycles, Memory &Memory, BYTE Value, U32 ADDR);
    static void WriteWord(U32 &Cycles, Memory &Memory, WORD Value, U32 ADDR);

    void PushProgramCounterToStack(U32 &Cycles, Memory &Memory);
    WORD PopAddressFromStack(U32 &Cycles, Memory &Memory);

    void PushByteToStack(U32 &Cycles, Memory &Memory, BYTE Value);
    void PushWordToStack(U32 &Cycles, Memory &Memory, WORD Value);

    BYTE PullByteFromStack(U32 &Cycles, Memory &Memory);
    WORD PullWordFromStack(U32 &Cycles, Memory &Memory);

    U32 Run(Memory &Memory);

    inline static void DoTick(U32 &Cycles, U32 Count = 1) {
        Cycles += Count;
    }

    WORD StackPointerToAddress() const {
        return 0x100 | SP;
    }

    void SetStatusValue(BYTE& Register, BYTE CheckArgs){
        Status.UpdateStatus(Register, CheckArgs);
    }
};
