#pragma once
#include <Types.h>
#include <cstdio>

struct Memory;

struct CPU6502 {
//****************************************************
//                        Main Registers            **
//****************************************************
    WORD PC;           // Program Counter           **
    WORD SP;           // Stack Pointer             **
    BYTE A;            // Accumulator               **
    BYTE X;            // X Index                   **
    BYTE Y;            // Y Index                   **
//****************************************************
//                        Processor Status          **
//****************************************************
    BYTE CF:1;         // Carry Flag                **
    BYTE ZF:1;         // Zero Flag                 **
    BYTE ID:1;         // Interrupt Disable         **
    BYTE DM:1;         // Decimal Mode              **
    BYTE BC:1;         // Break Command             **
    BYTE NU:1;         // Not Used                  **
    BYTE OF:1;         // Overflow Flag             **
    BYTE NF:1;         // Negative Flag             **
//****************************************************
//                        Functionality             **
//****************************************************

    void Reset(Memory& memory);
    WORD Run(Memory& memory);

    BYTE FetchByte(Memory& memory);
    BYTE ReadByte(BYTE ADDR, Memory& memory) const;

    WORD FetchWord(Memory& memory);
    void WriteWord(WORD Value, U32 ADDR, Memory& memory);

    void LDASetStatus(){
        ZF = (A == 0);
        NF = (A & 0b10000000) > 0;
    }
};