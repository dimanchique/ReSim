#include <CPU6502_OpHelpers.h>
#include "Operations/CPU6502_JMP_JSR_RTS_RTI_Ops.h"
#include <Operations/CPU6502_LDA_Ops.h>
#include <Operations/CPU6502_LDX_Ops.h>
#include <Operations/CPU6502_LDY_Ops.h>
#include <Operations/CPU6502_STA_Ops.h>
#include <Operations/CPU6502_STX_Ops.h>
#include <Operations/CPU6502_STY_Ops.h>
#include "Operations/CPU6502_CL_Ops.h"
#include "Operations/CPU6502_SE_Ops.h"
#include "Operations/CPU6502_DEC_Ops.h"
#include "Operations/CPU6502_INC_Ops.h"
#include "Operations/CPU6502_T_Ops.h"
#include "Operations/CPU6502_P_Ops.h"
#include "Operations/CPU6502_AND_Ops.h"
#include "Operations/CPU6502_ORA_Ops.h"
#include "Operations/CPU6502_EOR_Ops.h"
#include "Operations/CPU6502_ASL_Ops.h"
#include "Operations/CPU6502_LSR_Ops.h"
#include "Operations/CPU6502_BIT_Ops.h"
#include <CPU6502.h>
#include <Memory.h>
#include <cstdio>

void DumpStack(U32 &Cycles, Memory &Memory, CPU6502 &CPU){
    const auto &Stat = CPU.Status;
    std::printf("Runtime information:\n");
    std::printf("\tCycles passed:   %d\n", Cycles);
    std::printf("\tProgram Counter: 0x%04x\n", CPU.PC);
    std::printf("\tStack Pointer:   0x%04x\n", CPU.SP + 0x100);
    std::printf("\tStatus Register: %d%d%d%d%d%d%d\n", Stat.C, Stat.Z, Stat.I, Stat.D, Stat.B, Stat.V, Stat.N);
    std::printf("\t                 CZIDBVN\n");
    std::printf("\tA Register:      0x%04x\n", CPU.A);
    std::printf("\tX Register:      0x%04x\n", CPU.X);
    std::printf("\tY Register:      0x%04x\n", CPU.Y);
}

void CPU6502_NOOP(U32 &Cycles, Memory &Memory, CPU6502 &CPU){
    DumpStack(Cycles, Memory, CPU);
}

using OpSignature = void (*)(U32 &, Memory &, CPU6502 &);

// Code generator placeholder begin
const static OpSignature Ops[] = {
	CPU6502_NOOP,      	CPU6502_ORA_INDX,  	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      
	CPU6502_ORA_ZP,    	CPU6502_ASL_ZP,    	CPU6502_NOOP,      	CPU6502_PHP_IMPL,  	CPU6502_ORA_IM,    
	CPU6502_ASL_ACC,   	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_ORA_ABS,   	CPU6502_ASL_ABS,   
	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_ORA_INDY,  	CPU6502_NOOP,      	CPU6502_NOOP,      
	CPU6502_NOOP,      	CPU6502_ORA_ZPX,   	CPU6502_ASL_ZPX,   	CPU6502_NOOP,      	CPU6502_CLC_IMPL,  
	CPU6502_ORA_ABSY,  	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_ORA_ABSX,  
	CPU6502_ASL_ABSX,  	CPU6502_NOOP,      	CPU6502_JSR_ABS,   	CPU6502_AND_INDX,  	CPU6502_NOOP,      
	CPU6502_NOOP,      	CPU6502_BIT_ZP,    	CPU6502_AND_ZP,    	CPU6502_NOOP,      	CPU6502_NOOP,      
	CPU6502_PLP_IMPL,  	CPU6502_AND_IM,    	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_BIT_ABS,   
	CPU6502_AND_ABS,   	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_AND_INDY,  
	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_AND_ZPX,   	CPU6502_NOOP,      
	CPU6502_NOOP,      	CPU6502_SEC_IMPL,  	CPU6502_AND_ABSY,  	CPU6502_NOOP,      	CPU6502_NOOP,      
	CPU6502_NOOP,      	CPU6502_AND_ABSX,  	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_RTI_IMPL,  
	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_EOR_ZP,    
	CPU6502_LSR_ZP,    	CPU6502_NOOP,      	CPU6502_PHA_IMPL,  	CPU6502_EOR_IM,    	CPU6502_LSR_ACC,   
	CPU6502_NOOP,      	CPU6502_JMP_ABS,   	CPU6502_EOR_ABS,   	CPU6502_LSR_ABS,   	CPU6502_NOOP,      
	CPU6502_NOOP,      	CPU6502_EOR_INDY,  	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      
	CPU6502_EOR_ZPX,   	CPU6502_LSR_ZPX,   	CPU6502_NOOP,      	CPU6502_CLI_IMPL,  	CPU6502_EOR_ABSY,  
	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_EOR_ABSX,  	CPU6502_LSR_ABSX,  
	CPU6502_NOOP,      	CPU6502_RTS_IMPL,  	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      
	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_PLA_IMPL,  
	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_JMP_IND,   	CPU6502_NOOP,      
	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      
	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      
	CPU6502_SEI_IMPL,  	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      
	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_STA_INDX,  
	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_STY_ZP,    	CPU6502_STA_ZP,    	CPU6502_STX_ZP,    
	CPU6502_NOOP,      	CPU6502_DEY_IMPL,  	CPU6502_NOOP,      	CPU6502_TXA_IMPL,  	CPU6502_NOOP,      
	CPU6502_STY_ABS,   	CPU6502_STA_ABS,   	CPU6502_STX_ABS,   	CPU6502_NOOP,      	CPU6502_NOOP,      
	CPU6502_STA_INDY,  	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_STY_ZPX,   	CPU6502_STA_ZPX,   
	CPU6502_STX_ZPY,   	CPU6502_NOOP,      	CPU6502_TYA_IMPL,  	CPU6502_STA_ABSY,  	CPU6502_TXS_IMPL,  
	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_STA_ABSX,  	CPU6502_NOOP,      	CPU6502_NOOP,      
	CPU6502_LDY_IM,    	CPU6502_LDA_INDX,  	CPU6502_LDX_IM,    	CPU6502_NOOP,      	CPU6502_LDY_ZP,    
	CPU6502_LDA_ZP,    	CPU6502_LDX_ZP,    	CPU6502_NOOP,      	CPU6502_TAY_IMPL,  	CPU6502_LDA_IM,    
	CPU6502_TAX_IMPL,  	CPU6502_NOOP,      	CPU6502_LDY_ABS,   	CPU6502_LDA_ABS,   	CPU6502_LDX_ABS,   
	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_LDA_INDY,  	CPU6502_NOOP,      	CPU6502_NOOP,      
	CPU6502_LDY_ZPX,   	CPU6502_LDA_ZPX,   	CPU6502_LDX_ZPY,   	CPU6502_NOOP,      	CPU6502_CLV_IMPL,  
	CPU6502_LDA_ABSY,  	CPU6502_TSX_IMPL,  	CPU6502_NOOP,      	CPU6502_LDY_ABSX,  	CPU6502_LDA_ABSX,  
	CPU6502_LDX_ABSY,  	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_EOR_INDX,  	CPU6502_NOOP,      
	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_DEC_ZP,    	CPU6502_NOOP,      
	CPU6502_INY_IMPL,  	CPU6502_NOOP,      	CPU6502_DEX_IMPL,  	CPU6502_NOOP,      	CPU6502_NOOP,      
	CPU6502_NOOP,      	CPU6502_DEC_ABS,   	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      
	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_DEC_ZPX,   
	CPU6502_NOOP,      	CPU6502_CLD_IMPL,  	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      
	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_DEC_ABSX,  	CPU6502_NOOP,      	CPU6502_NOOP,      
	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      
	CPU6502_INC_ZP,    	CPU6502_NOOP,      	CPU6502_INX_IMPL,  	CPU6502_NOOP,      	CPU6502_NOOP,      
	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_INC_ABS,   	CPU6502_NOOP,      
	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      
	CPU6502_NOOP,      	CPU6502_INC_ZPX,   	CPU6502_NOOP,      	CPU6502_SED_IMPL,  	CPU6502_NOOP,      
	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_NOOP,      	CPU6502_INC_ABSX,  
};
// Code generator placeholder end

bool FetchCommand(U32& Cycles, const BYTE OpCode, Memory &Memory, CPU6502 &CPU) {
    const auto &Instruction = Ops[OpCode];
    Instruction(Cycles, Memory, CPU);
    return Instruction != CPU6502_NOOP;
}
