#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @brief Store (generic)
 * @details Stores the contents of the targetRegister into memory.
 * @short M = (A/X/Y)
 * @param cpu MOS6502 struct instance.
 * @param targetRegister Register to store from.
 * @param addressing MOS6502 Addressing mode.
 * @param shouldCheckPageCross Whether this operation should check page crossing while target address is calculating.
 */
FORCE_INLINE void PerformST(MOS6502 &cpu, const BYTE &targetRegister, const MOS6502_AddressingMode addressing, bool shouldCheckPageCross) {
    const WORD targetAddress = cpu.GetAddressingModeAddress(addressing, shouldCheckPageCross);
    cpu.WriteByte(targetRegister, targetAddress);
}

/**
 * @brief Store Accumulator
 * @details Stores the contents of the targetRegister into memory.
 * @short M = A
 * @param cpu MOS6502 struct instance.
 * @param addressing MOS6502 Addressing mode.
 * @param shouldCheckPageCross Whether this operation should check page crossing while target address is calculating.
 */
FORCE_INLINE void PerformSTA(MOS6502 &cpu, const MOS6502_AddressingMode addressing, bool shouldCheckPageCross = true){
    PerformST(cpu, cpu.A, addressing, shouldCheckPageCross);
}


/**
 * @brief Store X Register
 * @details Stores the contents of the targetRegister into memory.
 * @short M = X
 * @param cpu MOS6502 struct instance.
 * @param addressing MOS6502 Addressing mode.
 * @param shouldCheckPageCross Whether this operation should check page crossing while target address is calculating.
 */
FORCE_INLINE void PerformSTX(MOS6502 &cpu, const MOS6502_AddressingMode addressing, bool shouldCheckPageCross = true){
    PerformST(cpu, cpu.X, addressing, shouldCheckPageCross);
}


/**
 * @brief Store Y Register
 * @details Stores the contents of the targetRegister into memory.
 * @short M = Y
 * @param cpu MOS6502 struct instance.
 * @param addressing MOS6502 Addressing mode.
 * @param shouldCheckPageCross Whether this operation should check page crossing while target address is calculating.
 */
FORCE_INLINE void PerformSTY(MOS6502 &cpu, const MOS6502_AddressingMode addressing, bool shouldCheckPageCross = true){
    PerformST(cpu, cpu.Y, addressing, shouldCheckPageCross);
}
