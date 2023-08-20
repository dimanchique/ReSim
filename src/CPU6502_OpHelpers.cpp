#include <Operations/CPU6502_LDA_Op.h>
#include <Operations/CPU6502_LDX_Op.h>
#include <Operations/CPU6502_LDY_Op.h>
#include <CPU6502_OpHelpers.h>
#include <CPU6502.h>
#include <Memory.h>
#include <functional>

void CPU6502_NOOP(S32& Cycles, Memory &memory, CPU6502 &cpu){

}
void CPU6502_JSR_ABS(S32& Cycles, Memory &memory, CPU6502 &cpu){
    WORD JumpAddress = cpu.FetchWord(Cycles, memory);
    cpu.WriteWord(Cycles, cpu.PC - 1, cpu.SP, memory);
    cpu.PC = JumpAddress;
    cpu.SP += 2;
    Cycles--;
}

using OpSignature = std::function<void(S32&, Memory&, CPU6502&)>;
using OpSig = void (*)(S32 &,Memory &,CPU6502 &);

OpSig s[255] = {};

const static OpSig Ops[] = {
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_JSR_ABS,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_LDY_IM,
        CPU6502_LDA_INDX,
        CPU6502_LDX_IM,
        CPU6502_NOOP,
        CPU6502_LDY_ZP,
        CPU6502_LDA_ZP,
        CPU6502_LDX_ZP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_LDA_IM,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_LDY_ABS,
        CPU6502_LDA_ABS,
        CPU6502_LDX_ABS,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_LDA_INDY,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_LDY_ZPX,
        CPU6502_LDA_ZPX,
        CPU6502_LDX_ZPY,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_LDA_ABSY,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_LDY_ABSX,
        CPU6502_LDA_ABSX,
        CPU6502_LDX_ABSY,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP,
        CPU6502_NOOP
};

unsigned char FetchCommand(S32& Cycles, BYTE OpCode, Memory &Memory, CPU6502 &CPU) {
    Ops[OpCode](Cycles, Memory, CPU);
    return 1;
}