#include "CPU6502_TestingSuite.h"

class CPU6502_ANDFixture : public CPU6502_TestFixture{
public:
    void AND_IM_CanLoadValue(BYTE InitialValue, BYTE MemoryValue){
        // given:
        cpu.A = InitialValue;
        mem[0xFFFC] = CPU6502_OpCodes::AND_IM;          // read value from the next mem cell
        mem[0xFFFD] = MemoryValue;                      // store this value in target register

        CyclesExpected = 2;

        // when:
        CyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, MemoryValue & InitialValue);
        CheckCyclesCount();
    }

    void AND_ZP_CanLoadValue(BYTE InitialValue, BYTE MemoryValue){
        // given:
        cpu.A = InitialValue;
        mem[0xFFFC] = CPU6502_OpCodes::AND_ZP;                      // read pointer to the ZP memory from the next mem cell
        mem[0xFFFD] = 0x42;                                         // read value from memory using pointer
        mem[0x0042] = MemoryValue;                                  // store this value in target register

        CyclesExpected = 3;

        // when:
        CyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, MemoryValue & InitialValue);
        CheckCyclesCount();
    }

    void AND_ZPX_CanLoadValue(BYTE InitialValue, BYTE MemoryValue){
        // given:
        cpu.A = InitialValue;
        cpu.X = 0x10;
        mem[0xFFFC] = CPU6502_OpCodes::AND_ZPX;                 // read pointer to the ZP memory from the next mem cell
        mem[0xFFFD] = 0x42;                                     // add AffectingRegister value to this pointer
        mem[(mem[0xFFFD] + cpu.X) & 0xFF] = MemoryValue;        // read value from memory using pointer
        // store this value in TargetRegister register
        CyclesExpected = 4;

        // when:
        CyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, MemoryValue & InitialValue);
        CheckCyclesCount();
    }

    void AND_ABS_CanLoadValue(BYTE InitialValue, BYTE MemoryValue){
        // given:
        cpu.A = InitialValue;
        mem[0xFFFC] = CPU6502_OpCodes::AND_ABS;     // read the 16 bit Little Endian pointer from the next mem cell
        mem[0xFFFD] = 0x80;                         // read from this address
        mem[0xFFFE] = 0x44;                         // 0x4480
        mem[0x4480] = MemoryValue;                  // store this value in TargetRegister

        CyclesExpected = 4;

        // when:
        CyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, MemoryValue & InitialValue);
        CheckCyclesCount();
    }

    void AND_ABS_CanLoadValue(CPU6502_OpCodes OpCode, BYTE InitialValue, BYTE MemoryValue, BYTE AffectingRegister){
        // given:
        cpu.A = InitialValue;
        mem[0xFFFC] = OpCode;                           // read the 16 bit Little Endian pointer from the next mem cell
        mem[0xFFFD] = 0x02;                             // read from this address
        mem[0xFFFE] = 0x44;                             // target value is in memory address 0x4402 + AffectingRegister
        mem[0x4402 + AffectingRegister] = MemoryValue;  // store this value in TargetRegister

        CyclesExpected = CPU6502::isPageCrossed(0x4402 + AffectingRegister, 0x4402) ? 5 : 4;

        // when:
        CyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, MemoryValue & InitialValue);
        CheckCyclesCount();
    }
};

TEST_F(CPU6502_ANDFixture, AND_IM_CanLoadValue){
    AND_IM_CanLoadValue(0xFF, 0xF);
}

TEST_F(CPU6502_ANDFixture, AND_IM_CanAffectZeroFlag){
    AND_IM_CanLoadValue(0xFF, 0x0);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(CPU6502_ANDFixture, AND_IM_CanAffectNegativeFlag){
    AND_IM_CanLoadValue(0xFF, 0xFF);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(CPU6502_ANDFixture, AND_ZP_CanLoadValue){
    AND_ZP_CanLoadValue(0xFF, 0xF);
}

TEST_F(CPU6502_ANDFixture, AND_ZP_CanAffectZeroFlag){
    AND_ZP_CanLoadValue(0xFF, 0x0);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(CPU6502_ANDFixture, AND_ZP_CanAffectNegativeFlag){
    AND_ZP_CanLoadValue(0xFF, 0xFF);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(CPU6502_ANDFixture, AND_ZPX_CanLoadValue){
    AND_ZPX_CanLoadValue(0xFF, 0xF);
}

TEST_F(CPU6502_ANDFixture, AND_ZPX_CanAffectZeroFlag){
    AND_ZPX_CanLoadValue(0xFF, 0x0);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(CPU6502_ANDFixture, AND_ZPX_CanAffectNegativeFlag){
    AND_ZPX_CanLoadValue(0xFF, 0xFF);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(CPU6502_ANDFixture, AND_ABS_CanLoadValue){
    AND_ABS_CanLoadValue(0xFF, 0xF);
}

TEST_F(CPU6502_ANDFixture, AND_ABS_CanAffectZeroFlag){
    AND_ABS_CanLoadValue(0xFF, 0x0);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(CPU6502_ANDFixture, AND_ABS_CanAffectNegativeFlag){
    AND_ABS_CanLoadValue(0xFF, 0xFF);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(CPU6502_ANDFixture, AND_ABSX_CanLoadValue){
    cpu.X = 0x05;
    AND_ABS_CanLoadValue(CPU6502_OpCodes::AND_ABSX, 0xFF, 0xF, cpu.X);
}

TEST_F(CPU6502_ANDFixture, AND_ABSX_CanLoadValue_WithExtraCycleOnPageCrossing){
    cpu.X = 0xFF;
    AND_ABS_CanLoadValue(CPU6502_OpCodes::AND_ABSX, 0xFF, 0xF, cpu.X);
}

TEST_F(CPU6502_ANDFixture, AND_ABSX_CanAffectZeroFlag){
    cpu.X = 0x05;
    AND_ABS_CanLoadValue(CPU6502_OpCodes::AND_ABSX, 0xFF, 0x0, cpu.X);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(CPU6502_ANDFixture, AND_ABSX_CanAffectNegativeFlag){
    cpu.X = 0x05;
    AND_ABS_CanLoadValue(CPU6502_OpCodes::AND_ABSX, 0xFF, 0xFF, cpu.X);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(CPU6502_ANDFixture, AND_ABSY_CanLoadValue){
    cpu.Y = 0x05;
    AND_ABS_CanLoadValue(CPU6502_OpCodes::AND_ABSY, 0xFF, 0xF, cpu.Y);
}

TEST_F(CPU6502_ANDFixture, AND_ABSY_CanLoadValue_WithExtraCycleOnPageCrossing){
    cpu.Y = 0xFF;
    AND_ABS_CanLoadValue(CPU6502_OpCodes::AND_ABSY, 0xFF, 0xF, cpu.Y);
}

TEST_F(CPU6502_ANDFixture, AND_ABSY_CanAffectZeroFlag){
    cpu.Y = 0x05;
    AND_ABS_CanLoadValue(CPU6502_OpCodes::AND_ABSY, 0xFF, 0x0, cpu.Y);
    EXPECT_TRUE(cpu.Status.Z);
}

TEST_F(CPU6502_ANDFixture, AND_ABSY_CanAffectNegativeFlag){
    cpu.Y = 0x05;
    AND_ABS_CanLoadValue(CPU6502_OpCodes::AND_ABSY, 0xFF, 0xFF, cpu.Y);
    EXPECT_TRUE(cpu.Status.N);
}

TEST_F(CPU6502_ANDFixture, AND_INDX_CanLoadValue){
    // given:
    cpu.A = 0x42;
    cpu.X = 0x04;                               // preload 0x04 to X to add it to value we read
    mem[0xFFFC] = CPU6502_OpCodes::AND_INDX;    // read the 8 bit value from the next mem cell and add X
    mem[0xFFFD] = 0x02;                         // 0x2 + 0x4 = 0x6
    mem[0x0006] = 0x00;                         // read the 16 bit Little Endian address from 0x0006-0x0007
    mem[0x0007] = 0x80;                         // read from the address we've got
    mem[0x8000] = 0x37;                         // store this value in A register

    CyclesExpected = 6;

    // when:
    CyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37 & 0x42);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}

TEST_F(CPU6502_ANDFixture, AND_INDY_CanLoadValue){
    // given:
    cpu.A = 0x42;
    cpu.Y = 0x04;                               // preload 0x04 to Y to add it to value we read
    mem[0xFFFC] = CPU6502_OpCodes::AND_INDY;    // read the 8 bit value from the next mem cell
    mem[0xFFFD] = 0x02;                         // read the 16 bit Little Endian address from 0x0002-0x0003
    mem[0x0002] = 0x00;                         //
    mem[0x0003] = 0x80;                         // 0x8000 + 0x0004 (add Y) = 0x8004
    mem[0x8004] = 0x37;                         // store this value in A register

    CyclesExpected = 5;

    // when:
    CyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37 & 0x42);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}

TEST_F(CPU6502_ANDFixture, AND_INDY_CanLoadValueWithExtraCycleOnPageCrossing){
    // given:
    cpu.A = 0x42;
    cpu.Y = 0xFF;                               // preload FF to Y to add it to absolute address we read
    mem[0xFFFC] = CPU6502_OpCodes::AND_INDY;    // read the 8 bit value from the next mem cell and add X
    mem[0xFFFD] = 0x02;                         // read the 16 bit Little Endian address from 0x0002-0x0003
    mem[0x0002] = 0x02;                         //
    mem[0x0003] = 0x80;                         // 0x8002 + 0x00FF (Y) = 0x8101 -> page crossing, so we need extra cycle
    mem[0x8101] = 0x37;                         // store this value in A register

    CyclesExpected = 6;

    // when:
    CyclesPassed = cpu.Run(mem);

    // then:
    EXPECT_EQ(cpu.A, 0x37 & 0x42);
    EXPECT_FALSE(cpu.Status.Z);
    EXPECT_FALSE(cpu.Status.N);
    CheckCyclesCount();
}
