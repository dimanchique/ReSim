#pragma once

#include <cstdio>
#include <Types.h>
#include "CPU6502_OpHelpers.h"
#include "Memory.h"

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

    void Reset(Memory &memory) {
        PC = 0xFFFC;
        SP = 0x0100;

        A = X = Y = 0;
        C = Z = I = D = B = V = N = 0;

        memory.Reset();
    }

    BYTE FetchByte(S32 &Cycles, Memory &memory) {
        BYTE Data = memory[PC++];
        Cycles--;
        return Data;
    }

    WORD FetchWord(S32 &Cycles, Memory &memory) {
        // 6502 is little endian
        WORD Data = memory[PC++];
        Data |= (memory[PC++] << 8);

        Cycles -= 2;
        return Data;
    }

    void WriteWord(S32 &Cycles, WORD Value, U32 ADDR, Memory &memory) {
        memory[ADDR] = Value & 0xFF;
        memory[ADDR + 1] = (Value >> 8);
        Cycles -= 2;
    }

    BYTE ReadByte(S32 &Cycles, WORD ADDR, Memory &memory) const {
        BYTE Data = memory[ADDR];
        Cycles--;
        return Data;
    }

    WORD ReadWord(S32 &Cycles, WORD ADDR, Memory &memory) const {
        BYTE Lo = ReadByte(Cycles, ADDR, memory);
        BYTE Hi = ReadByte(Cycles, ADDR + 1, memory);
        return Lo | (Hi<<8);
    }

    S32 Run(S32 Cycles, Memory &memory) {
        const S32 CyclesRequested = Cycles;

        while (Cycles > 0) {
            BYTE Instruction = FetchByte(Cycles, memory);
            const auto res = FetchCommand(Cycles, Instruction, memory, *this);
            if (!res) {
                std::printf("Can't handle instruction 0x%x\n", Instruction);
                throw -1;
            }
        }

        const S32 NumCyclesUsed = CyclesRequested - Cycles;
        return NumCyclesUsed;
    }

    void LDASetStatus() {
        Z = (A == 0);
        N = (A & 0b10000000) > 0;
    }
};