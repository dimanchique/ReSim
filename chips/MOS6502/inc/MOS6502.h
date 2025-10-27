#pragma once

#include "compute.h"
#include "core/compilers_macro.h"
#include "MOS6502_Status.h"
#include "MOS6502_AddressingMode.h"
#include "core/macro.h"

#define MOS6502_STOP_OPCODE 0x02 /**< One of unused MOS6502 opcodes used to stop execution of finite programs */
#define PAGE_SIZE 0xFF /**< MOS6502 default page size */
#define IsPageCrossed(src, dst) (((src) ^ (dst)) >= PAGE_SIZE) /**< Memory page is crossed when it bounds PAGE_SIZE */

/**
 * @class MOS6502
 * @brief MOS6502 CPU implementation
 * @details MOS6502 (Launch: 1975) is an 8-bit microprocessor with 55 supported instructions and 8 addressing modes.
 * Registers:
 * - Program Counter register (PC)
 * - Stack Pointer register (SP)
 * - Accumulator register (A)
 * - X index register (X)
 * - Y index register (Y)
 * - Status register
 * Max CPU clock rate 1-3 MHz. Data width: 8 bits. Address width: 16 bits
 */
class MOS6502 final : public Compute {
public:

    WORD PC;                /**< Program Counter */
    BYTE SP;                /**< Stack Pointer (+ 0x100 offset) */
    BYTE A;                 /**< Accumulator */
    BYTE X;                 /**< X Register */
    BYTE Y;                 /**< Y Register */
    MOS6502_Status Status;  /**< Status Register */

    void Reset() noexcept override;

    U32 Run() override;

    bool Step() override;

    /**
     * @brief Fetch byte from a bus using address PC points to.
     * @note Increments PC and cycles count.
     * @return Fetched byte.
     */
    FORCE_INLINE BYTE FetchByte() {
        return ReadByte(PC++);
    }

    /**
     * @brief Fetch word from a bus using address PC points to.
     * @note Increments PC by 2. Increments cycles count by 2.
     * @attention MOS6502 is little-endian system.
     * 16-bit word value has memory layout [LOW][HIGH].
     * Additional 8-bit shift is needed.
     * @return Fetched word.
     */
    FORCE_INLINE WORD FetchWord() {
        const BYTE Lo = FetchByte();
        const BYTE Hi = FetchByte();
        return Lo | (Hi << 8);
    }

    /**
     * @brief Read byte from a bus.
     * @note Increments cycles count.
     * @param address Address to read from.
     * @return Read byte.
     */
    FORCE_INLINE BYTE ReadByte(const WORD address) {
        const BYTE Data = bus->Read(address);
        ++cycles;
        return Data;
    }

    /**
     * @brief Read word from a bus.
     * @note Increments cycles count by 2.
     * @attention MOS6502 is little-endian system.
     * 16-bit word value has memory layout [LOW][HIGH].
     * Additional 8-bit shift is needed.
     * @param address Address to read from.
     * @return Fetched word.
     */
    FORCE_INLINE WORD ReadWord(const WORD address) {
        const BYTE Lo = ReadByte(address);
        const BYTE Hi = ReadByte(address + 1);
        return Lo | (Hi << 8);
    }

    /**
     * @brief Write a byte to a bus.
     * @note Increments cycles count.
     * @param value Value to write.
     * @param address Address to write to.
     */
    FORCE_INLINE void WriteByte(const BYTE value, const WORD address) {
        bus->Write(address, value);
        ++cycles;
    }

    /**
     * @brief Write a word to a bus.
     * @note Increments cycles count by 2.
     * @attention MOS6502 is little-endian system.
     * 16-bit word value has memory layout [LOW][HIGH].
     * Additional 8-bit shift is needed.
     * @param value Value to write.
     * @param address Address to write to.
     */
    FORCE_INLINE void WriteWord(const WORD value, const WORD address) {
        WriteByte(value & 0xFF, address);
        WriteByte((value >> 8), address + 1);
    }

    /**
     * @brief Push Program Counter (PC) register value to stack.
     * @see PushWordToStack
     */
    FORCE_INLINE void PushProgramCounterToStack() {
        PushWordToStack(PC - 1);
    }

    /**
     * @brief Pop an address from stack.
     * @note Increments cycles count by 2. Increments the Stack Pointer by 2.
     * @see PopWordFromStack
     * @return Popped address.
     */
    FORCE_INLINE WORD PopAddressFromStack() {
        return PopWordFromStack() + 1;
    }

    /**
     * @brief Push Status register value to stack.
     * @note Increments cycles count by 2. Decrements the Stack Pointer.
     * @see WriteByte
     */
    FORCE_INLINE void PushStatusToStack() {
        WriteByte(Status.Value, StackPointerToAddress());
        SP--;
        ++cycles;
    }

    /**
     * @brief Pop Status register value from the stack.
     * @note Increments cycles count by 3. Increments the Stack Pointer.
     * @see ReadByte
     */
    FORCE_INLINE void PopStatusFromStack() {
        SP++;
        ++cycles;
        Status.Value = ReadByte(StackPointerToAddress());
        ++cycles;
    }

    /**
     * @brief Push a byte to stack.
     * @note Increments cycles count by 2. Decrements the Stack Pointer.
     * @see WriteByte
     * @param value Value to push to stack.
     */
    FORCE_INLINE void PushByteToStack(const BYTE value) {
        WriteByte(value, StackPointerToAddress());
        SP--;
        ++cycles;
    }

    /**
     * @brief Pop a byte from stack.
     * @note Increments cycles count by 3. Increments the Stack Pointer.
     * @see ReadByte
     * @return Popped value.
     */
    FORCE_INLINE BYTE PopByteFromStack() {
        SP++;
        ++cycles;
        const BYTE value = ReadByte(StackPointerToAddress());
        ++cycles;
        return value;
    }

    /**
     * @brief Push a word to stack.
     * @note Increments cycles count by 2. Decrements the Stack Pointer by 2.
     * @see WriteWord
     * @param value Value to push to stack.
     */
    FORCE_INLINE void PushWordToStack(const WORD value) {
        WriteWord(value, StackPointerToAddress() - 1);
        SP -= 2;
    }

    /**
     * @brief Pop a word from stack.
     * @note Increments cycles count by 4. Increments the Stack Pointer by 2.
     * @see ReadWord
     * @return Popped value.
     */
    FORCE_INLINE WORD PopWordFromStack() {
        const WORD value = ReadWord(StackPointerToAddress() + 1);
        cycles += 2;
        SP += 2;
        return value;
    }

    /**
     * @brief Convert Stack Pointer register to address.
     * @return Converted address.
     */
    [[nodiscard]] FORCE_INLINE WORD StackPointerToAddress() const noexcept {
        return 0x100 + SP;
    }

/** @defgroup MOS6502-Addressing MOS6502 Addressing
 *  MOS6502 Addressing Modes
 *  @{
 */

    /**
     * @brief Get address based on given addressing mode
     * @note Offset value is calculating automatically if addressing mode is indexed.
     * @param addressing MOS6502 Addressing mode.
     * @param shouldCheckPageCross Whether this operation should check page crossing while target address is calculating.
     * @return Target address.
     */
    FORCE_INLINE WORD GetAddressingModeAddress(MOS6502_AddressingMode addressing, bool shouldCheckPageCross = true) {
        BYTE offsetValue = 0;
        switch (addressing) {
            case MOS6502_AddressingMode::ZeroPage_X:
            case MOS6502_AddressingMode::Absolute_X:
            case MOS6502_AddressingMode::Indirect_X:
                offsetValue = X;
                break;

            case MOS6502_AddressingMode::ZeroPage_Y:
            case MOS6502_AddressingMode::Absolute_Y:
            case MOS6502_AddressingMode::Indirect_Y:
                offsetValue = Y;

            default:
                break;
        }

        switch (addressing) {
            case MOS6502_AddressingMode::Immediate:
                return PC++;
            case MOS6502_AddressingMode::ZeroPage:
                return FetchByte();
            case MOS6502_AddressingMode::ZeroPage_X:
            case MOS6502_AddressingMode::ZeroPage_Y:
                return GetZeroPageIndexedAddress(offsetValue);
            case MOS6502_AddressingMode::Absolute:
                return FetchWord();
            case MOS6502_AddressingMode::Absolute_X:
            case MOS6502_AddressingMode::Absolute_Y:
                return GetAbsIndexedAddress(offsetValue, shouldCheckPageCross);
            case MOS6502_AddressingMode::Indirect_X:
                return GetIndXAddress();
            case MOS6502_AddressingMode::Indirect_Y:
                return GetIndYAddress(shouldCheckPageCross);
        }
        RESIM_THROW;
    }

    /**
     * @brief Get value based on given addressing mode
     * @note Offset value is calculating automatically if addressing mode is indexed.
     * @param addressing MOS6502 Addressing mode.
     * @param shouldCheckPageCross Whether this operation should check page crossing while target address is calculating.
     * @return Memory value.
     */
    FORCE_INLINE BYTE GetAddressingModeValue(MOS6502_AddressingMode addressing, bool shouldCheckPageCross = true) {
        const WORD address = GetAddressingModeAddress(addressing, shouldCheckPageCross);
        return ReadByte(address);
    }

private:

    /**
     * @brief Get Indexed ZeroPage addressing mode address (Generic).
     * @details Fetch byte. Add offset to fetched byte to get effective address.
     * @attention Increments cycles count by 2. Increments PC.
     * @addressing Zero Page,X
     * Zero Page,Y
     * @see FetchByte
     * @param offsetValue Address offset value.
     * @return Zero Page Indexed address.
     */
    FORCE_INLINE WORD GetZeroPageIndexedAddress(const BYTE offsetValue) {
        const BYTE baseAddress = FetchByte();
        ++cycles;
        return (BYTE) (baseAddress + offsetValue);
    }

    /**
     * @brief Get Indexed Absolute addressing mode address (Generic).
     * @note Fetch word. Add offset to fetched word to get effective address.
     * @attention Increments cycles count by 2. Increments PC by 2.
     * Extra cycles count increment if a page cross is detected.
     * Extra cycles is not applied for ASL/DEC/INC/LSR/ROR/ROL/STA.
     * @addressing Absolute,X
     * Absolute,Y
     * @see FetchWord
     * @param offsetValue Address offset value.
     * @return Absolute Indexed address.
     */
    FORCE_INLINE WORD GetAbsIndexedAddress(const BYTE offsetValue, bool shouldCheckPageCross = true) {
        const WORD baseAddress = FetchWord();
        const WORD effectiveAddress = baseAddress + offsetValue;

        // add extra cycle if NO page-cross check
        if (!shouldCheckPageCross || IsPageCrossed(effectiveAddress, baseAddress))
            ++cycles;
        return effectiveAddress;
    }

    /**
     * @brief Get (Indirect,X) addressing mode address.
     * @details Fetch byte. Add X to the fetched value.
     * Read word using this value to get (Indirect,X) address.
     * @attention Increments cycles count by 4. Increments PC.
     * @addressing (Indirect,X)
     * @see FetchByte
     * @see ReadWord
     * @return (Indirect,X) address.
     */
    FORCE_INLINE WORD GetIndXAddress() {
        const BYTE baseAddress = FetchByte() + X;
        ++cycles;
        return ReadWord(baseAddress);
    }

    /**
     * @brief Get (Indirect),Y addressing mode address.
     * @details Fetch byte. Read word using fetched byte to get effective address.
     * Add Y to the effective address to get (Indirect),Y address.
     * @attention Increments cycles count by 3. Increments PC.
     * Extra cycles count increment if a page cross is detected.
     * Extra cycles is not applied for EOR/STA instructions
     * @addressing (Indirect),Y
     * @see FetchByte
     * @see ReadWord
     * @return (Indirect),Y address.
     */
    FORCE_INLINE WORD GetIndYAddress(bool shouldCheckPageCross = true) {
        const BYTE baseAddressPtr = FetchByte();
        const WORD baseAddress = ReadWord(baseAddressPtr);
        const WORD effectiveAddress = baseAddress + Y;
        if (shouldCheckPageCross && IsPageCrossed(effectiveAddress, baseAddress))
            ++cycles;
        return effectiveAddress;
    }

/** @} */ // end of addressing
};
