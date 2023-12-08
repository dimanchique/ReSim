#pragma once
#include "CPU6502.h"

/**
 * @instruction Transfer (generic)
 * @details Copies the current contents of the sourceRegister into the destinationRegister
 * and sets the zero and negative flags as appropriate.
 * @param sourceRegister Register to transfer from.
 * @param destinationRegister Register to transfer to.
 * @param cpu CPU6502 struct instance.
 */
FORCE_INLINE void GenericT(const BYTE sourceRegister, BYTE &destinationRegister, CPU6502 &cpu) {
    destinationRegister = sourceRegister;
    cpu.Status.UpdateStatusByValue(destinationRegister, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.cycles++;
}

/**
 * @instruction Transfer Accumulator to X – Implied
 * @details Copies the current contents of the accumulator into the X register
 * and sets the zero and negative flags as appropriate.
 * @short X = A
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
inline void CPU6502_TAX_IMPL(Memory &memory, CPU6502 &cpu) {
    GenericT(cpu.A, cpu.X, cpu);
}

/**
 * @instruction Transfer X to Accumulator – Implied
 * @details Copies the current contents of the X register into the accumulator
 * and sets the zero and negative flags as appropriate.
 * @short A = X
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
inline void CPU6502_TXA_IMPL(Memory &memory, CPU6502 &cpu) {
    GenericT(cpu.X, cpu.A, cpu);
}

/**
 * @instruction Transfer Accumulator to Y – Implied
 * @details Copies the current contents of the accumulator into the Y register
 * and sets the zero and negative flags as appropriate.
 * @short Y = A
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
inline void CPU6502_TAY_IMPL(Memory &memory, CPU6502 &cpu) {
    GenericT(cpu.A, cpu.Y, cpu);
}

/**
 * @instruction Transfer Accumulator to X – Implied
 * @details Copies the current contents of the accumulator into the X register
 * and sets the zero and negative flags as appropriate.
 * @short X = A
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
inline void CPU6502_TYA_IMPL(Memory &memory, CPU6502 &cpu) {
    GenericT(cpu.Y, cpu.A, cpu);
}

/**
 * @instruction Transfer Stack Pointer to X – Implied
 * @details Copies the current contents of the stack register into the X register
 * and sets the zero and negative flags as appropriate.
 * @short X = S
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
inline void CPU6502_TSX_IMPL(Memory &memory, CPU6502 &cpu) {
    GenericT(cpu.SP, cpu.X, cpu);
}

/**
 * @instruction Transfer X to Stack Pointer – Implied
 * @details Copies the current contents of the X register into the stack register.
 * @short S = X
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
inline void CPU6502_TXS_IMPL(Memory &memory, CPU6502 &cpu) {
    cpu.SP = cpu.X;
    cpu.cycles++;
}
