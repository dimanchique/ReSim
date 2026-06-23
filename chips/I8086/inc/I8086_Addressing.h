#pragma once

#include "memory.h"
#include "core/types.h"
#include "core/compilers_macro.h"

class I8086;

class InvalidInstruction : public std::invalid_argument {
public:
    InvalidInstruction() : std::invalid_argument("Invalid instruction encountered") {}
};

template<typename T>
using OperandSetter = void (*)(I8086 &, const void *, T);

template<typename T>
using OperandGetter = T(*)(I8086 &, const void *);

struct ModRegByte {
    explicit ModRegByte(BYTE inValue = 0) : value(inValue) {}

    union {
        struct {
            BYTE rm: 3;
            BYTE reg: 3;
            BYTE mod: 2;
        };
        BYTE value = 0;
    };
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

    void set(I8086& cpu, T value) const {
        setterFuncPtr(cpu, type == OperandType::Reg ? operand.reg : &operand.mem, value);
    }

    T get(I8086& cpu) const {
        return getterFuncPtr(cpu, type == OperandType::Reg ? operand.reg : &operand.mem);
    }

    void getterSet(OperandGetter<T> f) {
        getterFuncPtr = f;
    }

    void setterSet(OperandSetter<T> f) {
        setterFuncPtr = f;
    }

private:
    OperandGetter<T> getterFuncPtr;
    OperandSetter<T> setterFuncPtr;
};

template<typename T>
struct InstructionData {
    OperandInfo<T> leftOp;
    OperandInfo<T> rightOp;
};

template<typename T>
struct InstructionResult{
    struct {
        T before;
        T after;
    } leftOp;

    struct {
        T before;
        T after;
    } rightOp;

    struct {
        bool C; // Carry
        bool A; // Auxiliary
        bool O; // Overflow
    } status;
};
