#include "CPU6502_Tests.h"

class CPU6502_LDAFixture : public CPU6502_TestFixture{
};

TEST_F(CPU6502_LDAFixture, LDA_IM){
    // given:
    mem[0xFFFC] = CPU6502_OpCodes::LDA_IM;      // read value from the next mem cell
    mem[0xFFFD] = 0x42;                         // store this value in A register

    CPU6502 cpuCopy = cpu;
    // when:
    U32 CNT = cpu.Run(2, mem);

    // then:
    EXPECT_EQ(cpu.A, 0x42);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
    VerifyUnmodifiedFlagsFromLDA(cpu, cpuCopy);
    EXPECT_EQ(CNT, 2);
}

TEST_F(CPU6502_LDAFixture, LDA_ZP){
    // given:
    mem[0xFFFC] = CPU6502_OpCodes::LDA_ZP;      // read pointer to the ZP memory from the next mem cell
    mem[0xFFFD] = 0x42;                         // read value from memory using pointer
    mem[0x0042] = 0x37;                         // store this value in A register

    CPU6502 cpuCopy = cpu;
    // when:
    U32 CNT = cpu.Run(3, mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
    VerifyUnmodifiedFlagsFromLDA(cpu, cpuCopy);
    EXPECT_EQ(CNT, 3);
}

TEST_F(CPU6502_LDAFixture, LDA_ZPX){
    // given:
    cpu.X = 0x5;                                // read pointer to the ZP memory from the next mem cell
    mem[0xFFFC] = CPU6502_OpCodes::LDA_ZPX;     // add X register value to this pointer
    mem[0xFFFD] = 0x42;                         // read value from memory using pointer
    mem[0x0047] = 0x37;                         // store this value in A register

    CPU6502 cpuCopy = cpu;
    // when:
    U32 CNT = cpu.Run(4, mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
    VerifyUnmodifiedFlagsFromLDA(cpu, cpuCopy);
    EXPECT_EQ(CNT, 4);
}

TEST_F(CPU6502_LDAFixture, LDA_ZPX_WITH_WRAP){
    // given:
    cpu.X = 0xFF;                               // read pointer to the ZP memory from the next mem cell
    mem[0xFFFC] = CPU6502_OpCodes::LDA_ZPX;     // add X register value to this pointer
    mem[0xFFFD] = 0x80;                         // read value from memory using pointer
    mem[0x007F] = 0x37;                         // store this value in A register

    CPU6502 cpuCopy = cpu;
    // when:
    U32 CNT = cpu.Run(4, mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
    VerifyUnmodifiedFlagsFromLDA(cpu, cpuCopy);
    EXPECT_EQ(CNT, 4);
}
