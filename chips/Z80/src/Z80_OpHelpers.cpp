#include "Z80.h"
#include "Z80_OpCodes_Main.h"
#include "Z80_OpHelpers.h"

static void Z80_INVALID_OP(Z80&) {}

using OpSignature = void (*)(Z80&);

/** Instructions lookup table */
constexpr static OpSignature Ops[] =
        {
#ifndef ADD_CALL
#define ADD_CALL(call) Z80_##call
#include "Z80_OpCodesList_Main.h"
#undef ADD_CALL
#endif
        };

bool DecodeInstruction(const BYTE opcode, Z80 &cpu) {
    const OpSignature &instruction = Ops[opcode];
    if(opcode == Z80_STOP_OPCODE || instruction == Z80_INVALID_OP)
        return false;
    instruction(cpu);
    cpu.cycles++; // additional decode cycle
    return true;
}
