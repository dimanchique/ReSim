#include "MOS6502/MOS6502_OpHelpers.h"
#include "MOS6502/Operations/JMP_JSR_RTS_RTI_Ops.h"
#include "MOS6502/Operations/LDA_Ops.h"
#include "MOS6502/Operations/LDX_Ops.h"
#include "MOS6502/Operations/LDY_Ops.h"
#include "MOS6502/Operations/STA_Ops.h"
#include "MOS6502/Operations/STX_Ops.h"
#include "MOS6502/Operations/STY_Ops.h"
#include "MOS6502/Operations/CL_Ops.h"
#include "MOS6502/Operations/SE_Ops.h"
#include "MOS6502/Operations/DEC_Ops.h"
#include "MOS6502/Operations/INC_Ops.h"
#include "MOS6502/Operations/T_Ops.h"
#include "MOS6502/Operations/P_Ops.h"
#include "MOS6502/Operations/AND_Ops.h"
#include "MOS6502/Operations/ORA_Ops.h"
#include "MOS6502/Operations/EOR_Ops.h"
#include "MOS6502/Operations/ASL_Ops.h"
#include "MOS6502/Operations/LSR_Ops.h"
#include "MOS6502/Operations/BIT_Ops.h"
#include "MOS6502/Operations/ROL_Ops.h"
#include "MOS6502/Operations/ROR_Ops.h"
#include "MOS6502/Operations/NOP_Op.h"
#include "MOS6502/Operations/B_Ops.h"
#include "MOS6502/Operations/CMP_Ops.h"
#include "MOS6502/Operations/CPX_Ops.h"
#include "MOS6502/Operations/CPY_Ops.h"
#include "MOS6502/Operations/ADC_Ops.h"
#include "MOS6502/Operations/SBC_Ops.h"

static void MOS6502_INVALID_OP(Memory&, MOS6502&) {}

using OpSignature = void (*)(Memory&, MOS6502&);

/** Instructions lookup table */
constexpr static OpSignature Ops[] =
        {
#ifndef ADD_CALL
#   define ADD_CALL(call) MOS6502_##call
#   include "MOS6502/MOS6502_OpCodesList.h"
#   undef ADD_CALL
#endif
        };

bool DecodeInstruction(const BYTE opcode, Memory &memory, MOS6502 &cpu) {
    const auto &instruction = Ops[opcode];
    if(opcode == STOP_OPCODE || instruction == MOS6502_INVALID_OP)
        return false;
    instruction(memory, cpu);
    return true;
}
