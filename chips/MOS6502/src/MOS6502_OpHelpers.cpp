#include "MOS6502_OpHelpers.h"
#include "Operations/JMP_JSR_RTS_RTI_Ops.h"
#include "Operations/LDA_Ops.h"
#include "Operations/LDX_Ops.h"
#include "Operations/LDY_Ops.h"
#include "Operations/STA_Ops.h"
#include "Operations/STX_Ops.h"
#include "Operations/STY_Ops.h"
#include "Operations/CL_Ops.h"
#include "Operations/SE_Ops.h"
#include "Operations/DEC_Ops.h"
#include "Operations/INC_Ops.h"
#include "Operations/T_Ops.h"
#include "Operations/P_Ops.h"
#include "Operations/AND_Ops.h"
#include "Operations/ORA_Ops.h"
#include "Operations/EOR_Ops.h"
#include "Operations/ASL_Ops.h"
#include "Operations/LSR_Ops.h"
#include "Operations/BIT_Ops.h"
#include "Operations/ROL_Ops.h"
#include "Operations/ROR_Ops.h"
#include "Operations/NOP_Ops.h"
#include "Operations/B_Ops.h"
#include "Operations/CMP_Ops.h"
#include "Operations/CPX_Ops.h"
#include "Operations/CPY_Ops.h"
#include "Operations/ADC_Ops.h"
#include "Operations/SBC_Ops.h"

static void MOS6502_INVALID_OP(MOS6502&) {}

using OpSignature = void (*)(MOS6502&);

/** Instructions lookup table */
constexpr static OpSignature Ops[] =
        {
#ifndef ADD_CALL
#   define ADD_CALL(call) MOS6502_##call
#   include "MOS6502_OpCodesList_Main.h"
#   undef ADD_CALL
#endif
        };

bool DecodeInstruction(const BYTE opcode, MOS6502 &cpu) {
    const OpSignature &instruction = Ops[opcode];
    if(opcode == STOP_OPCODE || instruction == MOS6502_INVALID_OP)
        return false;
    instruction(cpu);
    return true;
}
