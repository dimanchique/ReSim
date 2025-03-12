#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @brief Compare Implementation
 * @details This instruction compares the contents of the targetRegister with memoryValue
 * and sets the zero and carry flags as appropriate.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param targetRegister Register to compare with.
 * @param addressing MOS6502 Addressing mode.
 */
FORCE_INLINE void PerformCM(MOS6502 &cpu, const BYTE &targetRegister, const MOS6502_AddressingMode addressing) {
    const BYTE memoryValue = cpu.GetAddressingModeValue(addressing);

    const BYTE compareResult = targetRegister - memoryValue;
    cpu.Status.UpdateStatusByValue(compareResult, MOS6502_Status_Z | MOS6502_Status_N);
    cpu.Status.C = targetRegister >= memoryValue;
}

/**
 * @brief Compare Accumulator (generic)
 * @details This instruction compares the contents of the Accumulator with memoryValue
 * and sets the zero and carry flags as appropriate.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param addressing MOS6502 Addressing mode.
 */
FORCE_INLINE void PerformCMP(MOS6502 &cpu, const MOS6502_AddressingMode addressing){
    PerformCM(cpu, cpu.A, addressing);
}

/**
 * @brief Compare X Register (generic)
 * @details This instruction compares the contents of the Accumulator with memoryValue
 * and sets the zero and carry flags as appropriate.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param addressing MOS6502 Addressing mode.
 */
FORCE_INLINE void PerformCPX(MOS6502 &cpu, const MOS6502_AddressingMode addressing){
    PerformCM(cpu, cpu.X, addressing);
}

/**
 * @brief Compare Y Register (generic)
 * @details This instruction compares the contents of the Accumulator with memoryValue
 * and sets the zero and carry flags as appropriate.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param addressing MOS6502 Addressing mode.
 */
FORCE_INLINE void PerformCPY(MOS6502 &cpu, const MOS6502_AddressingMode addressing){
    PerformCM(cpu, cpu.Y, addressing);
}
