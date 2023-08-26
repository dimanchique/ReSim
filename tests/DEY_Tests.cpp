#include "CPU6502_Tests.h"

class  CPU6502_DEYFixture: public CPU6502_TestFixture{};

TEST_F(CPU6502_DEYFixture, DEY_IMPL_CanAffectY){
    BYTE InitialValue = 0x9;
    BYTE TargetValue = InitialValue - 1;

    // given:
    cpu.Y = InitialValue;                           // set InitialValue to Y
    mem[0xFFFC] = CPU6502_OpCodes::DEY_IMPL;        // call DEY

    // when:
    cpu.Run(2, mem);

    // then:
    EXPECT_NE(cpu.Y, InitialValue);
    EXPECT_EQ(cpu.Y, TargetValue);
    EXPECT_FALSE(cpu.Z);
    EXPECT_FALSE(cpu.N);
}

TEST_F(CPU6502_DEYFixture, DEY_IMPL_CanAffectZeroFlag){
    BYTE InitialValue = 0x1;
    BYTE TargetValue = InitialValue - 1;

    // given:
    cpu.Y = InitialValue;                           // set InitialValue to Y
    mem[0xFFFC] = CPU6502_OpCodes::DEY_IMPL;        // call DEY

    // when:
    cpu.Run(2, mem);

    // then:
    EXPECT_NE(cpu.Y, InitialValue);
    EXPECT_EQ(cpu.Y, TargetValue);
    EXPECT_TRUE(cpu.Z);
    EXPECT_FALSE(cpu.N);
}

TEST_F(CPU6502_DEYFixture, DEY_IMPL_CanAffectNegativeFlag){
    BYTE InitialValue = 0x0;
    BYTE TargetValue = InitialValue - 1;

    // given:
    cpu.Y = InitialValue;                           // set InitialValue to Y
    mem[0xFFFC] = CPU6502_OpCodes::DEY_IMPL;        // call DEY

    // when:
    cpu.Run(2, mem);

    // then:
    EXPECT_NE(cpu.Y, InitialValue);
    EXPECT_EQ(cpu.Y, TargetValue);
    EXPECT_FALSE(cpu.Z);
    EXPECT_TRUE(cpu.N);
}
