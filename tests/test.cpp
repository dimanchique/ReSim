#include <gtest/gtest.h>
#include "CPU6502_OpCodes.h"
#include <CPU6502.h>
#include <Memory.h>

class CPU6502_TestFixture : public testing::Test{
public:
    Memory mem{64};
    CPU6502 cpu{};

    virtual void SetUp() override{
        cpu.Reset(mem);
    }

    void TearDown() override{

    }
};

TEST_F(CPU6502_TestFixture, LDA_IM){
    // start
    mem[0xFFFC] = CPU6502_OpCodes::LDA_IM;
    mem[0xFFFD] = 0x42;
    //end

    WORD CNT = cpu.Run(mem);
    ASSERT_EQ(cpu.A, 0x42);
    ASSERT_EQ(CNT, 1);
}

TEST_F(CPU6502_TestFixture, LDA_IM_WITH_JSR) {
    Memory mem{64};
    CPU6502 cpu{};
    cpu.Reset(mem);

    // start
    mem[0xFFFC] = CPU6502_OpCodes::JSR_ABS;
    mem[0xFFFD] = 0x42;
    mem[0xFFFE] = 0x42;
    mem[0x4242] = CPU6502_OpCodes::LDA_IM;
    mem[0x4243] = 0x84;
    //end

    WORD CNT = cpu.Run(mem);
    ASSERT_EQ(cpu.A, 0x84);
    ASSERT_EQ(CNT, 2);
}

TEST(RegularTests, MemCheck) {
    Memory mem{64};
    mem.Reset();

    for(U32 i = 0; i < mem.GetSize(); ++i)
        ASSERT_EQ(mem[i], 0);
}