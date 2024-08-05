#pragma once

#include "I8080_Status.h"
#include "core/macro.h"
#include "base/compute.h"
#include "base/memory.h"
#include "function_library/content_manipulation.h"

#define STOP_OPCODE 0x08 // one of unused OpCodes so it's pretty much OK to use it a stop flag

class I8080 final: public Compute{
public:

    WORD PC;                                // Program Counter
    WORD SP;                                // Stack Pointer
    BYTE A;                                 // Accumulator
    I8080_Status Status;                    // Status Register
    DECLARE_PAIRED_REG(BYTE, WORD, B, C);   // Paired BC
    DECLARE_PAIRED_REG(BYTE, WORD, D, E);   // Paired DE
    DECLARE_PAIRED_REG(BYTE, WORD, H, L);   // Paired HL

    void Reset(Memory &memory) noexcept override;

    U32 Run(Memory &memory) override;

    FORCE_INLINE BYTE FetchByte(const Memory &memory) {
        const BYTE Data = memory[PC++];
        cycles += 3;
        return Data;
    }

    FORCE_INLINE WORD FetchWord(const Memory &memory) {
        const BYTE Lo = FetchByte(memory);
        const BYTE Hi = FetchByte(memory);
        return Hi | (Lo << 8);
    }

    FORCE_INLINE BYTE ReadByte(const Memory &memory, const WORD address) {
        const BYTE Data = memory[address];
        cycles += 3;
        return Data;
    }

    FORCE_INLINE WORD ReadWord(const Memory &memory, const WORD address) {
        const BYTE Lo = ReadByte(memory, address);
        const BYTE Hi = ReadByte(memory, address + 1);
        return Lo | (Hi << 8);
    }

    FORCE_INLINE void WriteByte(Memory &memory, const BYTE value, const WORD address) {
        memory[address] = value;
        cycles += 3;
    }

    FORCE_INLINE void WriteWord(Memory &memory, const WORD value, const WORD address) {
        WriteByte(memory, value & 0xFF, address);
        WriteByte(memory, (value >> 8), address + 1);
    }

    FORCE_INLINE void PushProgramCounterOntoStack(Memory &memory) {
        WriteByte(memory, (PC >> 8) & 0xFF, --SP);
        WriteByte(memory, PC & 0xFF, --SP);
        cycles++;
    }

    FORCE_INLINE void PushDataOntoStack(Memory &memory, const BYTE &lsb, const BYTE &msb) {
        WriteByte(memory, lsb, --SP);
        WriteByte(memory, msb, --SP);
        cycles++;
    }

    FORCE_INLINE void PopProgramCounterOffStack(Memory &memory) {
        PC = ReadWord(memory, SP);
        SP += 2;
    }

    FORCE_INLINE void PopDataOffStack(Memory &memory, BYTE* lsb, BYTE* msb) {
        *msb = ReadByte(memory, SP++);
        *lsb = ReadByte(memory, SP++);
    }
};
