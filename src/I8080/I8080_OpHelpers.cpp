#include "I8080_OpHelpers.h"
#include "Operations/I8080_ADD_Ops.h"
#include "Operations/I8080_ANA_Ops.h"
#include "Operations/I8080_ANI_Ops.h"
#include "Operations/I8080_ROT_Ops.h"
#include "Operations/I8080_LDA_Ops.h"
#include "Operations/I8080_LXI_Ops.h"
#include "Operations/I8080_STA_Ops.h"
#include "Operations/I8080_NOP_Ops.h"
#include "Operations/I8080_MOV_A_Ops.h"
#include "Operations/I8080_MOV_B_Ops.h"
#include "Operations/I8080_MOV_C_Ops.h"
#include "Operations/I8080_MOV_D_Ops.h"
#include "Operations/I8080_MOV_E_Ops.h"
#include "Operations/I8080_MOV_H_Ops.h"
#include "Operations/I8080_MOV_L_Ops.h"
#include "Operations/I8080_MOV_M_Ops.h"
#include "Operations/I8080_MVI_Ops.h"
#include "Operations/I8080_JMP_Ops.h"
#include "Operations/I8080_JC_Ops.h"
#include "Operations/I8080_JNC_Ops.h"
#include "Operations/I8080_JZ_Ops.h"
#include "Operations/I8080_JNZ_Ops.h"
#include "Operations/I8080_JM_Ops.h"
#include "Operations/I8080_JP_Ops.h"
#include "Operations/I8080_JPO_Ops.h"
#include "Operations/I8080_JPE_Ops.h"
#include "Operations/I8080_INX_Ops.h"
#include "Operations/I8080_INR_Ops.h"
#include "Operations/I8080_DCX_Ops.h"
#include "Operations/I8080_DCR_Ops.h"
#include "Operations/I8080_ORA_Ops.h"
#include "Operations/I8080_ORI_Ops.h"
#include "Operations/I8080_XRA_Ops.h"
#include "Operations/I8080_XRI_Ops.h"
#include "Operations/I8080_POP_Ops.h"
#include "Operations/I8080_PUSH_Ops.h"
#include "Operations/I8080_SHLD_Ops.h"
#include "Operations/I8080_LHLD_Ops.h"
#include "Operations/I8080_SPHL_Ops.h"
#include "Operations/I8080_PCHL_Ops.h"
#include "Operations/I8080_STC_Ops.h"
#include "Operations/I8080_CMC_Ops.h"
#include "Operations/I8080_CMA_Ops.h"
#include "Operations/I8080_XCHG_Ops.h"
#include "Operations/I8080_XTHL_Ops.h"
#include "Operations/I8080_CALL_Ops.h"
#include "Operations/I8080_RET_Ops.h"
#include "Operations/I8080_CZ_Ops.h"
#include "Operations/I8080_RZ_Ops.h"
#include "Operations/I8080_CC_Ops.h"
#include "Operations/I8080_RC_Ops.h"
#include "Operations/I8080_CP_Ops.h"
#include "Operations/I8080_RP_Ops.h"
#include "Operations/I8080_CM_Ops.h"
#include "Operations/I8080_RM_Ops.h"
#include "Operations/I8080_CPO_Ops.h"
#include "Operations/I8080_RPO_Ops.h"
#include "Operations/I8080_CPE_Ops.h"
#include "Operations/I8080_RPE_Ops.h"
#include "Operations/I8080_CNZ_Ops.h"
#include "Operations/I8080_RNZ_Ops.h"
#include "Operations/I8080_CNC_Ops.h"
#include "Operations/I8080_RNC_Ops.h"
#include "Operations/I8080_RST_Ops.h"

static void I8080_INVALID_OP(Memory &memory, I8080 &cpu) {}

using OpSignature = void (*)(Memory &, I8080 &);

/** Instructions lookup table */
constexpr static OpSignature Ops[] =
        {
#ifndef ADD_CALL
#define ADD_CALL(call) I8080_##call
#include "I8080_OpCodesList.h"
#undef ADD_CALL
#endif
        };

bool DecodeCommand(const BYTE opcode, Memory &memory, I8080 &cpu) {
    if(opcode == 0x08) // one of unused OpCodes so it's pretty much OK to use it a stop flag
        return false;
    const auto &Instruction = Ops[opcode];
    Instruction(memory, cpu);
    return Instruction != I8080_INVALID_OP;
}
