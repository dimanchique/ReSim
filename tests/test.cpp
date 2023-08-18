#include <gtest/gtest.h>
#include "CPU6502_OpCodes.h"
#include <CPU6502.h>
#include <Memory.h>

class CPU6502_TestFixture : public testing::Test{
public:
    Memory mem{64};
    CPU6502 cpu{};

    void SetUp() override{
        cpu.Reset(mem);
    }

    void TearDown() override{

    }
};

TEST_F(CPU6502_TestFixture, LDA_IM){
    // given:
    // start
    mem[0xFFFC] = CPU6502_OpCodes::LDA_IM;      // read value from the next mem cell
    mem[0xFFFD] = 0x42;                         // store this value in A register
    //end

    CPU6502 cpuCopy = cpu;
    // when:
    WORD CNT = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x42);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
    EXPECT_EQ(cpu.C, cpuCopy.C);
    EXPECT_EQ(cpu.I, cpuCopy.I);
    EXPECT_EQ(cpu.D, cpuCopy.D);
    EXPECT_EQ(cpu.B, cpuCopy.B);
    EXPECT_EQ(cpu.V, cpuCopy.V);
    EXPECT_EQ(CNT, 1);
}

TEST_F(CPU6502_TestFixture, LDA_ZP){
    // given:
    // start
    mem[0xFFFC] = CPU6502_OpCodes::LDA_ZP;      // read pointer to the ZP memory from the next mem cell
    mem[0xFFFD] = 0x42;                         // read value from memory using pointer
    mem[0x0042] = 0x37;                         // store this value in A register
    //end

    CPU6502 cpuCopy = cpu;
    // when:
    WORD CNT = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
    EXPECT_EQ(cpu.C, cpuCopy.C);
    EXPECT_EQ(cpu.I, cpuCopy.I);
    EXPECT_EQ(cpu.D, cpuCopy.D);
    EXPECT_EQ(cpu.B, cpuCopy.B);
    EXPECT_EQ(cpu.V, cpuCopy.V);
    EXPECT_EQ(CNT, 1);
}

TEST_F(CPU6502_TestFixture, LDA_ZPX){
    // given:
    cpu.X = 0x5;
    // start
    mem[0xFFFC] = CPU6502_OpCodes::LDA_ZPX;     // read pointer to the ZP memory from the next mem cell
    mem[0xFFFD] = 0x42;                         // add X register value to this pointer
    mem[0x0047] = 0x37;                         // read value from memory using pointer
    //end                                       // store this value in A register

    CPU6502 cpuCopy = cpu;
    // when:
    WORD CNT = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
    EXPECT_EQ(cpu.C, cpuCopy.C);
    EXPECT_EQ(cpu.I, cpuCopy.I);
    EXPECT_EQ(cpu.D, cpuCopy.D);
    EXPECT_EQ(cpu.B, cpuCopy.B);
    EXPECT_EQ(cpu.V, cpuCopy.V);
    EXPECT_EQ(CNT, 1);
}

TEST_F(CPU6502_TestFixture, LDA_ZPX_WITH_WRAP){
    // given:
    cpu.X = 0xFF;
    // start
    mem[0xFFFC] = CPU6502_OpCodes::LDA_ZPX;     // read pointer to the ZP memory from the next mem cell
    mem[0xFFFD] = 0x80;                         // add X register value to this pointer
    mem[0x007F] = 0x37;                         // read value from memory using pointer
    //end                                       // store this value in A register

    CPU6502 cpuCopy = cpu;
    // when:
    WORD CNT = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
    EXPECT_EQ(cpu.C, cpuCopy.C);
    EXPECT_EQ(cpu.I, cpuCopy.I);
    EXPECT_EQ(cpu.D, cpuCopy.D);
    EXPECT_EQ(cpu.B, cpuCopy.B);
    EXPECT_EQ(cpu.V, cpuCopy.V);
    EXPECT_EQ(CNT, 1);
}

TEST_F(CPU6502_TestFixture, LDA_IM_WITH_JSR) {
    // given:
    // start
    mem[0xFFFC] = CPU6502_OpCodes::JSR_ABS;
    mem[0xFFFD] = 0x42;
    mem[0xFFFE] = 0x42;
    mem[0x4242] = CPU6502_OpCodes::LDA_IM;
    mem[0x4243] = 0x84;
    //end

    CPU6502 cpuCopy = cpu;
    // when:
    WORD CNT = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x84);
    EXPECT_FALSE(cpu.Z);
    EXPECT_TRUE(cpu.N);                             // 0x84 is 0b10000100 and N is checking the 7's bit in A and it's 1
    EXPECT_EQ(cpu.C, cpuCopy.C);
    EXPECT_EQ(cpu.I, cpuCopy.I);
    EXPECT_EQ(cpu.D, cpuCopy.D);
    EXPECT_EQ(cpu.B, cpuCopy.B);
    EXPECT_EQ(cpu.V, cpuCopy.V);
    EXPECT_EQ(CNT, 2);
}

TEST_F(CPU6502_TestFixture, MemCheck) {
    // given:
    unsigned long long MemCellsSum = 0;

    // when:
    for(U32 i = 0; i < mem.GetSize(); ++i)
        MemCellsSum+=mem[i];

    // then:
    EXPECT_EQ(MemCellsSum, 0);
}