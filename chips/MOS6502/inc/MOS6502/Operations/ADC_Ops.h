#pragma once
#include "MOS6502/MOS6502.h"

/**
 * @brief Add with Carry Implementation
 * @details This instruction adds the contents of a memory location to the accumulator together with the carry bit.
 * If overflow occurs the carry bit is set, this enables multiple byte addition to be performed.
 * @short A,Z,C,N = A+M+C
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @param addressing MOS6502 Addressing mode.
 */
FORCE_INLINE void PerformADC(MOS6502 &cpu, const MOS6502_AddressingMode addressing) {
    const BYTE value = cpu.GetAddressingModeValue(addressing);

    const bool signBitsMatch = !((cpu.A ^ value) & MOS6502_Status_N);
    const WORD addRes = cpu.A + value + cpu.Status.C;
    cpu.A = addRes;
    cpu.Status.UpdateStatusByValue(cpu.A, MOS6502_Status_Z | MOS6502_Status_N);
    cpu.Status.C = addRes > 0xFF;
    cpu.Status.V = signBitsMatch && ((cpu.A ^ value) & MOS6502_Status_N);
}

/**
 * @brief Add with Carry
 * @addressing Immediate
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ADC_IM(MOS6502 &cpu) {
    PerformADC(cpu, MOS6502_AddressingMode::Immediate);
}

/**
 * @brief Add with Carry
 * @addressing Zero Page
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ADC_ZP(MOS6502 &cpu) {
    PerformADC(cpu, MOS6502_AddressingMode::ZeroPage);
}

/**
 * @brief Add with Carry
 * @addressing Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ADC_ZPX(MOS6502 &cpu) {
    PerformADC(cpu, MOS6502_AddressingMode::ZeroPage_X);
}

/**
 * @brief Add with Carry
 * @addressing Absolute
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ADC_ABS(MOS6502 &cpu) {
    PerformADC(cpu, MOS6502_AddressingMode::Absolute);
}

/**
 * @brief Add with Carry
 * @addressing Absolute,X
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ADC_ABSX(MOS6502 &cpu) {
    PerformADC(cpu, MOS6502_AddressingMode::Absolute_X);
}

/**
 * @brief Add with Carry
 * @addressing Absolute,Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ADC_ABSY(MOS6502 &cpu) {
    PerformADC(cpu, MOS6502_AddressingMode::Absolute_Y);
}

/**
 * @brief Add with Carry
 * @addressing (Indirect,X)
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ADC_INDX(MOS6502 &cpu) {
    PerformADC(cpu, MOS6502_AddressingMode::Indirect_X);
}

/**
 * @brief Add with Carry
 * @addressing (Indirect),Y
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_ADC_INDY(MOS6502 &cpu) {
    PerformADC(cpu, MOS6502_AddressingMode::Indirect_Y);
}
