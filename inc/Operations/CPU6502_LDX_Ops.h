#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

/**
 * @instruction Load X Register – Immediate
 * @short X,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_LDX_IM(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Load X Register – Zero Page
 * @short X,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_LDX_ZP(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Load X Register – Zero Page,Y
 * @short X,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_LDX_ZPY(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Load X Register – Absolute
 * @short X,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_LDX_ABS(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Load X Register – Absolute,Y
 * @short X,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_LDX_ABSY(Memory &memory, CPU6502 &cpu);
