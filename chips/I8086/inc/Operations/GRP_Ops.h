#pragma once

#include "I8086.h"
#include "OR_Ops.h"
#include "AND_Ops.h"
#include "XOR_Ops.h"
#include "ROR_RCR_SAR_SHR_Ops.h"
#include "ROL_RCL_SAL_SHL_Ops.h"
#include "NOT_NEG_Ops.h"
#include "INC_DEC_Ops.h"
#include "PUSH_POP_Ops.h"
#include "TEST_Ops.h"
#include "CALL_Ops.h"
#include "JMP_Ops.h"

template<typename T>
using GRP_CallbackSignature = void (*)(I8086&, const ModRegByte&);

template<typename T>
void GRP_InvalidCall(I8086&, const ModRegByte&) {
    throw InvalidInstruction();
}

template<typename T>
FORCE_INLINE void I8086_GRP1_Ex_Ix(I8086 &cpu) {
    const BYTE modByte = cpu.Fetch<BYTE>();
    const ModRegByte modReg = ModRegByte::FromByte(modByte);

    static constexpr GRP_CallbackSignature<T> callMap[] = {
            &I8086_ADD_Ex_Ix<T>,    // 000 -> ADD
            &I8086_OR_Ex_Ix<T>,     // 001 -> OR
            &GRP_InvalidCall<T>,    // 010 -> ADC
            &GRP_InvalidCall<T>,    // 011 -> SBB
            &I8086_AND_Ex_Ix<T>,    // 100 -> AND
            &GRP_InvalidCall<T>,    // 101 -> SUB
            &I8086_XOR_Ex_Ix<T>,    // 110 -> XOR
            &GRP_InvalidCall<T>     // 111 -> CMP
    };

    callMap[modReg.reg](cpu, modReg);
}

void I8086_GRP1_Eb_Ib(BYTE, I8086 &cpu) {
    I8086_GRP1_Ex_Ix<BYTE>(cpu);
}

void I8086_GRP1_Ev_Iv(BYTE, I8086 &cpu) {
    I8086_GRP1_Ex_Ix<WORD>(cpu);
}

template<typename T>
FORCE_INLINE void I8086_GRP2_Ex_1(I8086 &cpu) {
    const BYTE modByte = cpu.Fetch<BYTE>();
    const ModRegByte modReg = ModRegByte::FromByte(modByte);

    static constexpr GRP_CallbackSignature<T> callMap[] = {
            &ROL_ByOne<T>,          // 000 -> ROL
            &ROR_ByOne<T>,          // 001 -> ROR
            &RCL_ByOne<T>,          // 010 -> RCL
            &RCR_ByOne<T>,          // 011 -> RCR
            &SAL_SHL_ByOne<T>,      // 100 -> SAL/SHL
            &SHR_ByOne<T>,          // 101 -> SHR
            &GRP_InvalidCall<T>,    // 110 -> INVALID
            &SAR_ByOne<T>           // 111 -> SAR
    };

    callMap[modReg.reg](cpu, modReg);
}

void I8086_GRP2_Eb_1(BYTE, I8086 &cpu) {
    I8086_GRP2_Ex_1<BYTE>(cpu);
}

void I8086_GRP2_Ev_1(BYTE, I8086 &cpu) {
    I8086_GRP2_Ex_1<WORD>(cpu);
}

template<typename T>
FORCE_INLINE void I8086_GRP2_Ex_CL(I8086 &cpu) {
    const BYTE modByte = cpu.Fetch<BYTE>();
    const ModRegByte modReg = ModRegByte::FromByte(modByte);

    static constexpr GRP_CallbackSignature<T> callMap[] = {
            &ROL_ByCL<T>,           // 000 -> ROL
            &ROR_ByCL<T>,           // 001 -> ROR
            &RCL_ByCL<T>,           // 010 -> RCL
            &RCR_ByCL<T>,           // 011 -> RCR
            &SAL_SHL_ByCL<T>,       // 100 -> SAL/SHL
            &SHR_ByCL<T>,           // 101 -> SHR
            &GRP_InvalidCall<T>,    // 110 -> INVALID
            &SAR_ByCL<T>            // 111 -> SAR
    };

    callMap[modReg.reg](cpu, modReg);
}

void I8086_GRP2_Eb_CL(BYTE, I8086 &cpu) {
    I8086_GRP2_Ex_CL<BYTE>(cpu);
}

void I8086_GRP2_Ev_CL(BYTE, I8086 &cpu) {
    I8086_GRP2_Ex_CL<WORD>(cpu);
}

template<typename T>
FORCE_INLINE void I8086_GRP3x_Ex(I8086 &cpu) {
    const BYTE modByte = cpu.Fetch<BYTE>();
    const ModRegByte modReg = ModRegByte::FromByte(modByte);

    static constexpr GRP_CallbackSignature<T> callMap[] = {
            &I8086_TEST_Ex_Ix<T>,            // 000 -> TEST
            &GRP_InvalidCall<T>,            // 001 -> INVALID
            &I8086_NOT<T>,                  // 010 -> NOT
            &I8086_NEG<T>,                  // 011 -> NEG
            &GRP_InvalidCall<T>,            // 100 -> MUL
            &GRP_InvalidCall<T>,            // 101 -> IMUL
            &GRP_InvalidCall<T>,            // 110 -> DIV
            &GRP_InvalidCall<T>             // 111 -> IDIV
    };

    callMap[modReg.reg](cpu, modReg);
}

void I8086_GRP3a_Eb(BYTE, I8086 &cpu) {
    I8086_GRP3x_Ex<BYTE>(cpu);
}

void I8086_GRP3b_Ev(BYTE, I8086 &cpu) {
    I8086_GRP3x_Ex<WORD>(cpu);
}

FORCE_INLINE void I8086_GRP4_Eb(I8086 &cpu) {
    const BYTE modByte = cpu.Fetch<BYTE>();
    const ModRegByte modReg = ModRegByte::FromByte(modByte);

    static constexpr GRP_CallbackSignature<BYTE> callMap[] = {
        &INC_GRP4_Eb,               // 000 -> INC
        &DEC_GRP4_Eb,               // 001 -> DEC
        &GRP_InvalidCall<BYTE>,     // 010 -> INVALID
        &GRP_InvalidCall<BYTE>,     // 011 -> INVALID
        &GRP_InvalidCall<BYTE>,     // 100 -> INVALID
        &GRP_InvalidCall<BYTE>,     // 101 -> INVALID
        &GRP_InvalidCall<BYTE>,     // 110 -> INVALID
        &GRP_InvalidCall<BYTE>,     // 111 -> INVALID
};

    callMap[modReg.reg](cpu, modReg);
}

void I8086_GRP4_Eb(BYTE, I8086 &cpu) {
    I8086_GRP4_Eb(cpu);
}

FORCE_INLINE void I8086_GRP5_Ev(I8086 &cpu) {
    const BYTE modByte = cpu.Fetch<BYTE>();
    const ModRegByte modReg = ModRegByte::FromByte(modByte);

    static constexpr GRP_CallbackSignature<WORD> callMap[] = {
        &INC_GRP5_Ev,               // 000 -> INC
        &DEC_GRP5_Ev,               // 001 -> DEC
        &CALL_GRP5,                 // 010 -> CALL
        &CALL_GRP5_MP,              // 011 -> CALL Mp
        &JMP_GRP5,                  // 100 -> JMP
        &JMP_GRP5_MP,               // 101 -> JMP Mp
        &PUSH_Ev,                   // 110 -> PUSH
        &GRP_InvalidCall<WORD>,     // 111 -> INVALID
};

    callMap[modReg.reg](cpu, modReg);
}

void I8086_GRP5_Ev(BYTE, I8086 &cpu) {
    I8086_GRP5_Ev(cpu);
}
