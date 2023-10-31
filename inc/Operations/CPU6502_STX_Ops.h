#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

/**
 * @instruction Store X Register – Zero Page
 * @details Stores the contents of the X register into memory.
 * @short M = X
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_STX_ZP(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Store X Register – Zero Page,Y
 * @details Stores the contents of the X register into memory.
 * @short M = X
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_STX_ZPY(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Store X Register – Absolute
 * @details Stores the contents of the X register into memory.
 * @short M = X
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_STX_ABS(Memory &memory, CPU6502 &cpu);
