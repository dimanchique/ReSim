#pragma once

#include "compute.h"
#include "core/macro.h"
#include "function_library/data_manipulation.h"
#include "I8080_Status.h"

#define I8080_STOP_OPCODE I8080_OpCodes_Main::HLT /**< HALT instruction opcode used to stop execution of finite programs */

/**
 * @class I8080
 * @brief I8080 CPU implementation
 * @details I8080 (Launch: 1974) is an 8-bit microprocessor with 78 supported instructions.
 * Registers:
 * - Program Counter register (PC)
 * - Stack Pointer register (SP)
 * - Accumulator register (A)
 * - BC paired register
 * - DE paired register
 * - HL paired register
 * - Status register
 * Max CPU clock rate 2-4 MHz. Data width: 8 bits. Address width: 16 bits
 */
class I8080 final: public Compute{
public:

    WORD PC;                                /**< Program Counter */
    WORD SP;                                /**< Stack Pointer */
    BYTE A;                                 /**< Accumulator */
    I8080_Status Status;                    /**< Status Register */
    DECLARE_PAIRED_REG(BYTE, WORD, B, C);   /**< Paired BC Register */
    DECLARE_PAIRED_REG(BYTE, WORD, D, E);   /**< Paired DE Register */
    DECLARE_PAIRED_REG(BYTE, WORD, H, L);   /**< Paired HL Register */

    void SetDataBusInstance(Bus* new_bus) { dataBus = new_bus; }
    Bus* GetDataBus() { return dataBus; }

    void Reset() noexcept override;

    U32 Run() override;

    bool Step() override;

    /**
     * @brief Fetch byte from memory address PC points to.
     * @note Increments PC. Increments cycles count by 3.
     * @return Fetched byte.
     */
    FORCE_INLINE BYTE FetchByte() {
        return ReadByte(PC++);
    }

    /**
     * @brief Fetch word from memory address PC points to.
     * @note Increments PC by 2. Increments cycles count by 6.
     * @attention I8080 is little-endian system.
     * 16-bit word value has memory layout [LOW][HIGH].
     * Additional 8-bit shift is needed.
     * @return Fetched word.
     */
    FORCE_INLINE WORD FetchWord() {
        const BYTE Lo = FetchByte();
        const BYTE Hi = FetchByte();
        return Hi | (Lo << 8);
    }

    /**
     * @brief Read byte from memory.
     * @note Increments cycles count by 3.
     * @param address Address to read from.
     * @return Read byte.
     */
    FORCE_INLINE BYTE ReadByte(const WORD address) {
        const BYTE Data = bus->Read(address);
        cycles += 3;
        return Data;
    }

    /**
     * @brief Read word from memory.
     * @note Increments cycles count by 6.
     * @attention I8080 is little-endian system.
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
     * @brief Write a byte to memory.
     * @note Increments cycles count by 3.
     * @param value Value to write.
     * @param address Address to write to.
     */
    FORCE_INLINE void WriteByte(const BYTE value, const WORD address) {
        bus->Write(address, value);
        cycles += 3;
    }

    /**
     * @brief Write a word to memory.
     * @note Increments cycles count by 6.
     * @attention I8080 is little-endian system.
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
     * @brief Push two bytes of data to stack.
     * @note Increments cycles count by 7. Decrements the Stack Pointer by 2.
     * @param lsb Low byte to push.
     * @param msb High byte to push.
     */
    FORCE_INLINE void PushDataToStack(const BYTE &lsb, const BYTE &msb) {
        WriteByte(lsb, --SP);
        WriteByte(msb, --SP);
        ++cycles;
    }

    /**
     * @brief Push Program Counter (PC) register value to stack.
     * @note Increments cycles count by 7. Decrements the Stack Pointer by 2.
     */
    FORCE_INLINE void PushProgramCounterToStack() {
        PushDataToStack((PC >> 8), PC & 0xFF);
    }

    /**
     * @brief Pop Program Counter (PC) register value from stack.
     * @details Sets new value of PC register.
     * @note Increments cycles count by 3. Increments the Stack Pointer by 2.
     */
    FORCE_INLINE void PopProgramCounterFromStack() {
        PC = ReadWord(SP);
        SP += 2;
    }

    /**
     * @brief Pop two bytes of data from stack.
     * @note Increments cycles count by 6. Increments the Stack Pointer by 2.
     * @param lsb Low byte ref to write-back to.
     * @param msb High byte ref to write-back to.
     */
    FORCE_INLINE void PopDataFromStack(BYTE* lsb, BYTE* msb) {
        *msb = ReadByte(SP++);
        *lsb = ReadByte(SP++);
    }

protected:
    Bus* dataBus;
};
