#include "I8086.h"
#include "Operations/ADD_Ops.h"
#include "Operations/SBB_Ops.h"
#include "Operations/CMP_Ops.h"
#include "Operations/SUB_Ops.h"
#include "Operations/NOP_Ops.h"
#include "Operations/GRP_Ops.h"
#include "Operations/CALL_Ops.h"
#include "Operations/OR_Ops.h"
#include "Operations/AND_Ops.h"
#include "Operations/XCHG_Ops.h"
#include "Operations/ST_CL_Ops.h"
#include "Operations/LAHF_SAHF_Ops.h"
#include "Operations/CBW_CWD_Ops.h"
#include "Operations/PUSH_POP_Ops.h"
#include "Operations/MOV_Ops.h"
#include "Operations/MOV_Imm_Ops.h"
#include "Operations/MOV_Direct_Ops.h"
#include "Operations/LOAD_Ops.h"
#include "Operations/XLAT_Ops.h"
#include "Operations/JMP_Ops.h"
#include "Operations/LOOP_Ops.h"
#include "Operations/TEST_Ops.h"
#include "Operations/DAA_DAS_Ops.h"
#include "Operations/AA_Ops.h"
#include "Operations/MISC_Ops.h"

static void I8086_INVALID_OP(BYTE, I8086&) {}

using OpSignature = void (*)(BYTE, I8086&);

/** Instructions lookup table */
constexpr static OpSignature Ops[] =
        {
#ifndef ADD_CALL
#define ADD_CALL(call) I8086_##call
#include "I8086_OpCodesList_Main.h"
#undef ADD_CALL
#endif
        };

bool DecodeInstruction(const BYTE opcode, I8086 &cpu) {
    const OpSignature &instruction = Ops[opcode];
    if(opcode == I8086_STOP_OPCODE || instruction == I8086_INVALID_OP)
        return false;
    instruction(opcode, cpu);
    return true;
}
