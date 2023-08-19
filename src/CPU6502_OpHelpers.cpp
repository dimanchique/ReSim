#include "Operations/CPU6502_LDA_Op.h"
#include <CPU6502_OpHelpers.h>
#include "CPU6502.h"
#include "Memory.h"
#include "map"
#include "functional"


struct CPU6502_JSR_ABS{
    void operator()(S32& Cycles, Memory &memory, CPU6502 &cpu){
        WORD JumpAddress = cpu.FetchWord(Cycles, memory);
        cpu.WriteWord(Cycles, cpu.PC - 1, cpu.SP, memory);
        cpu.PC = JumpAddress;
        cpu.SP += 2;
        Cycles--;
    }
};

const static std::map<BYTE, std::function<void(S32&, Memory &, CPU6502 &)>> CPU6502_OpCodesMap{
    //LDA
        { CPU6502_OpCodes::LDA_IM,  CPU6502_LDA_IM{}        },
        { CPU6502_OpCodes::LDA_ZP,  CPU6502_LDA_ZP{}        },
        { CPU6502_OpCodes::LDA_ZPX, CPU6502_LDA_ZPX{}       },
        { CPU6502_OpCodes::LDA_ABS, CPU6502_LDA_ABS{}       },
        { CPU6502_OpCodes::LDA_ABSX, CPU6502_LDA_ABSX{}     },
        { CPU6502_OpCodes::LDA_ABSY, CPU6502_LDA_ABSY{}     },
        { CPU6502_OpCodes::LDA_INDX, CPU6502_LDA_INDX{}     },
        { CPU6502_OpCodes::LDA_INDY, CPU6502_LDA_INDY{}     },

        { CPU6502_OpCodes::JSR_ABS, CPU6502_JSR_ABS{} },
};

unsigned char FetchCommand(S32& Cycles, BYTE OpCode, Memory &Memory, CPU6502 &CPU) {
    const auto FuncIter = CPU6502_OpCodesMap.find(OpCode);
    if (FuncIter == CPU6502_OpCodesMap.end())
        return 0;
    FuncIter->second(Cycles, Memory, CPU);
    return 1;
}