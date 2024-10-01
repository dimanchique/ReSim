#pragma once

#include "core/types.h"

struct I8086;
struct Memory;

/**
 * @brief Instruction decoder.
 * @details Looking for instruction in the instruction table using given OpCode.
 * @details Decode success status is true if:
 * @details - OpCode is not STOP_OPCODE (default invalid value)
 * @details - Instruction is not INVALID_OP (default invalid instruction)
 * @param opcode Instruction opcode to look for.
 * @param memory Memory struct instance.
 * @param cpu I8086 struct instance.
 * @return Decode success status.
 */
bool DecodeInstruction(BYTE opcode, Memory &memory, I8086 &cpu);
