#pragma once
#include "I8086/I8086.h"

template<typename T>
FORCE_INLINE T GenericOR(const T value1, const T value2) {
    return value1 | value2;
}

//  Mem8 <-- Mem8 OR Reg8
FORCE_INLINE void I8086_OR_Eb_Gb(BYTE OpCode, Memory &memory, I8086 &cpu) {
    const InstructionData instructionData = cpu.GetInstructionData(memory, OperandSize::BYTE, OperandsOrder::Mem_Reg);

    const BYTE mem8 =  cpu.Read<BYTE>(memory, instructionData.leftOp.mem);
    BYTE opRes = GenericOR(mem8, *instructionData.rightOp.reg8);
    cpu.Write<BYTE>(memory, instructionData.leftOp.mem, opRes);
}

//  Mem16 <-- Mem16 OR Reg16
FORCE_INLINE void I8086_OR_Ev_Gv(BYTE OpCode, Memory &memory, I8086 &cpu) {
    const InstructionData instructionData = cpu.GetInstructionData(memory, OperandSize::WORD, OperandsOrder::Mem_Reg);

    const WORD mem16 = cpu.Read<WORD>(memory, instructionData.leftOp.mem);
    WORD opRes = GenericOR(mem16, *instructionData.rightOp.reg16);
    cpu.Write<WORD>(memory, instructionData.leftOp.mem, opRes);
}

//  Reg8 <-- Reg8 OR Reg8
//  Reg8 <-- Reg8 OR Mem8
FORCE_INLINE void I8086_OR_Gb_Eb(BYTE OpCode, Memory &memory, I8086 &cpu) {
    const InstructionData instructionData = cpu.GetInstructionData(memory, OperandSize::BYTE, OperandsOrder::Reg_MemReg);

    const BYTE operand = instructionData.rightOp.type == OperandType::Reg8 ?
                         *instructionData.rightOp.reg8 :
                         cpu.Read<BYTE>(memory, instructionData.rightOp.mem);
    BYTE opRes = GenericOR(*instructionData.leftOp.reg8, operand);
    *instructionData.leftOp.reg8 = opRes;
}

//  Reg16 <-- Reg16 OR Reg16
//  Reg16 <-- Reg16 OR Mem16
FORCE_INLINE void I8086_OR_Gv_Ev(BYTE OpCode, Memory &memory, I8086 &cpu) {
    const InstructionData instructionData = cpu.GetInstructionData(memory, OperandSize::WORD, OperandsOrder::Reg_MemReg);

    const WORD operand = instructionData.rightOp.type == OperandType::Reg16 ?
                         *instructionData.rightOp.reg16 :
                         cpu.Read<WORD>(memory, instructionData.rightOp.mem);
    BYTE opRes = GenericOR(*instructionData.leftOp.reg16, operand);
    *instructionData.leftOp.reg16 = opRes;
}

//  AL <-- AL OR Immed8
FORCE_INLINE void I8086_OR_AL_Ib(BYTE OpCode, Memory &memory, I8086 &cpu) {
    const BYTE value = cpu.Fetch<BYTE>(memory);
    cpu.AL = GenericOR(cpu.AL, value);
}

//  AX <-- AX OR Immed16
FORCE_INLINE void I8086_OR_AX_Iv(BYTE OpCode, Memory &memory, I8086 &cpu) {
    const WORD value = cpu.Fetch<WORD>(memory);
    cpu.AX = GenericOR(cpu.AX, value);
}
