#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

/**
 * @instruction Load Accumulator – Immediate
 * @short A,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_LDA_IM(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Load Accumulator – Zero Page
 * @short A,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_LDA_ZP(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Load Accumulator – Zero Page,X
 * @short A,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_LDA_ZPX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Load Accumulator – Absolute
 * @short A,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_LDA_ABS(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Load Accumulator – Absolute,X
 * @short A,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_LDA_ABSX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Load Accumulator – Absolute,Y
 * @short A,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_LDA_ABSY(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Load Accumulator – (Indirect,X)
 * @short A,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_LDA_INDX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Load Accumulator – (Indirect),Y
 * @short A,Z,N = M
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_LDA_INDY(Memory &memory, CPU6502 &cpu);
