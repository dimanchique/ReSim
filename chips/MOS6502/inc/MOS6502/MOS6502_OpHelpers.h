#pragma once

#include "core/types.h"

struct MOS6502;
struct Memory;

/**
 * @brief Instruction decoder.
 * @details Looking for instruction in the instruction table using given OpCode.
 * @details Decode success status is true if:
 * @details - OpCode is not 0xFF (default invalid value)
 * @details - Instruction is not INVALID_OP (default invalid instruction)
 * @param opcode Instruction opcode to look for.
 * @param memory Memory struct instance.
 * @param cpu MOS6502 struct instance.
 * @return Decode success status.
 */
bool DecodeInstruction(BYTE opcode, Memory &memory, MOS6502 &cpu);
