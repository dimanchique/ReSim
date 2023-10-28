#pragma once
#include "Types.h"

struct CPU6502;
struct Memory;

/**
 * @description Instruction decoder
 * @description Looking for instruction in the instruction table using given OpCode
 * @note Decode success status is true if:
 * @note - OpCode is not 0xFF (default invalid value)
 * @note - Instruction is not FAKE_NOP (default invalid instruction)
 * @param opcode Instruction opcode to look for
 * @param memory Memory struct instance
 * @param cpu CPU6502 struct instance
 * @return Decode success status
 */
bool DecodeCommand(BYTE opcode, Memory &memory, CPU6502 &cpu);
