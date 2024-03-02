#pragma once

#include "Macro.h"
#include "MOS6502_Status.h"
#include "CPU_Base.h"

#define STOP_OPCODE 0x02 // one of unused OpCodes so it's pretty much OK to use it a stop flag
#define PAGE_SIZE 0xFF
#define IsPageCrossed(src, dst) ((src ^ dst) >= PAGE_SIZE)

class MOS6502 final: public CPU_Base{
public:

    WORD PC;                // Program Counter
    BYTE SP;                // Stack Pointer (+ 0x100 offset)
    BYTE A;                 // Accumulator
    BYTE X;                 // X Register
    BYTE Y;                 // Y Register
    MOS6502_Status Status;  // Status Register

    void Reset(Memory &memory, WORD resetVector) noexcept override;

    U32 Run(Memory &memory) override;

    /**
     * @brief Fetch byte from memory.
     * @attention Increments PC and cycles count.
     * @param memory Memory struct instance.
     * @return Fetched byte.
     */
    FORCE_INLINE BYTE FetchByte(const Memory &memory) {
        const BYTE Data = memory[PC++];
        cycles++;
        return Data;
    }

    /**
     * @brief Fetch word from memory.
     * @attention Increments PC by 2. Increments cycles count by 2.
     * @param memory Memory struct instance.
     * @return Fetched word.
     */
    FORCE_INLINE WORD FetchWord(const Memory &memory) {
        const BYTE Lo = FetchByte(memory);
        const BYTE Hi = FetchByte(memory);
        return Lo | (Hi << 8);
    }

    /**
     * @brief Read byte from memory.
     * @attention Increments cycles count.
     * @param memory Memory struct instance.
     * @param address Address to read from.
     * @return Read byte.
     */
    FORCE_INLINE BYTE ReadByte(const Memory &memory, const WORD address) {
        const BYTE Data = memory[address];
        cycles++;
        return Data;
    }

    /**
     * @brief Read word from memory.
     * @attention Increments PC by 2. Increments cycles count by 2.
     * @param memory Memory struct instance.
     * @param address Address to read from.
     * @return Fetched word.
     */
    FORCE_INLINE WORD ReadWord(const Memory &memory, const WORD address) {
        const BYTE Lo = ReadByte(memory, address);
        const BYTE Hi = ReadByte(memory, address + 1);
        return Lo | (Hi << 8);
    }

    /**
     * @brief Writes a byte from memory.
     * @attention Increments cycles count.
     * @param memory Memory struct instance.
     * @param value Value to write.
     * @param address Address to read from.
     * @return Read byte.
     */
    FORCE_INLINE void WriteByte(Memory &memory, const BYTE value, const WORD address) {
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
    FORCE_INLINE void WriteWord(Memory &memory, const WORD value, const WORD address) {
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
    FORCE_INLINE void PushProgramCounterToStack(Memory &memory) {
        PushWordToStack(memory, PC - 1);
    }

    /**
     * @brief Pops an address from the stack.
     * @attention Increments cycles count by 2. Increments the Stack Pointer by 2.
     * @param memory Memory struct instance.
     * @return Popped address.
     */
    FORCE_INLINE WORD PopAddressFromStack(const Memory &memory) {
        return PopWordFromStack(memory) + 1;
    }

    /**
     * @brief Pushes the Status register value to the stack.
     * @attention Increments cycles count by 2. Decrements the Stack Pointer.
     * @param memory Memory struct instance.
     */
    FORCE_INLINE void PushStatusToStack(Memory &memory) {
        WriteByte(memory, Status, StackPointerToAddress());
        SP--;
        cycles++;
    }

    /**
     * @brief Pops the Status register value from the stack.
     * @attention Increments cycles count by 3. Increments the Stack Pointer.
     * @param memory Memory struct instance.
     */
    FORCE_INLINE void PopStatusFromStack(const Memory &memory) {
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
    FORCE_INLINE void PushByteToStack(Memory &memory, const BYTE value) {
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
    FORCE_INLINE BYTE PopByteFromStack(const Memory &memory) {
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
    FORCE_INLINE void PushWordToStack(Memory &memory, const WORD value) {
        WriteWord(memory, value, StackPointerToAddress() - 1);
        SP -= 2;
    }

    /**
     * @brief Pops a word from the stack.
     * @attention Increments cycles count by 4. Increments the Stack Pointer by 2.
     * @param memory Memory struct instance.
     * @return Popped value.
     */
    FORCE_INLINE WORD PopWordFromStack(const Memory &memory) {
        const WORD value = ReadWord(memory, StackPointerToAddress() + 1);
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
    FORCE_INLINE BYTE GetZeroPageValue(const Memory &memory) {
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
    FORCE_INLINE WORD GetZeroPageAddress(const Memory& memory, const BYTE offsetAddress) {
        const BYTE TargetAddress = FetchByte(memory);
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
    FORCE_INLINE BYTE GetZeroPageValue(const Memory& memory, const BYTE offsetAddress) {
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
    FORCE_INLINE BYTE GetAbsValue(const Memory& memory) {
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
    FORCE_INLINE WORD GetAbsAddress(const Memory& memory, const BYTE offsetAddress) {
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
    FORCE_INLINE BYTE GetAbsValue(const Memory& memory, const BYTE offsetAddress) {
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
    FORCE_INLINE WORD GetIndXAddress(const Memory& memory) {
        const BYTE TargetAddress = FetchByte(memory) + X;
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
    FORCE_INLINE BYTE GetIndXAddressValue(const Memory& memory) {
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
    FORCE_INLINE WORD GetIndYAddress(const Memory& memory) {
        const BYTE ZeroPageAddress = FetchByte(memory);
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
    FORCE_INLINE BYTE GetIndYAddressValue(const Memory& memory) {
        const WORD TargetAddress = GetIndYAddress(memory);
        return ReadByte(memory, TargetAddress);
    }

    /**
     * @brief Convert StackPointer (BYTE) to Address (WORD).
     * @return Converted WORD address.
     */
    [[nodiscard]] inline WORD StackPointerToAddress() const noexcept {
        return 0x100 + SP;
    }
};
