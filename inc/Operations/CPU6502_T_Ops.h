#pragma once
#include "CPU6502.h"

/**
 * @instruction Transfer (generic)
 * @description
 * Copies the current contents of the sourceRegister into the destinationRegister and sets the zero and negative flags as appropriate.
 * @param sourceRegister Register to transfer from
 * @param destinationRegister Register to transfer to
 * @param cpu CPU6502 struct instance
 */
inline void GenericT(const BYTE sourceRegister, BYTE &destinationRegister, CPU6502 &cpu) {
    destinationRegister = sourceRegister;
    cpu.Status.UpdateStatusByValue(destinationRegister, CPU6502_Status_Z | CPU6502_Status_N);
    cpu.cycles++;
}

/**
 * @instruction Transfer Accumulator to X
 * @description
 * Copies the current contents of the accumulator into the X register and sets the zero and negative flags as appropriate.
 * @short X = A
 * @addressing Implied
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_TAX_IMPL(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Transfer X to Accumulator
 * @description
 * Copies the current contents of the X register into the accumulator and sets the zero and negative flags as appropriate.
 * @short A = X
 * @addressing Implied
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_TXA_IMPL(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Transfer Accumulator to Y
 * @description
 * Copies the current contents of the accumulator into the Y register and sets the zero and negative flags as appropriate.
 * @short Y = A
 * @addressing Implied
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_TAY_IMPL(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Transfer Accumulator to X
 * @description
 * Copies the current contents of the accumulator into the X register and sets the zero and negative flags as appropriate.
 * @short X = A
 * @addressing Implied
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_TYA_IMPL(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Transfer Stack Pointer to X
 * @description
 * Copies the current contents of the stack register into the X register and sets the zero and negative flags as appropriate.
 * @short X = S
 * @addressing Implied
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_TSX_IMPL(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Transfer X to Stack Pointer
 * @description
 * Copies the current contents of the X register into the stack register.
 * @short S = X
 * @addressing Implied
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_TXS_IMPL(Memory &memory, CPU6502 &cpu);
