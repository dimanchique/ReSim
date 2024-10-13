#pragma once

#include "core/types.h"

struct ModRegByte {

    explicit ModRegByte(BYTE value = 0) : value(value) {}

    union {
        struct {
            BYTE rm: 3;
            BYTE reg: 3;
            BYTE mod: 2;
        };
        BYTE value = 0;
    };
};

// Direction
enum class InstructionDirection {
    Mem_Reg, Reg_MemReg, MemReg_Imm
};

enum class OperandType {
    Reg, Mem
};

struct OperandInfo {
    OperandType type;

    union {
        void *reg = nullptr;
        DWORD mem;
    };
};

struct InstructionData {
    union{
        struct{
            OperandInfo leftOp;
            OperandInfo rightOp;
        } doubleOps;
        OperandInfo singleOp; // case for GRP instructions
    };
};

enum ByteRegisters : BYTE {
    bAL, bCL, bDL, bBL, bAH, bCH, bDH, bBH
};

enum WordRegisters : BYTE {
    wAX, wCX, wDX, wBX, wSP, wBP, wSI, wDI
};

enum sWordRegisters : BYTE {
    swES, swCS, swSS, swDS
};

enum AddressMode : BYTE {
    modeBXpSI, modeBXpDI, modeBPpSI, modeBPpDI, modeSI, modeDI, modeBP, modeBX, modeDirect
};

enum class OperandArchetype {
    Reg, Mem
};

struct OperandConstructor {
    OperandArchetype archetype{};

    union {
        struct {
            union{
                ByteRegisters byteReg;
                WordRegisters wordReg;
                sWordRegisters swordReg;
            };
        } regData{};

        struct {
            BYTE dispSize = 0;
            WORD dispValue = 0;
            AddressMode mode;
        } memData;
    };
};

// For testing purposes only
// Construct MOD|REG|R/M byte
struct ModRegByteConstructor {
    OperandSize size = OperandSize::BYTE;

    OperandConstructor leftOp;
    OperandConstructor rightOp;

    BYTE MakeModByte() {
        ModRegByte modByte{};

        // MOD field filling
        // MOD = 0b11 only if both operands are registers
        // MOD field contains displacement size otherwise
        if (leftOp.archetype == OperandArchetype::Reg && rightOp.archetype == OperandArchetype::Reg)
            modByte.mod = 0b11;
        else{
            modByte.mod = leftOp.archetype == OperandArchetype::Mem ?
                          leftOp.memData.dispSize :
                          rightOp.memData.dispSize;
        }

        // REG field filling
        // cast regData to byte is legal, enum values are sorted
        modByte.reg = size == OperandSize::BYTE ?
                      (BYTE)rightOp.regData.byteReg :
                      (BYTE)rightOp.regData.wordReg;

        // R/M field filling
        // if leftOp is reg just cast to byte as above section
        if (leftOp.archetype == OperandArchetype::Reg)
        {
            modByte.rm = size == OperandSize::BYTE ?
                         (BYTE)leftOp.regData.byteReg :
                         (BYTE)leftOp.regData.wordReg;
        }
        // if leftOp is mem we need a "hack"
        else
        {
            // Direct mode and BP indexed mode both have the same value (0b110) but cast doesn't work in this case
            if (leftOp.memData.mode == modeDirect)
                modByte.rm = (BYTE)modeBP;
            else
                modByte.rm = (BYTE)leftOp.memData.mode;
        }

        return modByte.value;
    }
};
