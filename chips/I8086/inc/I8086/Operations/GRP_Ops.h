#pragma once
#include "I8086/I8086.h"
#include "OR_Ops.h"

void I8086_GRP1_Eb_Ib(BYTE OpCode, Memory &memory, I8086 &cpu) {
    const BYTE modByte = cpu.Fetch<BYTE>(memory);
    const ModRegByte modReg = ModRegByte(modByte);
    switch (modReg.reg) {
        case 0b000:
            return; // ADD
        case 0b001:
            I8086_OR_Eb_Ib(memory, cpu, modReg);
        case 0b010:
            return; // ADC
        case 0b011:
            return; // SBB
        case 0b100:
            return; // AND
        case 0b101:
            return; // SUB
        case 0b110:
            return; // XOR
        case 0b111:
            return; // CMP
    }
}

void I8086_GRP1_Ev_Iv(BYTE OpCode, Memory &memory, I8086 &cpu) {
    const BYTE modByte = cpu.Fetch<BYTE>(memory);
    const ModRegByte modReg = ModRegByte(modByte);
    switch (modReg.reg) {
        case 0b000:
            return; // ADD
        case 0b001:
            I8086_OR_Ev_Iv(memory, cpu, modReg);
        case 0b010:
            return; // ADC
        case 0b011:
            return; // SBB
        case 0b100:
            return; // AND
        case 0b101:
            return; // SUB
        case 0b110:
            return; // XOR
        case 0b111:
            return; // CMP
    }
}
