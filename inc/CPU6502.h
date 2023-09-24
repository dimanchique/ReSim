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
    void Reset(Memory& memory, WORD ResetVector = 0xFFFC);

    U32 Run(Memory &memory);

    BYTE FetchByte(U32 &cycles, const Memory &memory);
    WORD FetchWord(U32 &cycles, const Memory &memory);

    static BYTE ReadByte(U32 &cycles, const Memory &memory, WORD ADDR);
    static WORD ReadWord(U32 &cycles, const Memory &memory, WORD ADDR);

    static void WriteByte(U32 &cycles, Memory &memory, BYTE value, U32 ADDR);
    static void WriteWord(U32 &cycles, Memory &memory, WORD value, U32 ADDR);

    void PushProgramCounterToStack(U32 &cycles, Memory &memory);
    WORD PullAddressFromStack(U32 &cycles, Memory &memory);

    void PushStatusToStack(U32 &cycles, Memory &memory);
    void PullStatusFromStack(U32 &cycles, Memory &memory);

    void PushByteToStack(U32 &cycles, Memory &memory, BYTE value);
    BYTE PullByteFromStack(U32 &cycles, Memory &memory);

    void PushWordToStack(U32 &cycles, Memory &memory, WORD value);
    WORD PullWordFromStack(U32 &cycles, Memory &memory);

    ValueAddressRequest GetImmediateAddressValue(U32 &cycles, Memory &memory);
    BYTE GetZeroPageAddress(U32 &cycles, Memory &memory);
    ValueAddressRequest GetZeroPageAddressValue(U32 &cycles, Memory &memory);
    WORD GetZeroPageAddress(U32 &cycles, Memory &memory, BYTE offsetAddress);
    ValueAddressRequest GetZeroPageAddressValue(U32 &cycles, Memory &memory, BYTE offsetAddress);
    WORD GetAbsAddress(U32 &cycles, Memory &memory);
    ValueAddressRequest GetAbsAddressValue(U32 &cycles, Memory &memory);
    ValueAddressRequest GetAbsAddressValue(U32 &cycles, Memory &memory, BYTE offsetAddress);
    WORD GetAbsAddress(U32 &cycles, Memory &memory, BYTE offsetAddress);
    WORD GetIndXAddress(U32 &cycles, Memory &memory);
    ValueAddressRequest GetIndXAddressValue(U32 &cycles, Memory &memory);
    WORD GetIndYAddress(U32 &cycles, Memory &memory);
    ValueAddressRequest GetIndYAddressValue(U32 &cycles, Memory &memory);

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
