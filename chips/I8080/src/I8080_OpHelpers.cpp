#include "I8080_OpHelpers.h"
#include "Operations/ADD_Ops.h"
#include "Operations/ADC_Ops.h"
#include "Operations/ANA_Ops.h"
#include "Operations/ANI_Ops.h"
#include "Operations/ROT_Ops.h"
#include "Operations/LDA_Ops.h"
#include "Operations/LXI_Ops.h"
#include "Operations/STA_Ops.h"
#include "Operations/NOP_Ops.h"
#include "Operations/MOV_A_Ops.h"
#include "Operations/MOV_B_Ops.h"
#include "Operations/MOV_C_Ops.h"
#include "Operations/MOV_D_Ops.h"
#include "Operations/MOV_E_Ops.h"
#include "Operations/MOV_H_Ops.h"
#include "Operations/MOV_L_Ops.h"
#include "Operations/MOV_M_Ops.h"
#include "Operations/MVI_Ops.h"
#include "Operations/INX_Ops.h"
#include "Operations/INR_Ops.h"
#include "Operations/DCX_Ops.h"
#include "Operations/DAA_Ops.h"
#include "Operations/DAD_Ops.h"
#include "Operations/DCR_Ops.h"
#include "Operations/ORA_Ops.h"
#include "Operations/ORI_Ops.h"
#include "Operations/XR_Ops.h"
#include "Operations/POP_Ops.h"
#include "Operations/PUSH_Ops.h"
#include "Operations/SHLD_Ops.h"
#include "Operations/LHLD_Ops.h"
#include "Operations/SPHL_Ops.h"
#include "Operations/PCHL_Ops.h"
#include "Operations/STC_Ops.h"
#include "Operations/CM_Ops.h"
#include "Operations/CMP_Ops.h"
#include "Operations/IO_Ops.h"
#include "Operations/XCHG_Ops.h"
#include "Operations/XTHL_Ops.h"
#include "Operations/JUMP_Ops.h"
#include "Operations/CALL_Ops.h"
#include "Operations/RETURN_Ops.h"
#include "Operations/RST_Ops.h"
#include "Operations/SUB_Ops.h"
#include "Operations/SBB_Ops.h"
#include "Operations/INT_Ops.h"

#ifdef PRINT_DIAGNOSTICS
/** Instructions names table */
constexpr static char* OpNames[] =
        {
#ifndef ADD_CALL
#define ADD_CALL(call) #call
#include "I8080_OpCodesList_Main.h"
#undef ADD_CALL
#endif
        };
#endif

static void I8080_INVALID_OP(I8080&) {}

using OpSignature = void (*)(I8080&);

/** Instructions lookup table */
constexpr static OpSignature Ops[] =
        {
#ifndef ADD_CALL
#define ADD_CALL(call) I8080_##call
#include "I8080_OpCodesList_Main.h"
#undef ADD_CALL
#endif
        };

bool DecodeInstruction(const BYTE opcode, I8080 &cpu) {
    const OpSignature &instruction = Ops[opcode];
#ifdef PRINT_DIAGNOSTICS
    std::cout << OpNames[opcode]
    << " ("
    << std::hex
    << int(opcode)
    << ") ";
#endif
    if((opcode == I8080_OpCodes_Main::RET && cpu.SP == 0xFFFF) || instruction == I8080_INVALID_OP)
        return false;
    instruction(cpu);
    cpu.cycles++; // additional decode cycle
    return true;
}
