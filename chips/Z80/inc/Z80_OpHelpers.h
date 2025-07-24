#pragma once

#include "core/types.h"

class Z80;

/**
 * @brief Instruction decoder.
 * @details Looking for instruction in the instruction table using given OpCode.
 * Decode success status is true if:
 * - OpCode is not STOP_OPCODE
 *      - decoder has reached the end of program (manually inserted OpCode)
 * - Instruction is not INVALID_OP
 *      - unexpected OpCode was fetched
 * @param opcode Instruction opcode to look for.
 * @param memory Memory struct instance.
 * @param cpu Z80 struct instance.
 * @return Decode success.
 */
bool DecodeInstruction(BYTE opcode, Z80 &cpu);
