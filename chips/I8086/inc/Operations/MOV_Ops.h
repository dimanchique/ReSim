#pragma once

#include "I8086.h"
#include "Adressing.h"

template<typename T>
void PerformMOV(InstructionResult<T>& result) {
    result.leftOp.after = result.rightOp.before;
    result.rightOp.after = result.leftOp.before;
}

template<typename T>
void UpdateStatusAfterMOV(I8086 &cpu, const T &value){
    cpu.Status.C = 0;
    cpu.Status.O = 0;
    cpu.Status.UpdateStatusByValue(value, I8086_Status_S | I8086_Status_Z | I8086_Status_P);
}

template<typename T>
void UpdateStatusAfterMOV_Wrapper(I8086 &cpu, const InstructionResult<T> &instructionResult) {
    UpdateStatusAfterMOV(cpu, instructionResult.leftOp.after);
}

template<typename T>
void I8086_EGx_EGx_MOV(I8086 &cpu) {
    I8086_EGx_EGx<T>(cpu, &PerformMOV, &UpdateStatusAfterMOV_Wrapper, InstructionDirection::MemReg_Reg, RightToLeft);
}

//  Mem8 <-- Reg8
void I8086_MOV_Eb_Gb(BYTE OpCode, I8086 &cpu) {
    I8086_EGx_EGx_MOV<BYTE>(cpu);
}

//  Mem16 <-- Reg16
void I8086_MOV_Ev_Gv(BYTE OpCode, I8086 &cpu) {
    I8086_EGx_EGx_MOV<WORD>(cpu);
}

//  Reg8 <-- Reg8/Mem8
void I8086_MOV_Gb_Eb(BYTE OpCode, I8086 &cpu) {
    I8086_EGx_EGx_MOV<BYTE>(cpu);
}

//  Reg16 <-- Reg16/Mem16
void I8086_MOV_Gv_Ev(BYTE OpCode, I8086 &cpu) {
    I8086_EGx_EGx_MOV<WORD>(cpu);
}

//  SReg16 <-- Mem16
void I8086_MOV_Sw_Ew(BYTE OpCode, I8086 &cpu) {
    const BYTE modByte = cpu.Fetch<BYTE>();
    const ModRegByte modReg = ModRegByte::FromByte(modByte);
    const InstructionData instructionData = cpu.GetInstructionDataNoFetch<WORD>(OperandSize::WORD, InstructionDirection::Reg_MemReg, modReg);
    WORD* sRegPtr = cpu.GetSRegWordPtr(modReg.reg);
    *sRegPtr = instructionData.rightOp.get(cpu, &instructionData.rightOp.operand);
}

//  Mem16 <-- SReg16
void I8086_MOV_Ew_Sw(BYTE OpCode, I8086 &cpu) {
    const BYTE modByte = cpu.Fetch<BYTE>();
    const ModRegByte modReg = ModRegByte::FromByte(modByte);
    const InstructionData instructionData = cpu.GetInstructionDataNoFetch<WORD>(OperandSize::WORD, InstructionDirection::MemReg_Reg, modReg);
    WORD* sRegPtr = cpu.GetSRegWordPtr(modReg.reg);
    instructionData.leftOp.set(cpu, &instructionData.leftOp.operand, *sRegPtr);
}
