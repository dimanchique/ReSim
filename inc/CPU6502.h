#pragma once
#include "Types.h"

struct Memory;

struct CPU6502 {
//****************************************************
//                        Main Registers            **
//****************************************************
    WORD PC;           // Program Counter           **
    BYTE SP;           // Stack Pointer             **
    BYTE A;            // Accumulator               **
    BYTE X;            // X Index                   **
    BYTE Y;            // Y Index                   **
//****************************************************
//                        Processor Status          **
//****************************************************
    BYTE C:  1;        // Carry Flag                **
    BYTE Z:  1;        // Zero Flag                 **
    BYTE I:  1;        // Interrupt Disable         **
    BYTE D:  1;        // Decimal Mode              **
    BYTE B:  1;        // Break Command             **
    BYTE NU: 1;        // Not Used                  **
    BYTE V:  1;        // Overflow Flag             **
    BYTE N:  1;        // Negative Flag             **
//****************************************************
//                        Functionality             **
//****************************************************

    void Reset(Memory &memory);
    void Reset(WORD ResetVector, Memory& memory);
    void SoftReset(Memory& memory);
    void SoftReset(WORD ResetVector, Memory& memory);

    BYTE FetchByte(S32 &cycles, const Memory &memory);
    WORD FetchWord(S32 &cycles, const Memory &memory);

    BYTE ReadByte(S32 &cycles, const Memory &memory, WORD ADDR) const;
    WORD ReadWord(S32 &cycles, const Memory &memory, WORD ADDR) const;

    void WriteByte(S32 &cycles, Memory &memory, BYTE Value, U32 ADDR);
    void WriteWord(S32 &cycles, Memory &memory, WORD Value, U32 ADDR);

    void PushProgramCounterToStack(S32 &Cycles, Memory &memory);
    WORD PopAddressFromStack(S32 &Cycles, Memory &Memory);

    WORD StackPointerToAddress() const{
        return 0x100 | SP;
    }

    S32 Run(S32 cycles, Memory &memory);
    void LoadRegisterSetStatus(BYTE& Register);
};
