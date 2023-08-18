#include "Operations/CPU6502_LDA_Op.h"
#include <CPU6502_OpHelpers.h>
#include "CPU6502.h"
#include "Memory.h"
#include "map"
#include "functional"


struct CPU6502_JSR_ABS{
    void operator()(Memory &memory, CPU6502 &cpu){
        std::printf("JSR_ABS\n");
        WORD JumpAddress = cpu.FetchWord(memory);
        cpu.WriteWord(cpu.PC - 1, cpu.SP, memory);
        cpu.PC = JumpAddress;
        std::printf("Jumping to 0x%x\n", cpu.PC);
    }
};

const static std::map<BYTE, std::function<void(Memory &, CPU6502 &)>> CPU6502_OpCodesMap{
        { CPU6502_OpCodes::LDA_IM,  CPU6502_LDA_IM{}  },
        { CPU6502_OpCodes::LDA_ZP,  CPU6502_LDA_ZP{}  },
        { CPU6502_OpCodes::LDA_ZPX, CPU6502_LDA_ZPX{} },
        { CPU6502_OpCodes::JSR_ABS, CPU6502_JSR_ABS{} },
};

unsigned char FetchCommand(BYTE OpCode, Memory &Memory, CPU6502 &CPU) {
    std::printf("------------------------------------------\n");
    const auto FuncIter = CPU6502_OpCodesMap.find(OpCode);
    if (FuncIter == CPU6502_OpCodesMap.end())
    {
        std::printf("Can't handle instruction; Abort execution\n");
        return 0;
    }

    std::printf("Operation: ");
    FuncIter->second(Memory, CPU);
    return 1;
}