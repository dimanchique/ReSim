#pragma once

#include "core/types.h"
#include "I8086_Addressing.h"

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

enum OperandArchetype : BYTE {
    Mem, Reg, SReg
};

enum class InstructionType {
    SingleOp, DoubleOp
};


struct OperandConstructor {
    OperandArchetype archetype{};

    union {
        BYTE regData;

        struct {
            BYTE dispSize;
            WORD dispValue;
            AddressMode mode;
        } memData;
    };
};


// For testing purposes only
// Construct MOD|REG|R/M byte
struct ModRegByteConstructor {
    OperandSize size = OperandSize::BYTE;
    InstructionType type = InstructionType::DoubleOp;

    OperandConstructor leftOp;
    OperandConstructor rightOp;
    //TODO: Add 'singleOp' field for single operand instructions

    BYTE MakeModByte() {
        ModRegByte modByte{};

        // MOD field filling
        // MOD = 0b11 only if both operands are registers
        // MOD field contains displacement size otherwise
        bool isRegRegOp = (leftOp.archetype & rightOp.archetype) >= OperandArchetype::Reg;

        if (isRegRegOp)
            modByte.mod = 0b11;
        else {
            modByte.mod = leftOp.archetype == OperandArchetype::Mem ?
                          leftOp.memData.dispSize :
                          rightOp.memData.dispSize;
        }

        // REG field filling
        // cast regData to byte is legal, enum values are mapped to REG field values
        if (isRegRegOp) {
            modByte.reg = (BYTE) leftOp.regData;
        }
        else {
            modByte.reg = leftOp.archetype > OperandArchetype::Mem ?
                          (BYTE) leftOp.regData :
                          (BYTE) rightOp.regData;
        }

        // R/M field filling
        // if operand is reg just cast to byte as above section
        if (isRegRegOp) {
            modByte.rm = rightOp.regData;
        }
        else {
            OperandConstructor* opPtr = leftOp.archetype == OperandArchetype::Mem ?
                    &leftOp :
                    &rightOp;

            // if operand is Mem we need a "hack"
            // Direct mode and BP indexed mode both have the same value (0b110) so cast doesn't work in this case
            if ((*opPtr).memData.mode == modeDirect)
                modByte.rm = (BYTE) modeBP;
            else
                modByte.rm = (BYTE) (*opPtr).memData.mode;
        }

        return modByte.value;
    }
};
