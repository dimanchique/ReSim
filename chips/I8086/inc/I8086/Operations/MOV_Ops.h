#pragma once

#include "I8086/I8086.h"
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

//  Mem8 <-- Mem8 MOV Reg8
void I8086_MOV_Eb_Gb(BYTE OpCode, I8086 &cpu) {
I8086_EGx_EGx_MOV<BYTE>(cpu);
}

//  Mem16 <-- Mem16 MOV Reg16
void I8086_MOV_Ev_Gv(BYTE OpCode, I8086 &cpu) {
I8086_EGx_EGx_MOV<WORD>(cpu);
}

//  Reg8 <-- Reg8 MOV Reg8
//  Reg8 <-- Reg8 MOV Mem8
void I8086_MOV_Gb_Eb(BYTE OpCode, I8086 &cpu) {
I8086_EGx_EGx_MOV<BYTE>(cpu);
}

//  Reg16 <-- Reg16 MOV Reg16
//  Reg16 <-- Reg16 MOV Mem16
void I8086_MOV_Gv_Ev(BYTE OpCode, I8086 &cpu) {
I8086_EGx_EGx_MOV<WORD>(cpu);
}
