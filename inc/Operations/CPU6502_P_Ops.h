#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

/**
 * @instruction Push Accumulator
 * @description
 * Pushes a copy of the accumulator on to the stack.
 * @addressing Implied
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_PHA_IMPL(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Pull Accumulator
 * @description
 * Pulls an 8 bit value from the stack and into the accumulator.
 * The zero and negative flags are set as appropriate.
 * @addressing Implied
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_PLA_IMPL(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Push Processor Status
 * @description
 * Pushes a copy of the status flags on to the stack.
 * @addressing Implied
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_PHP_IMPL(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Pull Processor Status
 * @description
 * Pulls an 8 bit value from the stack and into the processor flags.
 * The flags will take on new states as determined by the value pulled.
 * @addressing Implied
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 */
void CPU6502_PLP_IMPL(Memory &memory, CPU6502 &cpu);
