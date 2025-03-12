#include "memory.h"
#include "I8086/I8086.h"
#include "I8086/Operations/NOP_Ops.h"
#include "I8086/Operations/GRP_Ops.h"
#include "I8086/Operations/OR_Ops.h"
#include "I8086/Operations/AND_Ops.h"
#include "I8086/Operations/XCHG_Ops.h"
#include "I8086/Operations/ST_CL_Ops.h"
#include "I8086/Operations/LAHF_SAHF_Ops.h"
#include "I8086/Operations/CBW_CWD_Ops.h"
#include "I8086/Operations/PUSH_POP_Ops.h"
#include "I8086/Operations/MOV_Imm_Ops.h"

static void I8086_INVALID_OP(BYTE, I8086&) {}

using OpSignature = void (*)(BYTE, I8086&);

/** Instructions lookup table */
constexpr static OpSignature Ops[] =
        {
#ifndef ADD_CALL
#define ADD_CALL(call) I8086_##call
#include "I8086/I8086_OpCodesList.h"
#undef ADD_CALL
#endif
        };

bool DecodeInstruction(const BYTE opcode, I8086 &cpu) {
    const auto &instruction = Ops[opcode];
    if(opcode == STOP_OPCODE || instruction == I8086_INVALID_OP)
        return false;
    instruction(opcode, cpu);
    return true;
}
