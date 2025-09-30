#pragma once

#include "core/types.h"

class I8080;

/**
 * @brief Instruction decoder.
 * @details Looking for instruction in the instruction table using given OpCode.
 * Decode success status is true if:
 * - OpCode is not I8080_STOP_OPCODE
 *      - decoder has reached the end of program (manually inserted OpCode)
 * - Instruction is not INVALID_OP
 *      - unexpected OpCode was fetched
 * @param opcode Instruction opcode to look for.
 * @param memory Memory struct instance.
 * @param cpu I8080 struct instance.
 * @return Decode success.
 */
bool DecodeInstruction(BYTE opcode, I8080 &cpu);
