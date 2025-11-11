#pragma once

#include "core/types.h"

class MOS6502;

/**
 * @brief Instruction decoder.
 * @details Looking for instruction in the instruction table using given OpCode.
 * Decode success status is true if:
 * - OpCode is not RTS_IMPL and SP != 0xFF
 *      - decoder has reached the end of program
 * - Instruction is not INVALID_OP
 *      - unexpected OpCode was fetched
 * @param opcode Instruction opcode to look for.
 * @param cpu MOS6502 struct instance.
 * @return Decode success.
 */
bool DecodeInstruction(BYTE opcode, MOS6502 &cpu);
