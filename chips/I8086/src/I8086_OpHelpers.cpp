#include "base/memory.h"
#include "I8086/I8086.h"

static void I8086_INVALID_OP(BYTE, Memory&, I8086&) {}

using OpSignature = void (*)(BYTE, Memory&, I8086&);

/** Instructions lookup table */
constexpr static OpSignature Ops[] =
        {
#ifndef ADD_CALL
#define ADD_CALL(call) I8086_##call
#include "I8086/I8086_OpCodesList.h"
#undef ADD_CALL
#endif
        };

bool DecodeInstruction(const BYTE opcode, Memory &memory, I8086 &cpu) {
    const auto &instruction = Ops[opcode];
    if(opcode == STOP_OPCODE || instruction == I8086_INVALID_OP)
        return false;
    instruction(opcode, memory, cpu);
    cpu.cycles++; // additional decode cycle
    return true;
}
