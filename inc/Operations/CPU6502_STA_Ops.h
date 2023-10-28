#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

/**
 * @instruction Store Accumulator
 * @description
 * Stores the contents of the accumulator into memory.
 * @short M = A
 * @addressing Zero Page
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_STA_ZP(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Store Accumulator
 * @description
 * Stores the contents of the accumulator into memory.
 * @short M = A
 * @addressing Zero Page,X
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_STA_ZPX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Store Accumulator
 * @description
 * Stores the contents of the accumulator into memory.
 * @short M = A
 * @addressing Absolute
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_STA_ABS(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Store Accumulator
 * @description
 * Stores the contents of the accumulator into memory.
 * @short M = A
 * @addressing Absolute,X
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_STA_ABSX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Store Accumulator
 * @description
 * Stores the contents of the accumulator into memory.
 * @short M = A
 * @addressing Absolute,Y
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_STA_ABSY(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Store Accumulator
 * @description
 * Stores the contents of the accumulator into memory.
 * @short M = A
 * @addressing (Indirect,X)
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_STA_INDX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Store Accumulator
 * @description
 * Stores the contents of the accumulator into memory.
 * @short M = A
 * @addressing (Indirect),Y
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_STA_INDY(Memory &memory, CPU6502 &cpu);
