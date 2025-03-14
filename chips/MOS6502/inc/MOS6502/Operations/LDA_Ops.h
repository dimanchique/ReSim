#pragma once
#include "LD_Ops.h"

/**
 * @brief Load Accumulator
 * @addressing Immediate
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDA_IM(MOS6502 &cpu) {
    PerformLDA(cpu, MOS6502_AddressingMode::Immediate);
}

/**
 * @brief Load Accumulator
 * @addressing Zero Page
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDA_ZP(MOS6502 &cpu) {
    PerformLDA(cpu, MOS6502_AddressingMode::ZeroPage);
}

/**
 * @brief Load Accumulator
 * @addressing Zero Page,X
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDA_ZPX(MOS6502 &cpu) {
    PerformLDA(cpu, MOS6502_AddressingMode::ZeroPage_X);
}

/**
 * @brief Load Accumulator
 * @addressing Absolute
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDA_ABS(MOS6502 &cpu) {
    PerformLDA(cpu, MOS6502_AddressingMode::Absolute);
}

/**
 * @brief Load Accumulator
 * @addressing Absolute,X
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDA_ABSX(MOS6502 &cpu) {
    PerformLDA(cpu, MOS6502_AddressingMode::Absolute_X);
}

/**
 * @brief Load Accumulator
 * @addressing Absolute,Y
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDA_ABSY(MOS6502 &cpu) {
    PerformLDA(cpu, MOS6502_AddressingMode::Absolute_Y);
}

/**
 * @brief Load Accumulator
 * @addressing (Indirect,X)
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDA_INDX(MOS6502 &cpu) {
    PerformLDA(cpu, MOS6502_AddressingMode::Indirect_X);
}

/**
 * @brief Load Accumulator
 * @addressing (Indirect),Y
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_LDA_INDY(MOS6502 &cpu) {
    PerformLDA(cpu, MOS6502_AddressingMode::Indirect_Y);
}
