#pragma once
#include "I8086/I8086.h"

template<typename T>
FORCE_INLINE T GenericOR(const T value1, const T value2) {
    return value1 | value2;
}

//  Generic handler for Ex,Gx instructions: MemX/RegX <-- MemX/RegX OR RegX
//  But in this case (0x08/0x09) it's always MemX <-- MemX OR RegX
template<typename T>
void I8086_OR_Ex_Gx(Memory &memory, I8086 &cpu) {
    const OperandSize opSize = std::is_same_v<T, BYTE> ? OperandSize::BYTE : OperandSize::WORD;
    const InstructionData instructionData = cpu.GetInstructionData(memory, opSize, InstructionDirection::Mem_Reg);

    const T memValue = cpu.Read<T>(memory, instructionData.doubleOps.leftOp.mem);
    const T opRes = GenericOR(memValue, *(T *) instructionData.doubleOps.rightOp.reg);
    cpu.Write<T>(memory, instructionData.doubleOps.leftOp.mem, opRes);
}

//  Generic handler for Gx,Ex instructions: RegX <-- RegX OR RegX/MemX
//  RightOp can be both Reg or Mem, while LeftOp is always Reg
template<typename T>
void I8086_OR_Gx_Ex(Memory &memory, I8086 &cpu) {
    const OperandSize opSize = std::is_same_v<T, BYTE> ? OperandSize::BYTE : OperandSize::WORD;
    const InstructionData instructionData = cpu.GetInstructionData(memory, opSize, InstructionDirection::Reg_MemReg);

    const T operand = instructionData.doubleOps.rightOp.type == OperandType::Reg ?
                      *(T *) instructionData.doubleOps.rightOp.reg :
                      cpu.Read<T>(memory, instructionData.doubleOps.rightOp.mem);
    const T opRes = GenericOR(*(T *) instructionData.doubleOps.leftOp.reg, operand);
    *(T *) instructionData.doubleOps.leftOp.reg = opRes;
}

//  Generic handler for Ex,Ix instructions: RegX/MemX <-- RegX/MemX OR ImmediateX
//  LeftOp can be both Reg or Mem, while RightOp is always Immediate value
template<typename T>
void I8086_OR_Ex_Ix(Memory &memory, I8086 &cpu, const ModRegByte modRegByte) {
    const OperandSize opSize = std::is_same_v<T, BYTE> ? OperandSize::BYTE : OperandSize::WORD;
    const InstructionData instructionData = cpu.GetInstructionData(memory, opSize, InstructionDirection::MemReg_Imm);

    const bool isRegDstOp = modRegByte.mod == 0b11;

    const T immValue = cpu.Fetch<T>(memory);
    const T operandValue = isRegDstOp ?
                           *(T *) instructionData.singleOp.reg :
                           cpu.Read<T>(memory, instructionData.singleOp.mem);
    const T opRes = GenericOR(operandValue, immValue);

    if (isRegDstOp)
        *(T *) instructionData.singleOp.reg = opRes;
    else
        cpu.Write<T>(memory, instructionData.singleOp.mem, opRes);
}

//  Mem8 <-- Mem8 OR Reg8
FORCE_INLINE void I8086_OR_Eb_Gb(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_OR_Ex_Gx<BYTE>(memory, cpu);
}

//  Mem16 <-- Mem16 OR Reg16
FORCE_INLINE void I8086_OR_Ev_Gv(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_OR_Ex_Gx<WORD>(memory, cpu);
}

//  Reg8 <-- Reg8 OR Reg8
//  Reg8 <-- Reg8 OR Mem8
FORCE_INLINE void I8086_OR_Gb_Eb(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_OR_Gx_Ex<BYTE>(memory, cpu);
}

//  Reg16 <-- Reg16 OR Reg16
//  Reg16 <-- Reg16 OR Mem16
FORCE_INLINE void I8086_OR_Gv_Ev(BYTE OpCode, Memory &memory, I8086 &cpu) {
    I8086_OR_Gx_Ex<WORD>(memory, cpu);
}

//  AL <-- AL OR Immediate8
FORCE_INLINE void I8086_OR_AL_Ib(BYTE OpCode, Memory &memory, I8086 &cpu) {
    const BYTE value = cpu.Fetch<BYTE>(memory);
    cpu.AL = GenericOR(cpu.AL, value);
}

//  AX <-- AX OR Immediate16
FORCE_INLINE void I8086_OR_AX_Iv(BYTE OpCode, Memory &memory, I8086 &cpu) {
    const WORD value = cpu.Fetch<WORD>(memory);
    cpu.AX = GenericOR(cpu.AX, value);
}

//  Reg8 <-- Reg8 OR Immediate8
//  Mem8 <-- Mem8 OR Immediate8
FORCE_INLINE void I8086_OR_Eb_Ib(Memory &memory, I8086 &cpu, const ModRegByte modRegByte) {
    I8086_OR_Ex_Ix<BYTE>(memory, cpu, modRegByte);
}

//  Reg16 <-- Reg16 OR Immediate16
//  Mem16 <-- Mem16 OR Immediate16
FORCE_INLINE void I8086_OR_Ev_Iv(Memory &memory, I8086 &cpu, const ModRegByte modRegByte) {
    I8086_OR_Ex_Ix<WORD>(memory, cpu, modRegByte);
}
