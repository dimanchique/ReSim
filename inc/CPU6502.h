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

    BYTE FetchByte(S32 &Cycles, const Memory &memory);
    WORD FetchWord(S32 &Cycles, const Memory &memory);

    S32 Run(S32 Cycles, Memory &memory);
    void LoadRegisterSetStatus(BYTE& Register);
};
