#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

/**
 * @instruction Load Y Register – Immediate
 * @short Y,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_LDY_IM(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Load Y Register – Zero Page
 * @short Y,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_LDY_ZP(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Load Y Register – Zero Page,X
 * @short Y,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_LDY_ZPX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Load Y Register – Absolute
 * @short Y,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_LDY_ABS(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Load Y Register – Absolute,X
 * @short Y,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_LDY_ABSX(Memory &memory, CPU6502 &cpu);
