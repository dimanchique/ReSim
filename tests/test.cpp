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

    // when:
    WORD CNT = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x42);
    EXPECT_EQ(CNT, 1);
}

TEST_F(CPU6502_TestFixture, LDA_ZP){
    // given:
    // start
    mem[0xFFFC] = CPU6502_OpCodes::LDA_ZP;      // read pointer to the ZP memory from the next mem cell
    mem[0xFFFD] = 0x42;                         // read value from memory using pointer
    mem[0x0042] = 0x37;                         // store this value in A register
    //end

    // when:
    WORD CNT = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37);
    EXPECT_EQ(CNT, 1);
}

TEST_F(CPU6502_TestFixture, LDA_ZPX){
    // given:
    cpu.X = 5;
    // start
    mem[0xFFFC] = CPU6502_OpCodes::LDA_ZPX;     // read pointer to the ZP memory from the next mem cell
    mem[0xFFFD] = 0x42;                         // add X register value to this pointer
    mem[0x0047] = 0x37;                         // read value from memory using pointer
    //end                                       // store this value in A register

    // when:
    WORD CNT = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37);
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

    // when:
    WORD CNT = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x84);
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