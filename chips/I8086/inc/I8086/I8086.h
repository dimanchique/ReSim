#pragma once

#include "I8086_Status.h"
#include "I8086_OpCodes.h"
#include "core/macro.h"
#include "base/compute.h"
#include "base/memory.h"
#include "I8086_Addressing.h"
#include <type_traits>
#include <cassert>

#define STOP_OPCODE I8086_OpCodes::HLT // HLT instruction is pretty OK to use as a STOP opcode

#define EFFECTIVE_ADDRESS(m, n) (m + (n << 4))

class I8086 final : public Compute {
public:

    DECLARE_PAIRED_REG_UNIQUE_NAME(BYTE, WORD, AH, AL, AX); // primary accumulator
    DECLARE_PAIRED_REG_UNIQUE_NAME(BYTE, WORD, BH, BL, BX); // base, accumulator
    DECLARE_PAIRED_REG_UNIQUE_NAME(BYTE, WORD, CH, CL, CX); // counter, accumulator
    DECLARE_PAIRED_REG_UNIQUE_NAME(BYTE, WORD, DH, DL, DX); // accumulator, other functions

    WORD SI;    // Source Index
    WORD DI;    // Destination Index

    WORD BP;    // Base Pointer
    WORD SP;    // Stack Pointer

    I8086_Status Status;

    WORD CS;    // Code Segment
    WORD DS;    // Data Segment
    WORD ES;    // Extra Segment
    WORD SS;    // Stack Segment

    WORD PC;    // Program Counter

    // As far as segment is overriding only by specific instructions we can store default segment DS here as a pointer
    WORD *currentSegment = &DS;

    void Reset(Memory &memory) noexcept override;

    U32 Run(Memory &memory) override;

    FORCE_INLINE BYTE FetchByte(const Memory &memory) {
        DWORD EffectiveAddress = EFFECTIVE_ADDRESS(PC, CS);
        PC++;
        cycles++;
        return memory[EffectiveAddress];
    }

    template<typename T>
    FORCE_INLINE T Fetch(const Memory &memory) {
        cycles += 1;
        BYTE ll = FetchByte(memory);
        if constexpr (std::is_same_v<T, BYTE>)
            return ll;
        BYTE hh = FetchByte(memory);
        return (hh << 8) | ll;
    }

    FORCE_INLINE BYTE ReadByte(Memory &memory, const DWORD &address) {
        cycles += 4;
        return memory[address];
    }

    template<typename T>
    FORCE_INLINE T Read(Memory &memory, const DWORD &address) {
        BYTE ll = ReadByte(memory, address);
        if constexpr (std::is_same_v<T, BYTE>)
            return ll;
        BYTE hh = ReadByte(memory, address + 1);

        // Additional 4 cycles for WORD read of odd address
        if (address & 0x01)
            cycles += 4;
        return (hh << 8) | ll;
    }

    FORCE_INLINE void WriteByte(Memory &memory, const DWORD &address, const BYTE value) {
        memory[address] = value;
    }

    template<typename T>
    FORCE_INLINE void Write(Memory &memory, const DWORD &address, const T value) {
        WriteByte(memory, address, value & 0xFF);
        if constexpr (std::is_same_v<T, BYTE>)
            return;
        WriteByte(memory, address + 1, (value >> 8) & 0xFF);
    }

    // Addressing routine

    // Override segment register
    // Current segment is a segment used to calculate EFFECTIVE ADDRESS
    // Default is DS
    FORCE_INLINE void OverrideSegmentRegister(WORD *newSegment) {
        currentSegment = newSegment;
        cycles += 2;
    }

    // Direct addressing mode
    // Effective address is taken directly from the displacement field of the instruction
    // Takes 6 cycles
    FORCE_INLINE DWORD GetDirectAddress(const Memory &memory) {
        WORD offset = Fetch<WORD>(memory);
        return EFFECTIVE_ADDRESS(offset, *currentSegment);
    }

    // Base addressing mode
    // The effective address is the sum of a displacement value and the content of base registers BX or BP
    // Takes 5 cycles
    // Additional 4 cycles if displacement presented
    FORCE_INLINE DWORD GetBasedAddress(const Memory &memory, const WORD &baseRegister, const BYTE dispSize = 0) {
        WORD disp = 0;
        if (dispSize != 0) {
            disp += dispSize == 2 ? Fetch<WORD>(memory) : Fetch<BYTE>(memory);
            cycles += 4;
        }
        cycles += 4;

        // if BP was chosen as a Base register, SS is forced to be used as a segment register
        // See "The 8086 Family Users Manual", p.93 BaseAddressing section
        const WORD *realSegment = (&baseRegister == &BP) ? &SS : currentSegment;
        return EFFECTIVE_ADDRESS((baseRegister + disp), *realSegment);
    }

    // Indexed addressing mode
    // The effective address is the sum of a displacement value and the content of index registers SI or DI
    // Takes 5 cycles
    // Additional 4 cycles if displacement presented
    FORCE_INLINE DWORD GetIndexedAddress(const Memory &memory, const WORD &indexRegister, const BYTE dispSize = 0) {
        WORD disp = 0;
        if (dispSize != 0) {
            disp += dispSize == 2 ? Fetch<WORD>(memory) : Fetch<BYTE>(memory);
            cycles += 4;
        }
        cycles += 4;
        return EFFECTIVE_ADDRESS((indexRegister + disp), *currentSegment);
    }

    // Based Indexed addressing mode
    // The effective address that is the sum of a base register (BP/BX), an index register (SI/DI) and a displacement
    // Takes 7 cycles for BP+DI / BX+SI
    // Takes 8 cycles for BP+SI / BX+DI
    // Additional 4 cycles if displacement presented
    FORCE_INLINE DWORD GetBasedIndexedAddress(const Memory &memory, const WORD *baseRegister, const WORD *indexRegister, const BYTE dispSize = 0) {
        WORD disp = 0;
        if (dispSize != 0) {
            disp += dispSize == 2 ? Fetch<WORD>(memory) : Fetch<BYTE>(memory);
            cycles += 4;
        }
        if ((baseRegister == &BP && indexRegister == &DI) || (baseRegister == &BX && indexRegister == &SI))
            cycles += 2;
        else
            cycles += 3;
        cycles += 4;
        return EFFECTIVE_ADDRESS((*baseRegister + *indexRegister + disp), *currentSegment);
    }

    // MOD|REG|R/M control byte principles
    //
    //
    // MOD Bits 6-7 (mode); determines how R/M field is interpreted
    //
    // 00 Use R/M Table 1 for R/M operand
    // 01 Use R/M Table 2 with 8-bit displacement
    // 10 Use R/M Table 2 with 16-bit displacement
    // 11 Two register instruction; use REG table
    //
    //
    // REG Bits 3-5 (register) or SREG (Seg register) (Mod = 11)
    //
    // REG | w=0 | w=1 | // SREG
    // 000 | AL  | AX  | // 000 ES
    // 001 | CL  | CX  | // 001 CS
    // 010 | DL  | DX  | // 010 SS
    // 011 | BL  | BX  | // 110 DS
    // 100 | AH  | SP
    // 101 | CH  | BP
    // 110 | DH  | SI
    // 111 | BH  | DI
    //
    //
    // R/M Bits 0-2 (register/memory)
    //
    // R/M Table 1 (Mod = 00)
    // 000 [BX+SI]
    // 001 [BX+DI]
    // 010 [BP+SI]
    // 011 [BP+DI]
    // 100    [SI]
    // 101    [DI]
    // 110  Direct
    // 111    [BX]
    //
    // R/M Table 2 (Mod = 01 || Mod = 10) Add DISP to register specified
    // 000 [BX+SI] + 1 or 2 bytes of disp
    // 001 [BX+DI] + 1 or 2 bytes of disp
    // 010 [BP+SI] + 1 or 2 bytes of disp
    // 011 [BP+DI] + 1 or 2 bytes of disp
    // 100    [SI] + 1 or 2 bytes of disp
    // 101    [DI] + 1 or 2 bytes of disp
    // 110    [BP] + 1 or 2 bytes of disp
    // 111    [BX] + 1 or 2 bytes of disp
    //
    // R/M Table 3 (Mod = 11)
    //
    // REG | w=0 | w=1
    // 000 | AL  | AX
    // 001 | CL  | CX
    // 010 | DL  | DX
    // 011 | BL  | BX
    // 100 | AH  | SP
    // 101 | CH  | BP
    // 110 | DH  | SI
    // 111 | BH  | DI

    InstructionData GetInstructionDataNoFetch(Memory &memory, OperandSize operandSize, InstructionDirection direction, const ModRegByte modReg, bool isSRegInstruction = false) {
        InstructionData instructionData{};

        // Pre-calculate target registers pointers
        void *regRegPtr = operandSize == OperandSize::BYTE ?
                          (void *) GetRegBytePtr(modReg.reg) :
                          (void *) GetRegWordPtr(modReg.reg);
        void *rmRegPtr = operandSize == OperandSize::BYTE ?
                         (void *) GetRegBytePtr(modReg.rm) :
                         (void *) GetRegWordPtr(modReg.rm);

        // Reg-Reg instructions
        if (modReg.mod == 0b11) {
            OperandType regOperands = OperandType::Reg;
            instructionData.doubleOps.leftOp.type = instructionData.doubleOps.rightOp.type = regOperands;

            // MemReg_Imm instruction direction in this branch covers only Register destination
            // Only one operand needed if instruction direction is MemReg_Imm
            if (direction == InstructionDirection::MemReg_Imm) {
                instructionData.singleOp.reg = rmRegPtr;
                return instructionData;
            }

            instructionData.doubleOps.leftOp.reg = rmRegPtr;
            instructionData.doubleOps.rightOp.reg = regRegPtr;
            return instructionData;
        }
        // Mem-Reg or Reg-Mem instructions
        else {
            OperandInfo op1;
            op1.type = OperandType::Mem;
            op1.mem = GetModRegAddress(memory, modReg);

            // MemReg_Imm instruction direction in this branch covers only Memory destination
            // Only one operand needed if instruction direction is MemReg_Imm
            if (direction == InstructionDirection::MemReg_Imm) {
                instructionData.singleOp = op1;
                return instructionData;
            }

            OperandInfo op2;
            op2.type = OperandType::Reg;
            op2.reg = regRegPtr;

            instructionData.doubleOps.leftOp = direction == InstructionDirection::Mem_Reg ? op1 : op2;
            instructionData.doubleOps.rightOp = direction == InstructionDirection::Mem_Reg ? op2 : op1;
            return instructionData;
        }
    }

    InstructionData GetInstructionData(Memory &memory, OperandSize operandSize, InstructionDirection direction, bool isSRegInstruction = false) {
        const BYTE modByte = Fetch<BYTE>(memory);
        const ModRegByte modReg = ModRegByte(modByte);
        return GetInstructionDataNoFetch(memory, operandSize, direction, modReg, isSRegInstruction);
    }

    // REG | R/M should be passed
    BYTE *GetRegBytePtr(BYTE modByte) {
        assert(modByte <= 7);
        BYTE *regTable[] = {&AL, &CL, &DL, &BL, &AH, &CH, &DH, &BH};
        return regTable[modByte];
    }

    // REG | R/M should be passed
    WORD *GetRegWordPtr(BYTE modByte) {
        assert(modByte <= 7);
        WORD *regTable[] = {&AX, &CX, &DX, &BX, &SP, &BP, &SI, &DI};
        return regTable[modByte];
    }

    // REG | R/M should be passed
    WORD *GetSRegWordPtr(BYTE modByte) {
        assert(modByte <= 7);
        WORD *regTable[] = {&ES, &CS, &SS, nullptr, nullptr, nullptr, &DS, nullptr};
        return regTable[modByte];
    }

    DWORD GetModRegAddress(const Memory &memory, const ModRegByte &modReg) {
        switch (modReg.rm) {
            case 0b000:
                return GetBasedIndexedAddress(memory, &BX, &SI, modReg.mod);
            case 0b001:
                return GetBasedIndexedAddress(memory, &BX, &DI, modReg.mod);
            case 0b010:
                return GetBasedIndexedAddress(memory, &BP, &SI, modReg.mod);
            case 0b011:
                return GetBasedIndexedAddress(memory, &BP, &DI, modReg.mod);
            case 0b100:
                return GetIndexedAddress(memory, SI, modReg.mod);
            case 0b101:
                return GetIndexedAddress(memory, DI, modReg.mod);
            case 0b110:
                return (modReg.mod != 0) ? // special case for 110
                       GetBasedAddress(memory, BP, modReg.mod) :
                       GetDirectAddress(memory);
            case 0b111:
                return GetBasedAddress(memory, BX, modReg.mod);
        }
        throw; // invalid case; something went wrong
    }
};
