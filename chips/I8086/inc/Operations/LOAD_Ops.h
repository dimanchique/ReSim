#pragma once

#include "I8086.h"

void I8086_LEA_Gv_M(BYTE, I8086& cpu) {
    const InstructionData instructionData = cpu.GetInstructionData<WORD>(OperandSize::WORD, InstructionDirection::Reg_MemReg);
    DWORD effectiveAddress = instructionData.rightOp.operand.mem;
    WORD offsetAddress = effectiveAddress - (*cpu.currentSegment << 4);
    instructionData.leftOp.set(cpu, offsetAddress);
}

void I8086_LES_Gv_Mp(BYTE, I8086& cpu) {
    const InstructionData instructionData = cpu.GetInstructionData<WORD>(OperandSize::WORD, InstructionDirection::Reg_MemReg);
    DWORD effectiveAddress = instructionData.rightOp.operand.mem;
    instructionData.leftOp.set(cpu, (effectiveAddress >> 16) & 0xFFFF);
    cpu.ES = effectiveAddress & 0xFFFF;
}

void I8086_LDS_Gv_Mp(BYTE, I8086& cpu) {
    const InstructionData instructionData = cpu.GetInstructionData<WORD>(OperandSize::WORD, InstructionDirection::Reg_MemReg);
    DWORD effectiveAddress = instructionData.rightOp.operand.mem;
    instructionData.leftOp.set(cpu, (effectiveAddress >> 16) & 0xFFFF);
    cpu.DS = effectiveAddress & 0xFFFF;
}
