#pragma once
#include <cstring>
#include "Types.h"
#include "Memory.h"
#include "CPU6502_Status.h"

#define PAGE_SIZE 0xFF
#define IsPageCrossed(src, dst) ((src ^ dst) >= PAGE_SIZE)

struct CPU6502 {

    WORD PC;                // Program Counter
    BYTE SP;                // Stack Pointer
    BYTE A;                 // Accumulator
    BYTE X;                 // X Register
    BYTE Y;                 // Y Register
    CPU6502_Status Status;  // Status Register

    U32 cycles;             // Cycles counter

    /**
     * @description Resets CPU registers and Stack Pointer to it's default values.
     * Program Counter value after reset depends on ResetVector value.
     * @param memory Memory struct instance
     * @param resetVector Program Counter (PC) value after reset. Default is 0xFFFC
     */
    void Reset(Memory &memory, WORD resetVector = 0xFFFC) noexcept;

    /**
     * @description Main 6502 running function. Stop looping if 0xFF or FAKE_NOP instruction fetched
     * @param memory Memory struct instance
     * @return Cycles count
     */
    U32 Run(Memory &memory);

    /**
     * @description Fetch byte from memory.
     * @attention Increments PC. Increments cycles count.
     * @param memory Memory struct instance
     * @return Fetched byte
     */
    inline BYTE FetchByte(const Memory &memory) {
        BYTE Data = memory[PC++];
        cycles++;
        return Data;
    }

    /**
     * @description Fetch word from memory.
     * @attention Increments PC (x2). Increments cycles count (x2).
     * @param memory Memory struct instance
     * @return Fetched word
     */
    inline WORD FetchWord(const Memory &memory) {
        BYTE Lo = FetchByte(memory);
        BYTE Hi = FetchByte(memory);
        return Lo | (Hi << 8);
    }

    /**
     * @description Read byte from memory.
     * @attention Increments cycles count.
     * @param memory Memory struct instance
     * @param address Address to read from
     * @return Read byte
     */
    inline BYTE ReadByte(const Memory &memory, WORD address) {
        BYTE Data = memory[address];
        cycles++;
        return Data;
    }

    /**
     * @description Read word from memory.
     * @attention Increments cycles count (x2).
     * @param memory Memory struct instance
     * @param address Address to read from
     * @return Read word
     */
    inline WORD ReadWord(const Memory &memory, WORD address) {
        BYTE Lo = ReadByte(memory, address);
        BYTE Hi = ReadByte(memory, address + 1);
        return Lo | (Hi << 8);
    }

    /**
     * @description Write byte to memory.
     * @attention Increments cycles count.
     * @param memory Memory struct instance
     * @param value Value to write
     * @param address Address to write to
     */
    inline void WriteByte(Memory &memory, BYTE value, WORD address) {
        memory[address] = value;
        cycles++;
    }

    /**
     * @description Write word to memory.
     * @attention Increments cycles count (x2).
     * @param memory Memory struct instance
     * @param value Value to write
     * @param address Address to write to
     */
    inline void WriteWord(Memory &memory, WORD value, WORD address) {
        memory[address] = value & 0xFF;
        cycles++;
        memory[address + 1] = (value >> 8);
        cycles++;
    }

    /**
     * @description Push Program Counter (PC) register value to stack.
     * @attention Increments cycles count (x2). Decrements Stack Pointer (x2).
     * @param memory Memory struct instance
     */
    inline void PushProgramCounterToStack(Memory &memory) {
        PushWordToStack(memory, PC - 1);
    }

    /**
     * @description Pop address from stack.
     * @attention Increments cycles count (x2). Increments Stack Pointer (x2).
     * @param memory Memory struct instance
     * @return Popped address
     */
    inline WORD PopAddressFromStack(Memory &memory) {
        return PopWordFromStack(memory) + 1;
    }

    /**
     * @description Push Status register value to stack.
     * @attention Increments cycles count (x2). Decrements Stack Pointer.
     * @param memory Memory struct instance
     */
    inline void PushStatusToStack(Memory &memory) {
        WriteByte(memory, Status, StackPointerToAddress());
        SP--;
        cycles++;
    }

    /**
     * @description Pop Status register value from stack.
     * @attention Increments cycles count (x3). Increments Stack Pointer.
     * @param memory Memory struct instance
     */
    inline void PopStatusFromStack(Memory &memory) {
        SP++;
        cycles++;
        Status = ReadByte(memory, StackPointerToAddress());
        cycles++;
    }

    /**
     * @description Push byte to stack.
     * @attention Increments cycles count (x2). Decrements Stack Pointer.
     * @param memory Memory struct instance
     * @param value Value to push to stack
     */
    inline void PushByteToStack(Memory &memory, BYTE value) {
        WriteByte(memory, value, StackPointerToAddress());
        SP--;
        cycles++;
    }

    /**
     * @description Pop byte from stack.
     * @attention Increments cycles count (x3). Increments Stack Pointer.
     * @param memory Memory struct instance
     * @return Popped value
     */
    inline BYTE PopByteFromStack(Memory &memory) {
        SP++;
        cycles++;
        const BYTE value = ReadByte(memory, StackPointerToAddress());
        cycles++;
        return value;
    }

    /**
     * @description Push word to stack.
     * @attention Increments cycles count (x2). Decrements Stack Pointer (x2).
     * @param memory Memory struct instance
     * @param value Value to push to stack
     */
    inline void PushWordToStack(Memory &memory, WORD value) {
        WriteWord(memory, value, StackPointerToAddress() - 1);
        SP -= 2;
    }

    /**
     * @description Pop word from stack.
     * @attention Increments cycles count (x4). Increments Stack Pointer (x2).
     * @param memory Memory struct instance
     * @return Popped value
     */
    inline WORD PopWordFromStack(Memory &memory) {
        WORD value = ReadWord(memory, StackPointerToAddress() + 1);
        cycles++;
        SP += 2;
        cycles++;
        return value;
    }

    /**
     * @description Get value using ZeroPage addressing mode.
     * @note Call FetchByte
     * @note Call ReadByte using fetched byte as ZeroPage address
     * @attention Increments cycles count (x2). Increments PC.
     * @param memory Memory struct instance
     * @return Zero Page address value
     */
    inline BYTE GetZeroPageValue(Memory &memory) {
        const BYTE TargetAddress = FetchByte(memory);
        return ReadByte(memory, TargetAddress);
    }

    /**
     * @description Get address and value using ZeroPage addressing mode.
     * @note Call FetchByte
     * @note Call ReadByte using fetched byte as ZeroPage address
     * @attention Increments cycles count (x2). Increments PC.
     * @param memory Memory struct instance
     * @return {Value, TargetAddress}
     */
    inline ValueAddressRequest GetZeroPageAddressValue(Memory &memory) {
        const BYTE TargetAddress = FetchByte(memory);
        const BYTE Value = ReadByte(memory, TargetAddress);
        return {Value, TargetAddress};
    }

    /**
     * @description Get generic ZeroPage address.
     * @note Call FetchByte
     * @note Add offset to fetched byte to get generic ZeroPage address
     * @attention Increments cycles count. Increments PC.
     * @note Addressing mode: Zero Page,X.
     * @note Addressing mode: Zero Page,Y.
     * @param memory Memory struct instance
     * @param offsetAddress Offset memory address value
     * @return generic ZeroPage address
     */
    inline WORD GetZeroPageAddress(Memory &memory, BYTE offsetAddress) {
        BYTE TargetAddress = FetchByte(memory);
        cycles++;
        return TargetAddress + offsetAddress;
    }

    /**
     * @description Get generic ZeroPage value.
     * @note Call FetchByte
     * @note Add offset to fetched byte to get generic ZeroPage address
     * @note Call ReadByte using generic ZeroPage address
     * @attention Increments cycles count. Increments PC.
     * @addressing Zero Page,X; Zero Page,Y.
     * @param memory Memory struct instance
     * @param offsetAddress Offset memory address value
     * @return generic ZeroPage value
     */
    inline BYTE GetZeroPageValue(Memory &memory, BYTE offsetAddress) {
        const BYTE TargetAddress = GetZeroPageAddress(memory, offsetAddress);
        return ReadByte(memory, TargetAddress);
    }

    /**
     * @description Get generic ZeroPage address and value.
     * @note Call FetchByte
     * @note Add offset to fetched byte to get generic ZeroPage address
     * @note Call ReadByte using generic ZeroPage address
     * @attention Increments cycles count. Increments PC.
     * @addressing Zero Page,X; Zero Page,Y.
     * @param memory Memory struct instance
     * @param offsetAddress Offset memory address value
     * @return {Value, TargetAddress}
     */
    inline ValueAddressRequest GetZeroPageAddressValue(Memory &memory, BYTE offsetAddress) {
        const BYTE TargetAddress = GetZeroPageAddress(memory, offsetAddress);
        const BYTE Value = ReadByte(memory, TargetAddress);
        return {Value, TargetAddress};
    }

    /**
     * @description Get value using Absolute addressing mode.
     * @note Call FetchWord
     * @note Call ReadByte using fetched word address
     * @attention Increments cycles count (x3). Increments PC (x2).
     * @param memory Memory struct instance
     * @return Absolute address value
     */
    inline BYTE GetAbsValue(Memory &memory) {
        const WORD TargetAddress = FetchWord(memory);
        return ReadByte(memory, TargetAddress);
    }

    /**
     * @description Get address and value using Absolute addressing mode.
     * @note Call FetchWord
     * @note Call ReadByte using fetched word address
     * @attention Increments cycles count (x3). Increments PC (x2).
     * @param memory Memory struct instance
     * @return {Value, TargetAddress}
     */
    inline ValueAddressRequest GetAbsAddressValue(Memory &memory) {
        const WORD TargetAddress = FetchWord(memory);
        const BYTE Value = ReadByte(memory, TargetAddress);
        return {Value, TargetAddress};
    }

    /**
     * @description Get generic Absolute address.
     * @note Call FetchWord
     * @note Add offset to fetched word to get generic Absolute address
     * @attention Increments cycles count (x2). Increments PC (x2).
     * @attention Extra cycles count increment if page cross detected.
     * @addressing Absolute,X; Absolute,Y.
     * @param memory Memory struct instance
     * @param offsetAddress Offset memory address value
     * @return generic Absolute address
     */
    inline WORD GetAbsAddress(Memory &memory, BYTE offsetAddress) {
        const WORD AbsAddress = FetchWord(memory);
        const WORD TargetAddress = AbsAddress + offsetAddress;
        if (IsPageCrossed(TargetAddress, AbsAddress))
            cycles++;
        return TargetAddress;
    }

    /**
     * @description Get generic Absolute value.
     * @note Call FetchWord
     * @note Add offset to fetched word to get generic Absolute address
     * @note Call ReadByte using generic Absolute address
     * @attention Increments cycles count (x3). Increments PC (x2).
     * @attention Extra cycles count increment if page cross detected.
     * @addressing Absolute,X; Absolute,Y.
     * @param memory Memory struct instance
     * @param offsetAddress Offset memory address value
     * @return generic Absolute address value
     */
    inline BYTE GetAbsValue(Memory &memory, BYTE offsetAddress) {
        const WORD TargetAddress = GetAbsAddress(memory, offsetAddress);
        return ReadByte(memory, TargetAddress);
    }

    /**
     * @description Get generic Absolute address and value.
     * @note Call FetchWord
     * @note Add offset to fetched word to get generic Absolute address
     * @note Call ReadByte using generic Absolute address
     * @attention Increments cycles count (x3). Increments PC (x2).
     * @attention Extra cycles count increment if page cross detected.
     * @addressing Absolute,X; Absolute,Y.
     * @param memory Memory struct instance
     * @param offsetAddress Offset memory address value
     * @return {Value, TargetAddress}
     */
    inline ValueAddressRequest GetAbsAddressValue(Memory &memory, BYTE offsetAddress) {
        const WORD TargetAddress = GetAbsAddress(memory, offsetAddress);
        const BYTE Value = ReadByte(memory, TargetAddress);
        return {Value, TargetAddress};
    }

    /**
     * @description Get (Indirect,X) address
     * @note Call FetchByte
     * @note Add X to fetched value
     * @note Call ReadWord using this value to get (Indirect,X) address
     * @attention Increments cycles count (x4). Increments PC.
     * @addressing (Indirect,X).
     * @param memory Memory struct instance
     * @return (Indirect,X) address
     */
    inline WORD GetIndXAddress(Memory &memory) {
        BYTE TargetAddress = FetchByte(memory) + X;
        cycles++;
        return ReadWord(memory, TargetAddress);
    }

    /**
     * @description Get value using (Indirect,X) address
     * @note Call FetchByte
     * @note Add X to fetched value
     * @note Call ReadWord using this value to get (Indirect,X) address
     * @note Call ReadByte using (Indirect,X) address to get result value
     * @attention Increments cycles count (x5). Increments PC.
     * @addressing (Indirect,X)
     * @param memory Memory struct instance
     * @return (Indirect,X) address value
     */
    inline BYTE GetIndXAddressValue(Memory &memory) {
        const WORD TargetAddress = GetIndXAddress(memory);
        return ReadByte(memory, TargetAddress);
    }

    /**
     * @description Get (Indirect),Y address
     * @note Call FetchByte
     * @note Call ReadWord using fetched byte to get Effective Address
     * @note Add Y to Effective Address to get (Indirect),Y address
     * @attention Increments cycles count (x3). Increments PC.
     * @attention Extra cycles count increment if page cross detected.
     * @addressing (Indirect),Y
     * @param memory Memory struct instance
     * @return (Indirect),Y address
     */
    inline WORD GetIndYAddress(Memory &memory) {
        BYTE ZeroPageAddress = FetchByte(memory);
        const WORD EffectiveAddress = ReadWord(memory, ZeroPageAddress);
        const WORD TargetAddress = EffectiveAddress + Y;
        if (IsPageCrossed(TargetAddress, EffectiveAddress))
            cycles++;
        return TargetAddress;
    }

    /**
     * @description Get (Indirect),Y address value
     * @note Call FetchByte
     * @note Call ReadWord using fetched byte to get Effective Address
     * @note Add Y to Effective Address to get (Indirect),Y address
     * @note ReadByte using (Indirect),Y address to get result value
     * @attention Increments cycles count (x4). Increments PC.
     * @attention Extra cycles count increment if page cross detected
     * @addressing (Indirect),Y
     * @param memory Memory struct instance
     * @return (Indirect),Y address value
     */
    inline BYTE GetIndYAddressValue(Memory &memory) {
        const WORD TargetAddress = GetIndYAddress(memory);
        return ReadByte(memory, TargetAddress);
    }

    /** Convert StackPointer (BYTE) to Address (WORD) */
    [[nodiscard]] inline WORD StackPointerToAddress() const noexcept {
        return 0x100 + SP;
    }
};
