#include "I8080/I8080_OpHelpers.h"
#include "I8080/Operations/ADD_Ops.h"
#include "I8080/Operations/ADC_Ops.h"
#include "I8080/Operations/ANA_Ops.h"
#include "I8080/Operations/ANI_Ops.h"
#include "I8080/Operations/ROT_Ops.h"
#include "I8080/Operations/LDA_Ops.h"
#include "I8080/Operations/LXI_Ops.h"
#include "I8080/Operations/STA_Ops.h"
#include "I8080/Operations/NOP_Ops.h"
#include "I8080/Operations/MOV_A_Ops.h"
#include "I8080/Operations/MOV_B_Ops.h"
#include "I8080/Operations/MOV_C_Ops.h"
#include "I8080/Operations/MOV_D_Ops.h"
#include "I8080/Operations/MOV_E_Ops.h"
#include "I8080/Operations/MOV_H_Ops.h"
#include "I8080/Operations/MOV_L_Ops.h"
#include "I8080/Operations/MOV_M_Ops.h"
#include "I8080/Operations/MVI_Ops.h"
#include "I8080/Operations/INX_Ops.h"
#include "I8080/Operations/INR_Ops.h"
#include "I8080/Operations/DCX_Ops.h"
#include "I8080/Operations/DAA_Ops.h"
#include "I8080/Operations/DAD_Ops.h"
#include "I8080/Operations/DCR_Ops.h"
#include "I8080/Operations/ORA_Ops.h"
#include "I8080/Operations/ORI_Ops.h"
#include "I8080/Operations/XR_Ops.h"
#include "I8080/Operations/POP_Ops.h"
#include "I8080/Operations/PUSH_Ops.h"
#include "I8080/Operations/SHLD_Ops.h"
#include "I8080/Operations/LHLD_Ops.h"
#include "I8080/Operations/SPHL_Ops.h"
#include "I8080/Operations/PCHL_Ops.h"
#include "I8080/Operations/STC_Ops.h"
#include "I8080/Operations/CMC_Ops.h"
#include "I8080/Operations/CMA_Ops.h"
#include "I8080/Operations/CMP_Ops.h"
#include "I8080/Operations/XCHG_Ops.h"
#include "I8080/Operations/XTHL_Ops.h"
#include "I8080/Operations/JUMP_Ops.h"
#include "I8080/Operations/CALL_Ops.h"
#include "I8080/Operations/RETURN_Ops.h"
#include "I8080/Operations/RST_Ops.h"
#include "I8080/Operations/SUB_Ops.h"
#include "I8080/Operations/SBB_Ops.h"

static void I8080_INVALID_OP(Memory&, I8080&) {}

using OpSignature = void (*)(Memory&, I8080&);

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
        return false;
    instruction(memory, cpu);
    cpu.cycles++; // additional decode cycle
    return true;
}
