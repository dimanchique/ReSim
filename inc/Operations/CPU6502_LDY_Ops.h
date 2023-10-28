#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

/**
 * @instruction Load Y Register
 * @short Y,Z,N = M
 * @addressing Immediate
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_LDY_IM(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Load Y Register
 * @short Y,Z,N = M
 * @addressing Zero Page
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_LDY_ZP(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Load Y Register
 * @short Y,Z,N = M
 * @addressing Zero Page,X
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_LDY_ZPX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Load Y Register
 * @short Y,Z,N = M
 * @addressing Absolute
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_LDY_ABS(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Load Y Register
 * @short Y,Z,N = M
 * @addressing Absolute,X
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_LDY_ABSX(Memory &memory, CPU6502 &cpu);
