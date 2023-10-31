#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

/**
 * @instruction Compare Accumulator – Immediate
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_CMP_IM(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Compare Accumulator – Zero Page
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_CMP_ZP(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Compare Accumulator – Zero Page,X
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_CMP_ZPX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Compare Accumulator – Absolute
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_CMP_ABS(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Compare Accumulator – Absolute,X
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_CMP_ABSX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Compare Accumulator – Absolute,Y
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_CMP_ABSY(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Compare Accumulator – (Indirect,X)
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_CMP_INDX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Compare Accumulator – (Indirect),Y
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_CMP_INDY(Memory &memory, CPU6502 &cpu);
