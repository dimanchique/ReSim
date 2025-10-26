#pragma once
#include "I8080.h"

/**
 * @brief No Operation Implementation
 * @details The NOP instruction causes no changes to the processor
 * other than the normal incrementing of the program counter to the next instruction.
 * @param cpu I8080 struct instance.
 */
void I8080_NOP(I8080&) {}
