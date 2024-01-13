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

    FORCE_INLINE void PushProgramCounterToStack(Memory &memory) {
        PushWordToStack(memory, PC - 1);
    }

    FORCE_INLINE WORD PopAddressFromStack(const Memory &memory) {
        return PopWordFromStack(memory) + 1;
    }

    FORCE_INLINE void PushStatusToStack(Memory &memory) {
        WriteByte(memory, Status, SP);
        SP--;
        cycles++;
    }

    FORCE_INLINE void PopStatusFromStack(const Memory &memory) {
        SP++;
        cycles++;
        Status = ReadByte(memory, SP);
        cycles++;
    }

    FORCE_INLINE void PushByteToStack(Memory &memory, const BYTE value) {
        WriteByte(memory, value, SP);
        SP--;
        cycles++;
    }

    FORCE_INLINE BYTE PopByteFromStack(const Memory &memory) {
        SP++;
        cycles++;
        const BYTE value = ReadByte(memory, SP);
        cycles++;
        return value;
    }

    FORCE_INLINE void PushWordToStack(Memory &memory, const WORD value) {
        WriteWord(memory, value, SP - 1);
        SP -= 2;
    }

    FORCE_INLINE WORD PopWordFromStack(const Memory &memory) {
        const WORD value = ReadWord(memory, SP + 1);
        cycles++;
        SP += 2;
        cycles++;
        return value;
    }

    static FORCE_INLINE WORD SwapRegistersAsWord(BYTE& lsbReg, BYTE& msbReg) {
        WORD value = 0;
        value |= lsbReg << 8;
        value |= msbReg;
        return value;
    }

    static FORCE_INLINE void SwapWordToRegisters(WORD value, BYTE& lsbReg, BYTE& msbReg) {
        msbReg = value & 0xFF;
        lsbReg = (value >> 8) & 0xFF;
    }
};
