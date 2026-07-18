#pragma once
#include "MOS6502.h"

/**
 * @brief Transfer Implementation
 * @details Copies the current contents of the sourceRegister into the destinationRegister
 * and sets the zero and negative flags as appropriate.
 * @param sourceRegister Register to transfer from.
 * @param destinationRegister Register to transfer to.
 * @param cpu MOS6502 struct instance.
 */
FORCE_INLINE void PerformT(const BYTE sourceRegister, BYTE &destinationRegister, MOS6502 &cpu) {
    destinationRegister = sourceRegister;
    ++cpu.cycles;
    cpu.Status.UpdateStatusByValue(destinationRegister, MOS6502_Status_Z | MOS6502_Status_N);
}

/**
 * @brief Transfer Accumulator to X
 * @addressing Implied
 * @details Copies the current contents of the accumulator into the X register
 * and sets the zero and negative flags as appropriate.
 * @short X = A
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_TAX_IMPL(MOS6502 &cpu) {
    PerformT(cpu.A, cpu.X, cpu);
}

/**
 * @brief Transfer X to Accumulator
 * @addressing Implied
 * @details Copies the current contents of the X register into the accumulator
 * and sets the zero and negative flags as appropriate.
 * @short A = X
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_TXA_IMPL(MOS6502 &cpu) {
    PerformT(cpu.X, cpu.A, cpu);
}

/**
 * @brief Transfer Accumulator to Y
 * @addressing Implied
 * @details Copies the current contents of the accumulator into the Y register
 * and sets the zero and negative flags as appropriate.
 * @short Y = A
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_TAY_IMPL(MOS6502 &cpu) {
    PerformT(cpu.A, cpu.Y, cpu);
}

/**
 * @brief Transfer Y to Accumulator
 * @addressing Implied
 * @details Copies the current contents of the Y register into the accumulator
 * and sets the zero and negative flags as appropriate.
 * @short A = Y
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_TYA_IMPL(MOS6502 &cpu) {
    PerformT(cpu.Y, cpu.A, cpu);
}

/**
 * @brief Transfer Stack Pointer to X
 * @addressing Implied
 * @details Copies the current contents of the stack register into the X register
 * and sets the zero and negative flags as appropriate.
 * @short X = S
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_TSX_IMPL(MOS6502 &cpu) {
    PerformT(cpu.SP, cpu.X, cpu);
}

/**
 * @brief Transfer X to Stack Pointer
 * @addressing Implied
 * @details Copies the current contents of the X register into the stack register.
 * @short S = X
 * @param cpu MOS6502 struct instance.
 */
void MOS6502_TXS_IMPL(MOS6502 &cpu) {
    PerformT(cpu.X, cpu.SP, cpu);
}
