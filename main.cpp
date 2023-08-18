#include <iostream>
#include <vector>
#include "OpCodes_6502.h"

struct Memory{
    explicit Memory(U32 MEM_SIZE = 1024) : SIZE(MEM_SIZE){
        MEM.resize(SIZE);
    }

    BYTE operator[](U32 ADDR) const {
        return MEM[ADDR];
    }

    BYTE& operator[](U32 ADDR){
        return MEM[ADDR];
    }

    void Initialize(){
        for(U32 i = 0; i < SIZE; ++i)
            MEM[i] = 0;
    }
    std::vector<BYTE> MEM;
    U32 SIZE;
};


struct CPU_6502{
//*****************************************************
///////////////////////// Main Registers
//*****************************************************
    WORD PC;           // Program Counter
    WORD SP;           // Stack Pointer
    BYTE A;            // Accumulator
    BYTE X;            // X Index
    BYTE Y;            // Y Index
///////////////////////// Processor Status
    BYTE CF:1;         // Carry Flag
    BYTE ZF:1;         // Zero Flag
    BYTE ID:1;         // Interrupt Disable
    BYTE DM:1;         // Decimal Mode
    BYTE BC:1;         // Break Command
    BYTE NU:1;         // Not Used
    BYTE OF:1;         // Overflow Flag
    BYTE NF:1;         // Negative Flag

//*****************************************************
///////////////////////// Functionality
//*****************************************************
    void Reset(Memory& memory){
        PC = 0xFFFC;
        SP = 0x0100;

        A = X = Y = 0;
        CF = ZF = ID = DM = BC = OF = NF = 0;

        memory.Initialize();
    }

    BYTE FetchByte(Memory& memory){
        BYTE Data = memory[PC];
        PC++;
        return Data;
    }

    WORD FetchWord(Memory& memory){
        // 6502 is little endian
        WORD Data = memory[PC];
        PC++;

        Data |= (memory[PC] << 8);
        PC++;
        return Data;
    }

    void WriteWord(WORD Value, U32 ADDR, Memory& memory){
        memory[ADDR]      =  Value & 0xFF;
        memory[ADDR + 1]  = (Value >> 8);
    }

    BYTE ReadByte(BYTE ADDR, Memory& memory) const {
        BYTE Data = memory[ADDR];
        return Data;
    }

    void LDASetStatus(){
        ZF = (A == 0);
        NF = (A & 0b10000000) > 0;
    }

    void Execute(Memory& memory){
        while(true){
            BYTE Instruction = FetchByte(memory);
            switch (Instruction) {
                case OpCodes_6502::LDA_IM: {
                    printf("Executing LDA_IM\n");
                    BYTE Value = FetchByte(memory);
                    A = Value;
                    LDASetStatus();
                    printf("Stored %x in A\n", Value);
                    break;
                }
                case OpCodes_6502::LDA_ZP: {
                    printf("Executing LDA_ZP\n");
                    BYTE ZeroPageAddress = FetchByte(memory);
                    A = ReadByte(ZeroPageAddress, memory);
                    LDASetStatus();
                    break;
                }
                case OpCodes_6502::LDA_ZPX: {
                    printf("Executing LDA_ZPX\n");
                    BYTE ZeroPageAddress = FetchByte(memory);
                    ZeroPageAddress += X;
                    A = ReadByte(ZeroPageAddress, memory);
                    LDASetStatus();
                    break;
                }
                case OpCodes_6502::JSR_ABS: {
                    printf("Executing JSR_ABS\n");
                    WORD JumpAddress = FetchWord(memory);
                    WriteWord(PC - 1, SP, memory);
                    PC = JumpAddress;
                    printf("Jumping to %x\n", PC);
                    break;
                }
                default: {
                    printf("Instruction not handled; End execution");
                    return;
                }
            }
        }
    }
};

int main() {
    Memory mem{1024 * 64};
    CPU_6502 cpu{};
    cpu.Reset(mem);

    // start
    mem[0xFFFC] = OpCodes_6502::JSR_ABS;
    mem[0xFFFD] = 0xF9;
    mem[0xFFFE] = 0xFF;
    mem[0xFFFA] = 0x42;
    mem[0xFFF9] = OpCodes_6502::LDA_IM;
    //end
    cpu.Execute(mem);
    return 0;
}
