#pragma once
#include "MOS6502.h"

/**
 * @brief Subtract with Carry Implementation
 * @details This instruction subtracts the contents of a memory location to the accumulator
 * together with the not of the carry bit.
 * If overflow occurs the carry bit is clear, this enables multiple byte subtraction to be performed.
 * @short A,Z,C,N = A-M-(1-C)
 * @param cpu MOS6502 struct instance.
 * @param addressing MOS6502 Addressing mode.
 */
FORCE_INLINE void PerformSBC(MOS6502 &cpu, const MOS6502_AddressingMode addressing) {
    const BYTE value = cpu.GetAddressingModeValue(addressing);
    const BYTE originalValue = cpu.A;
    const WORD subRes = cpu.A - value - (1 - cpu.Status.C);
    cpu.A = subRes;
    cpu.Status.UpdateStatusByValue(cpu.A, MOS6502_Status_Z | MOS6502_Status_N);
    cpu.Status.C = subRes <= 0xFF;
    cpu.Status.V = ((originalValue ^ value) & (originalValue ^ cpu.A) & MOS6502_Status_N) != 0;
}

/**
 * @brief Subtract with Carry
 * @addressing Immediate
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_SBC_IM(MOS6502 &cpu) {
    PerformSBC(cpu, MOS6502_AddressingMode::Immediate);
}

/**
 * @brief Subtract with Carry
 * @addressing Zero Page
 * @param memory Memory struct instance
 * @param cpu MOS6502 struct instance
 */
void MOS6502_SBC_ZP(MOS6502 &cpu) {
    PerformSBC(cpu, MOS6502_AddressingMode::ZeroPage);
}

/**
 * @brief Subtract with Carry
 * @addressing Zero Page,X
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_SBC_ZPX(MOS6502 &cpu) {
    PerformSBC(cpu, MOS6502_AddressingMode::ZeroPage_X);
}

/**
 * @brief Subtract with Carry
 * @addressing Absolute
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_SBC_ABS(MOS6502 &cpu) {
    PerformSBC(cpu, MOS6502_AddressingMode::Absolute);
}

/**
 * @brief Subtract with Carry
 * @addressing Absolute,X
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_SBC_ABSX(MOS6502 &cpu) {
    PerformSBC(cpu, MOS6502_AddressingMode::Absolute_X);
}

/**
 * @brief Subtract with Carry
 * @addressing Absolute,Y
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_SBC_ABSY(MOS6502 &cpu) {
    PerformSBC(cpu, MOS6502_AddressingMode::Absolute_Y);
}

/**
 * @brief Subtract with Carry
 * @addressing (Indirect,X)
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_SBC_INDX(MOS6502 &cpu) {
    PerformSBC(cpu, MOS6502_AddressingMode::Indirect_X);
}

/**
 * @brief Subtract with Carry
 * @addressing (Indirect),Y
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_SBC_INDY(MOS6502 &cpu) {
    PerformSBC(cpu, MOS6502_AddressingMode::Indirect_Y);
}
