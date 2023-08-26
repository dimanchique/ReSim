#include "CPU6502_Tests.h"

class  CPU6502_DEXFixture: public CPU6502_TestFixture{};

TEST_F(CPU6502_DEXFixture, DEX_IMPL_CanAffectX){
    BYTE InitialValue = 0x9;
    BYTE TargetValue = InitialValue - 1;

    // given:
    cpu.X = InitialValue;                           // set InitialValue to X
    mem[0xFFFC] = CPU6502_OpCodes::DEX_IMPL;        // call DEX

    // when:
    cpu.Run(2, mem);

    // then:
    EXPECT_NE(cpu.X, InitialValue);
    EXPECT_EQ(cpu.X, TargetValue);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
}

TEST_F(CPU6502_DEXFixture, DEX_IMPL_CanAffectZeroFlag){
    BYTE InitialValue = 0x1;
    BYTE TargetValue = InitialValue - 1;

    // given:
    cpu.X = InitialValue;                           // set InitialValue to X
    mem[0xFFFC] = CPU6502_OpCodes::DEX_IMPL;        // call DEX

    // when:
    cpu.Run(2, mem);

    // then:
    EXPECT_NE(cpu.X, InitialValue);
    EXPECT_EQ(cpu.X, TargetValue);
    EXPECT_TRUE(cpu.Z);
    EXPECT_FALSE(cpu.N);
}

TEST_F(CPU6502_DEXFixture, DEX_IMPL_CanAffectNegativeFlag){
    BYTE InitialValue = 0x0;
    BYTE TargetValue = InitialValue - 1;

    // given:
    cpu.X = InitialValue;                           // set InitialValue to X
    mem[0xFFFC] = CPU6502_OpCodes::DEX_IMPL;        // call DEX

    // when:
    cpu.Run(2, mem);

    // then:
    EXPECT_NE(cpu.X, InitialValue);
    EXPECT_EQ(cpu.X, TargetValue);
    EXPECT_FALSE(cpu.Z);
    EXPECT_TRUE(cpu.N);
}
