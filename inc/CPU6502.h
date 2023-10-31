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
     * @brief Resets CPU registers and Stack Pointer to their default values.
     * The Program Counter value after reset depends on the ResetVector value.
     * @param memory Memory struct instance.
     * @param resetVector Program Counter (PC) value after reset. Default is 0xFFFC.
     */
    void Reset(Memory &memory, WORD resetVector = 0xFFFC) noexcept;

    /**
     * @brief Main 6502 execution function. Stops execution if 0xFF or FAKE_NOP instruction is encountered.
     * @param memory Memory struct instance.
     * @return Cycles count.
     */
    U32 Run(Memory &memory);

    /**
     * @brief Static function to read a binary file.
     * @param filename Path to the binary file.
     * @param [out] fileSize Number of bytes read.
     * @return Char pointer to data (or nullptr if any error).
     */
    static char* ReadBinary(const char* filename, size_t& fileSize);

    /**
     * @brief Load data into memory from a binary file and a specified starting address.
     * @param filename Path to the binary file.
     * @param memory Memory struct instance.
     * @param startingAddress Starting address to write the binary.
     * @return True if the load was successful; otherwise, false.
     */
    bool LoadROM(const char *filename, Memory& memory, WORD startingAddress);

    /**
     * @brief Fetches a byte from memory.
     * @attention Increments PC and cycles count.
     * @param memory Memory struct instance.
     * @return Fetched byte.
     */
    inline BYTE FetchByte(const Memory &memory) {
        BYTE Data = memory[PC++];
        cycles++;
        return Data;
    }

    /**
     * @brief Fetch word from memory.
     * @attention Increments PC by 2. Increments cycles count by 2.
     * @param memory Memory struct instance.
     * @return Fetched word.
     */
    inline WORD FetchWord(const Memory &memory) {
        BYTE Lo = FetchByte(memory);
        BYTE Hi = FetchByte(memory);
        return Lo | (Hi << 8);
    }

    /**
     * @brief Read byte from memory.
     * @attention Increments cycles count.
     * @param memory Memory struct instance.
     * @param address Address to read from.
     * @return Read byte.
     */
    inline BYTE ReadByte(const Memory &memory, WORD address) {
        BYTE Data = memory[address];
        cycles++;
        return Data;
    }

    /**
     * @brief Fetches a word from memory.
     * @attention Increments PC by 2. Increments cycles count by 2.
     * @param memory Memory struct instance.
     * @return Fetched word.
     */
    inline WORD ReadWord(const Memory &memory, WORD address) {
        BYTE Lo = ReadByte(memory, address);
        BYTE Hi = ReadByte(memory, address + 1);
        return Lo | (Hi << 8);
    }

    /**
     * @brief Reads a byte from memory.
     * @attention Increments cycles count.
     * @param memory Memory struct instance.
     * @param address Address to read from.
     * @return Read byte.
     */
    inline void WriteByte(Memory &memory, BYTE value, WORD address) {
        memory[address] = value;
        cycles++;
    }

    /**
     * @brief Write word to memory.
     * @attention Increments cycles count by 2.
     * @param memory Memory struct instance.
     * @param value Value to write.
     * @param address Address to write to.
     */
    inline void WriteWord(Memory &memory, WORD value, WORD address) {
        memory[address] = value & 0xFF;
        cycles++;
        memory[address + 1] = (value >> 8);
        cycles++;
    }

    /**
     * @brief Pushes the Program Counter (PC) register value to the stack.
     * @attention Increments cycles count by 2. Decrements the Stack Pointer by 2.
     * @param memory Memory struct instance.
     */
    inline void PushProgramCounterToStack(Memory &memory) {
        PushWordToStack(memory, PC - 1);
    }

    /**
     * @brief Pops an address from the stack.
     * @attention Increments cycles count by 2. Increments the Stack Pointer by 2.
     * @param memory Memory struct instance.
     * @return Popped address.
     */
    inline WORD PopAddressFromStack(Memory &memory) {
        return PopWordFromStack(memory) + 1;
    }

    /**
     * @brief Pushes the Status register value to the stack.
     * @attention Increments cycles count by 2. Decrements the Stack Pointer.
     * @param memory Memory struct instance.
     */
    inline void PushStatusToStack(Memory &memory) {
        WriteByte(memory, Status, StackPointerToAddress());
        SP--;
        cycles++;
    }


    /**
     * @brief Pops the Status register value from the stack.
     * @attention Increments cycles count by 3. Increments the Stack Pointer.
     * @param memory Memory struct instance.
     */
    inline void PopStatusFromStack(Memory &memory) {
        SP++;
        cycles++;
        Status = ReadByte(memory, StackPointerToAddress());
        cycles++;
    }

    /**
     * @brief Pushes a byte to the stack.
     * @attention Increments cycles count by 2. Decrements the Stack Pointer.
     * @param memory Memory struct instance.
     * @param value Value to push to the stack.
     */
    inline void PushByteToStack(Memory &memory, BYTE value) {
        WriteByte(memory, value, StackPointerToAddress());
        SP--;
        cycles++;
    }

    /**
     * @brief Pops a byte from the stack.
     * @attention Increments cycles count by 3. Increments the Stack Pointer.
     * @param memory Memory struct instance.
     * @return Popped value.
     */
    inline BYTE PopByteFromStack(Memory &memory) {
        SP++;
        cycles++;
        const BYTE value = ReadByte(memory, StackPointerToAddress());
        cycles++;
        return value;
    }

    /**
     * @brief Pushes a word to the stack.
     * @attention Increments cycles count by 2. Decrements the Stack Pointer by 2.
     * @param memory Memory struct instance.
     * @param value Value to push to the stack.
     */
    inline void PushWordToStack(Memory &memory, WORD value) {
        WriteWord(memory, value, StackPointerToAddress() - 1);
        SP -= 2;
    }

    /**
     * @brief Pops a word from the stack.
     * @attention Increments cycles count by 4. Increments the Stack Pointer by 2.
     * @param memory Memory struct instance.
     * @return Popped value.
     */
    inline WORD PopWordFromStack(Memory &memory) {
        WORD value = ReadWord(memory, StackPointerToAddress() + 1);
        cycles++;
        SP += 2;
        cycles++;
        return value;
    }

    /**
     * @brief Get value using ZeroPage addressing mode.
     * @note Call FetchByte.
     * @note Call ReadByte using the fetched byte as the ZeroPage address.
     * @attention Increments cycles count by 2. Increments PC.
     * @param memory Memory struct instance.
     * @return Zero Page address value.
     */
    inline BYTE GetZeroPageValue(Memory& memory) {
        const BYTE TargetAddress = FetchByte(memory);
        return ReadByte(memory, TargetAddress);
    }

    /**
     * @brief Get generic ZeroPage address.
     * @note Call FetchByte.
     * @note Add offset to the fetched byte to get a generic ZeroPage address.
     * @attention Increments cycles count. Increments PC.
     * @addressing Zero Page,X
     * @addressing Zero Page,Y
     * @param memory Memory struct instance.
     * @param offsetAddress Offset memory address value.
     * @return Generic ZeroPage address.
     */
    inline WORD GetZeroPageAddress(Memory& memory, BYTE offsetAddress) {
        BYTE TargetAddress = FetchByte(memory);
        cycles++;
        return TargetAddress + offsetAddress;
    }

    /**
     * @brief Get generic ZeroPage value.
     * @note Call FetchByte.
     * @note Add offset to the fetched byte to get a generic ZeroPage address.
     * @note Call ReadByte using generic ZeroPage address.
     * @attention Increments cycles count. Increments PC.
     * @addressing Zero Page,X
     * @addressing Zero Page,Y
     * @param memory Memory struct instance.
     * @param offsetAddress Offset memory address value.
     * @return Generic ZeroPage value.
     */
    inline BYTE GetZeroPageValue(Memory& memory, BYTE offsetAddress) {
        const BYTE TargetAddress = GetZeroPageAddress(memory, offsetAddress);
        return ReadByte(memory, TargetAddress);
    }

    /**
     * @brief Get value using Absolute addressing mode.
     * @note Call FetchWord.
     * @note Call ReadByte using the fetched word address.
     * @attention Increments cycles count by 3. Increments PC by 2.
     * @param memory Memory struct instance.
     * @return Absolute address value.
     */
    inline BYTE GetAbsValue(Memory& memory) {
        const WORD TargetAddress = FetchWord(memory);
        return ReadByte(memory, TargetAddress);
    }

    /**
     * @brief Get generic Absolute address.
     * @note Call FetchWord.
     * @note Add offset to the fetched word to get a generic Absolute address.
     * @attention Increments cycles count by 2. Increments PC by 2.
     * @attention Extra cycles count increment if a page cross is detected.
     * @addressing Absolute,X
     * @addressing Absolute,Y
     * @param memory Memory struct instance.
     * @param offsetAddress Offset memory address value.
     * @return Generic Absolute address.
     */
    inline WORD GetAbsAddress(Memory& memory, BYTE offsetAddress) {
        const WORD AbsAddress = FetchWord(memory);
        const WORD TargetAddress = AbsAddress + offsetAddress;
        if (IsPageCrossed(TargetAddress, AbsAddress))
            cycles++;
        return TargetAddress;
    }

    /**
     * @brief Get generic Absolute value.
     * @note Call FetchWord.
     * @note Add offset to the fetched word to get a generic Absolute address.
     * @note Call ReadByte using the generic Absolute address.
     * @attention Increments cycles count by 3. Increments PC by 2.
     * @attention Extra cycles count increment if a page cross is detected.
     * @addressing Absolute,X
     * @addressing Absolute,Y
     * @param memory Memory struct instance.
     * @param offsetAddress Offset memory address value.
     * @return Generic Absolute address value.
     */
    inline BYTE GetAbsValue(Memory& memory, BYTE offsetAddress) {
        const WORD TargetAddress = GetAbsAddress(memory, offsetAddress);
        return ReadByte(memory, TargetAddress);
    }

    /**
     * @brief Get (Indirect,X) address.
     * @note Call FetchByte.
     * @note Add X to the fetched value.
     * @note Call ReadWord using this value to get (Indirect,X) address.
     * @attention Increments cycles count by 4. Increments PC.
     * @addressing (Indirect,X)
     * @param memory Memory struct instance.
     * @return (Indirect,X) address.
     */
    inline WORD GetIndXAddress(Memory& memory) {
        BYTE TargetAddress = FetchByte(memory) + X;
        cycles++;
        return ReadWord(memory, TargetAddress);
    }


    /**
     * @brief Get value using (Indirect,X) address.
     * @note Call FetchByte.
     * @note Add X to the fetched value.
     * @note Call ReadWord using this value to get (Indirect,X) address.
     * @note Call ReadByte using (Indirect,X) address to get the result value.
     * @attention Increments cycles count by 5. Increments PC.
     * @addressing (Indirect,X)
     * @param memory Memory struct instance.
     * @return (Indirect,X) address value.
     */
    inline BYTE GetIndXAddressValue(Memory& memory) {
        const WORD TargetAddress = GetIndXAddress(memory);
        return ReadByte(memory, TargetAddress);
    }

    /**
     * @brief Get (Indirect),Y address.
     * @note Call FetchByte.
     * @note Call ReadWord using the fetched byte to get the Effective Address.
     * @note Add Y to the Effective Address to get (Indirect),Y address.
     * @attention Increments cycles count by 3. Increments PC.
     * @attention Extra cycles count increment if a page cross is detected.
     * @addressing (Indirect),Y
     * @param memory Memory struct instance.
     * @return (Indirect),Y address.
     */
    inline WORD GetIndYAddress(Memory& memory) {
        BYTE ZeroPageAddress = FetchByte(memory);
        const WORD EffectiveAddress = ReadWord(memory, ZeroPageAddress);
        const WORD TargetAddress = EffectiveAddress + Y;
        if (IsPageCrossed(TargetAddress, EffectiveAddress))
            cycles++;
        return TargetAddress;
    }

    /**
     * @brief Get (Indirect),Y address value.
     * @note Call FetchByte.
     * @note Call ReadWord using the fetched byte to get the Effective Address.
     * @note Add Y to the Effective Address to get (Indirect),Y address.
     * @note ReadByte using (Indirect),Y address to get the result value.
     * @attention Increments cycles count by 4. Increments PC.
     * @attention Extra cycles count increment if a page cross is detected.
     * @addressing (Indirect),Y
     * @param memory Memory struct instance.
     * @return (Indirect),Y address value.
     */
    inline BYTE GetIndYAddressValue(Memory& memory) {
        const WORD TargetAddress = GetIndYAddress(memory);
        return ReadByte(memory, TargetAddress);
    }

    /** Convert StackPointer (BYTE) to Address (WORD) */
    [[nodiscard]] inline WORD StackPointerToAddress() const noexcept {
        return 0x100 + SP;
    }
};
