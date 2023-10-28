#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

/**
 * @instruction Load Accumulator
 * @short A,Z,N = M
 * @addressing Immediate
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_LDA_IM(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Load Accumulator
 * @short A,Z,N = M
 * @addressing Zero Page
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_LDA_ZP(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Load Accumulator
 * @short A,Z,N = M
 * @addressing Zero Page,X
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_LDA_ZPX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Load Accumulator
 * @short A,Z,N = M
 * @addressing Absolute
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_LDA_ABS(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Load Accumulator
 * @short A,Z,N = M
 * @addressing Absolute,X
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_LDA_ABSX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Load Accumulator
 * @short A,Z,N = M
 * @addressing Absolute,Y
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_LDA_ABSY(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Load Accumulator
 * @short A,Z,N = M
 * @addressing (Indirect,X)
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_LDA_INDX(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Load Accumulator
 * @short A,Z,N = M
 * @addressing (Indirect),Y
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_LDA_INDY(Memory &memory, CPU6502 &cpu);
