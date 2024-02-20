#pragma once

#include "Macro.h"
#include "I8080_Status.h"
#include "CPU_Base.h"
#include "Memory.h"

#define PAGE_SIZE 0xFF
#define IsPageCrossed(src, dst) ((src ^ dst) >= PAGE_SIZE)

class I8080 final: public CPU_Base{
public:

    WORD PC;                // Program Counter
    WORD SP;                // Stack Pointer
    BYTE A;                 // Accumulator
    BYTE B;                 // Paired BC
    BYTE C;                 //
    BYTE D;                 // Paired DE
    BYTE E;                 //
    BYTE H;                 // Paired HL
    BYTE L;                 //
    I8080_Status Status;    // Status Register

    void Reset(Memory &memory, WORD resetVector) noexcept override;

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

    FORCE_INLINE void PushDataOntoStack(Memory &memory, const BYTE& lsb, const BYTE& msb) {
        WriteByte(memory, lsb, --SP);
        WriteByte(memory, msb, --SP);
        cycles++;
    }

    FORCE_INLINE void PopProgramCounterOffStack(Memory &memory) {
        PC = ReadWord(memory, SP);
        SP += 2;
    }

    template<typename T>
    FORCE_INLINE void PopDataOffStack(Memory &memory, BYTE& lsb, T& msb) {
        msb = ReadByte(memory, SP++);
        lsb = ReadByte(memory, SP++);
        cycles++;
    }

    static FORCE_INLINE WORD wordRegisterAsWordSwapped(const BYTE& lsbReg, const BYTE& msbReg) {
        WORD value = 0;
        value |= lsbReg << 8;
        value |= msbReg;
        return value;
    }

    static FORCE_INLINE WORD* wordRegisterAsWordUnswapped(BYTE& lsbReg) {
        return reinterpret_cast<WORD*>(&lsbReg);
    }

    static FORCE_INLINE void wordToRegisterSwapped(const WORD value, BYTE& lsbReg, BYTE& msbReg) {
        msbReg = value & 0xFF;
        lsbReg = (value >> 8) & 0xFF;
    }

    static FORCE_INLINE void wordToRegisterUnswapped(const WORD value, BYTE& lsbReg) {
        *reinterpret_cast<WORD*>(&lsbReg) = value;
    }
};
