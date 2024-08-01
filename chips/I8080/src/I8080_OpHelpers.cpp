#include "I8080/I8080_OpHelpers.h"
#include "I8080/Operations/I8080_ADD_Ops.h"
#include "I8080/Operations/I8080_ADC_Ops.h"
#include "I8080/Operations/I8080_ANA_Ops.h"
#include "I8080/Operations/I8080_ANI_Ops.h"
#include "I8080/Operations/I8080_ROT_Ops.h"
#include "I8080/Operations/I8080_LDA_Ops.h"
#include "I8080/Operations/I8080_LXI_Ops.h"
#include "I8080/Operations/I8080_STA_Ops.h"
#include "I8080/Operations/I8080_NOP_Ops.h"
#include "I8080/Operations/I8080_MOV_A_Ops.h"
#include "I8080/Operations/I8080_MOV_B_Ops.h"
#include "I8080/Operations/I8080_MOV_C_Ops.h"
#include "I8080/Operations/I8080_MOV_D_Ops.h"
#include "I8080/Operations/I8080_MOV_E_Ops.h"
#include "I8080/Operations/I8080_MOV_H_Ops.h"
#include "I8080/Operations/I8080_MOV_L_Ops.h"
#include "I8080/Operations/I8080_MOV_M_Ops.h"
#include "I8080/Operations/I8080_MVI_Ops.h"
#include "I8080/Operations/I8080_INX_Ops.h"
#include "I8080/Operations/I8080_INR_Ops.h"
#include "I8080/Operations/I8080_DCX_Ops.h"
#include "I8080/Operations/I8080_DAA_Ops.h"
#include "I8080/Operations/I8080_DAD_Ops.h"
#include "I8080/Operations/I8080_DCR_Ops.h"
#include "I8080/Operations/I8080_ORA_Ops.h"
#include "I8080/Operations/I8080_ORI_Ops.h"
#include "I8080/Operations/I8080_XR_Ops.h"
#include "I8080/Operations/I8080_POP_Ops.h"
#include "I8080/Operations/I8080_PUSH_Ops.h"
#include "I8080/Operations/I8080_SHLD_Ops.h"
#include "I8080/Operations/I8080_LHLD_Ops.h"
#include "I8080/Operations/I8080_SPHL_Ops.h"
#include "I8080/Operations/I8080_PCHL_Ops.h"
#include "I8080/Operations/I8080_STC_Ops.h"
#include "I8080/Operations/I8080_CMC_Ops.h"
#include "I8080/Operations/I8080_CMA_Ops.h"
#include "I8080/Operations/I8080_CMP_Ops.h"
#include "I8080/Operations/I8080_XCHG_Ops.h"
#include "I8080/Operations/I8080_XTHL_Ops.h"
#include "I8080/Operations/I8080_JUMP_Ops.h"
#include "I8080/Operations/I8080_CALL_Ops.h"
#include "I8080/Operations/I8080_RETURN_Ops.h"
#include "I8080/Operations/I8080_RST_Ops.h"
#include "I8080/Operations/I8080_SUB_Ops.h"
#include "I8080/Operations/I8080_SBB_Ops.h"

static void I8080_INVALID_OP(Memory &memory, I8080 &cpu) {}

using OpSignature = void (*)(Memory &, I8080 &);

/** Instructions lookup table */
constexpr static OpSignature Ops[] =
        {
#ifndef ADD_CALL
#define ADD_CALL(call) I8080_##call
#include "I8080/I8080_OpCodesList.h"
#undef ADD_CALL
#endif
        };

bool DecodeInstruction(const BYTE opcode, Memory &memory, I8080 &cpu) {
    const auto &instruction = Ops[opcode];
    if(opcode == STOP_OPCODE || instruction == I8080_INVALID_OP)
    {
        cpu.cycles -= 3; // revert false fetch cycles
        return false;
    }
    instruction(memory, cpu);
    cpu.cycles++; // additional decode cycle
    return true;
}
