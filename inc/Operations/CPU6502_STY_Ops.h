#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

/**
 * @instruction Store Y Register
 * @description
 * Stores the contents of the Y register into memory.
 * @short M = Y
 * @addressing Zero Page
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_STY_ZP(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Store Y Register
 * @description
 * Stores the contents of the Y register into memory.
 * @short M = Y
 * @addressing Zero Page,X
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_STY_ZPX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Store Y Register
 * @description
 * Stores the contents of the Y register into memory.
 * @short M = Y
 * @addressing Absolute
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_STY_ABS(Memory &memory, CPU6502 &cpu);
