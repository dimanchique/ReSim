#pragma once

#include "core/types.h"
#include "core/compilers_macro.h"

class I8086;
struct Memory;

class InvalidInstruction : public std::invalid_argument {
public:
    InvalidInstruction() : std::invalid_argument("Invalid instruction encountered") {}
};

template<typename T>
using OperandSetter = void (*)(I8086 &, const void *, T);

template<typename T>
using OperandGetter = T(*)(I8086 &, const void *);

struct ModRegByte {
    union {
        struct {
            BYTE rm: 3;
            BYTE reg: 3;
            BYTE mod: 2;
        };
        BYTE value = 0;
    };

    FORCE_INLINE static ModRegByte FromByte(const BYTE value) {
        ModRegByte modReg;
        modReg.value = value;
        return modReg;
    }
};

enum class InstructionDirection {
    MemReg_Reg, Reg_MemReg, MemReg_Imm
};

enum OperandDirection {
    LeftToRight = 1, RightToLeft, Bidirectional
};

enum class OperandType {
    Reg, Mem
};

template<typename T>
struct OperandInfo {
    OperandType type;
    union {
        void *reg = nullptr;
        DWORD mem;
    } operand;

    OperandGetter<T> get;
    OperandSetter<T> set;
};

template<typename T>
struct InstructionData {
    union {
        struct {
            OperandInfo<T> leftOp;
            OperandInfo<T> rightOp;
        };                          // Regular instruction operands
        OperandInfo<T> singleOp;    // GRP instructions operand
    };
};

template<typename T>
struct OperandValue{
    T before;
    T after;
};

template<typename T>
struct InstructionResult{
    OperandValue<T> leftOp;
    OperandValue<T> rightOp;
};
