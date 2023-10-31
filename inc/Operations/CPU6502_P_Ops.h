#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

/**
 * @instruction Push Accumulator – Implied
 * @details Pushes a copy of the accumulator on to the stack.
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_PHA_IMPL(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Pull Accumulator – Implied
 * @details Pulls an 8 bit value from the stack and into the accumulator.
 * The zero and negative flags are set as appropriate.
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_PLA_IMPL(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Push Processor Status – Implied
 * @details Pushes a copy of the status flags on to the stack.
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_PHP_IMPL(Memory &memory, CPU6502 &cpu);

/**
 * @instruction Pull Processor Status – Implied
 * @details Pulls an 8 bit value from the stack and into the processor flags.
 * The flags will take on new states as determined by the value pulled.
 * @param memory Memory struct instance.
 * @param cpu CPU6502 struct instance.
 */
void CPU6502_PLP_IMPL(Memory &memory, CPU6502 &cpu);
