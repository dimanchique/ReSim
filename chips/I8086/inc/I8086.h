#pragma once

#include "I8086_Status.h"
#include "I8086_OpCodes_Main.h"
#include "core/macro.h"
#include "compute.h"
#include "memory.h"
#include "I8086_Addressing.h"
#include <cassert>

#define STOP_OPCODE I8086_OpCodes_Main::HLT // HLT instruction is pretty OK to use as a STOP opcode

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

    void Reset() noexcept override;

    U32 Run() override;

    bool Step() override;

    FORCE_INLINE BYTE FetchByte() {
        const DWORD EffectiveAddress = EFFECTIVE_ADDRESS(PC++, CS);
        ++cycles;
        return bus->Read(EffectiveAddress);
    }

    template<typename T>
    FORCE_INLINE T Fetch() {
        ++cycles;
        const BYTE ll = FetchByte();
        if (std::is_same_v<T, BYTE>)
            return ll;
        const BYTE hh = FetchByte();
        return (hh << 8) | ll;
    }

    FORCE_INLINE BYTE ReadByte(const DWORD address) {
        cycles += 4;
        return bus->Read(address);
    }

    template<typename T>
    FORCE_INLINE T Read(const DWORD address) {
        const BYTE ll = ReadByte(address);
        if (std::is_same_v<T, BYTE>)
            return ll;
        const BYTE hh = ReadByte(address + 1);

        // Additional 4 cycles for WORD read of odd address
        if (address & 0x01)
            cycles += 4;
        return (hh << 8) | ll;
    }

    FORCE_INLINE void WriteByte(const DWORD address, const BYTE value) {
        bus->Write(address, value);
    }

    template<typename T>
    FORCE_INLINE void Write(const DWORD address, const T value) {
        WriteByte(address, value & 0xFF);
        if (std::is_same_v<T, BYTE>)
            return;
        WriteByte(address + 1, (value >> 8) & 0xFF);
    }

    FORCE_INLINE void PushDataToStack(const WORD data) {
        DWORD stackPointerAddress = EFFECTIVE_ADDRESS(SP, SS);
        Write<BYTE>(--stackPointerAddress, (data & 0xFF00) >> 8);
        SP--;
        Write<BYTE>(--stackPointerAddress, data & 0xFF);
        SP--;
    }

    FORCE_INLINE WORD PopDataFromStack() {
        DWORD stackPointerAddress = EFFECTIVE_ADDRESS(SP, SS);
        const BYTE ll = ReadByte(stackPointerAddress++);
        SP++;
        const BYTE hh = ReadByte(stackPointerAddress++);
        SP++;
        return hh << 8 | ll;
    }

    // Override segment register
    // Current segment is a segment used to calculate EFFECTIVE ADDRESS
    // Default is DS
    FORCE_INLINE void OverrideSegmentRegister(WORD *newSegment) {
        currentSegment = newSegment;
        cycles += 2;
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

    template<typename T>
    InstructionData<T> GetInstructionDataNoFetch(const OperandSize operandSize, const InstructionDirection direction, const ModRegByte modReg) {
        InstructionData<T> instructionData{};

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
            instructionData.leftOp.type = instructionData.rightOp.type = regOperands;
            instructionData.leftOp.get = instructionData.rightOp.get = RegisterGet;
            instructionData.leftOp.set = instructionData.rightOp.set = RegisterSet;

            // MemReg_Imm instruction direction in this branch covers only Register destination
            // Only one operand needed if instruction direction is MemReg_Imm
            if (direction == InstructionDirection::MemReg_Imm) {
                instructionData.singleOp.operand.reg = rmRegPtr;
                return instructionData;
            }

            instructionData.leftOp.operand.reg = rmRegPtr;
            instructionData.rightOp.operand.reg = regRegPtr;
            return instructionData;
        }
        // Mem-Reg or Reg-Mem instructions
        else {
            OperandInfo<T> op1;
            op1.type = OperandType::Mem;
            op1.operand.mem = GetModRegAddress(modReg);
            op1.get = AddressGet;
            op1.set = AddressSet;

            // MemReg_Imm instruction direction in this branch covers only Memory destination
            // Only one operand needed if instruction direction is MemReg_Imm
            if (direction == InstructionDirection::MemReg_Imm) {
                instructionData.singleOp = op1;
                return instructionData;
            }

            OperandInfo<T> op2;
            op2.type = OperandType::Reg;
            op2.operand.reg = regRegPtr;
            op2.get = RegisterGet;
            op2.set = RegisterSet;

            instructionData.leftOp = direction == InstructionDirection::MemReg_Reg ? op1 : op2;
            instructionData.rightOp = direction == InstructionDirection::MemReg_Reg ? op2 : op1;
            return instructionData;
        }
    }

    template<typename T>
    InstructionData<T> GetInstructionData(const OperandSize operandSize, const InstructionDirection direction) {
        const BYTE modByte = Fetch<BYTE>();
        const ModRegByte modReg = ModRegByte::FromByte(modByte);
        return GetInstructionDataNoFetch<T>(operandSize, direction, modReg);
    }

    DWORD GetModRegAddress(const ModRegByte &modReg) {
        switch (modReg.rm) {
            case 0b000:
                return GetBasedIndexedAddress(&BX, &SI, modReg.mod);
            case 0b001:
                return GetBasedIndexedAddress(&BX, &DI, modReg.mod);
            case 0b010:
                return GetBasedIndexedAddress(&BP, &SI, modReg.mod);
            case 0b011:
                return GetBasedIndexedAddress(&BP, &DI, modReg.mod);
            case 0b100:
                return GetIndexedAddress(SI, modReg.mod);
            case 0b101:
                return GetIndexedAddress(DI, modReg.mod);
            case 0b110:
                return (modReg.mod != 0) ? // special case for 110
                       GetBasedAddress(BP, modReg.mod) :
                       GetDirectAddress();
            case 0b111:
                return GetBasedAddress(BX, modReg.mod);
        }
        throw InvalidInstruction();
    }

    // Getters/Setters for instruction data operands
    template<typename T>
    static void AddressSet(I8086 &cpu, const void *address, T value) {
        cpu.Write(*(DWORD *) address, value);
    }

    template<typename T>
    static void RegisterSet(I8086 &cpu, const void *destReg, T value) {
        *(T *) *(uintptr_t *) destReg = value;
    }

    template<typename T>
    static T AddressGet(I8086 &cpu, const void *address) {
        return cpu.Read<T>(*(DWORD *) address);
    }

    template<typename T>
    static T RegisterGet(I8086 &cpu, const void *srcReg) {
        return *(T *) *(uintptr_t *) srcReg; // srcReg is passed as a pointer to void pointer
    }

    // Addressing modes
    // Direct addressing mode
    // Effective address is taken directly from the displacement field of the instruction
    // Takes 6 cycles
    FORCE_INLINE DWORD GetDirectAddress() {
        const WORD offset = Fetch<WORD>();
        return EFFECTIVE_ADDRESS(offset, *currentSegment);
    }

    // Base addressing mode
    // The effective address is the sum of a displacement value and the content of base registers BX or BP
    // Takes 5 cycles
    // Additional 4 cycles if displacement presented
    FORCE_INLINE DWORD GetBasedAddress(const WORD &baseRegister, const BYTE dispSize = 0) {
        WORD disp = 0;
        if (dispSize != 0) {
            disp += dispSize == 2 ? Fetch<WORD>() : Fetch<BYTE>();
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
    FORCE_INLINE DWORD GetIndexedAddress(const WORD &indexRegister, const BYTE dispSize = 0) {
        WORD disp = 0;
        if (dispSize != 0) {
            disp += dispSize == 2 ? Fetch<WORD>() : Fetch<BYTE>();
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
    FORCE_INLINE DWORD GetBasedIndexedAddress(const WORD *baseRegister, const WORD *indexRegister, const BYTE dispSize = 0) {
        WORD disp = 0;
        if (dispSize != 0) {
            disp += dispSize == 2 ? Fetch<WORD>() : Fetch<BYTE>();
            cycles += 4;
        }
        if ((baseRegister == &BP && indexRegister == &DI) || (baseRegister == &BX && indexRegister == &SI))
            cycles += 2;
        else
            cycles += 3;
        cycles += 4;
        return EFFECTIVE_ADDRESS((*baseRegister + *indexRegister + disp), *currentSegment);
    }

    // REG | R/M should be passed
    BYTE *GetRegBytePtr(const BYTE modByte) {
        assert(modByte <= 7);
        BYTE *regTable[] = {&AL, &CL, &DL, &BL, &AH, &CH, &DH, &BH};
        return regTable[modByte];
    }

    // REG | R/M should be passed
    WORD *GetRegWordPtr(const BYTE modByte) {
        assert(modByte <= 7);
        WORD *regTable[] = {&AX, &CX, &DX, &BX, &SP, &BP, &SI, &DI};
        return regTable[modByte];
    }

    // REG | R/M should be passed
    WORD *GetSRegWordPtr(const BYTE modByte) {
        assert(modByte <= 3);
        WORD *regTable[] = {&ES, &CS, &SS, &DS};
        return regTable[modByte];
    }
};
