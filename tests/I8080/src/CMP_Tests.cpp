#include "I8080_TestingSuite.h"

class I8080_CMPFixture : public I8080_TestFixture {
public:
    void CMP_CanCompareReg(const I8080_OpCodes opcode,
                           const BYTE initialAccumulator,
                           const bool expectedZero,
                           const bool expectedCarry,
                           const BYTE expectedCycles = 4) {
        // given:
        cpu.A = initialAccumulator;
        mem[0x0000] = opcode;
        mem[opcode == CPI ? 0x0002 : 0x0001] = STOP_OPCODE;

        cyclesExpected = expectedCycles;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.Status.Z, expectedZero);
        EXPECT_EQ(cpu.Status.C, expectedCarry);
        CheckCyclesCount();
    }

    void
    CMP_CanCompareMemory(const BYTE initialAccumulator,
                         const BYTE memoryValue,
                         const bool expectedZero,
                         const bool expectedCarry) {
        cpu.H = 0x12;
        cpu.L = 0x34;
        mem[0x1234] = memoryValue;
        CMP_CanCompareReg(CMP_M, initialAccumulator, expectedZero, expectedCarry, 7);
    }

    void CPI_CanCompareImmediateValue(const BYTE initialAccumulator,
                                      const BYTE memoryValue,
                                      const bool expectedZero,
                                      const bool expectedCarry) {
        mem[0x0001] = memoryValue;
        CMP_CanCompareReg(CPI, initialAccumulator, expectedZero, expectedCarry, 7);
    }
};

TEST_F(I8080_CMPFixture, CMP_A_1) {
    CMP_CanCompareReg(CMP_A, 0x10, true, false);
}

TEST_F(I8080_CMPFixture, CMP_A_2) {
    CMP_CanCompareReg(CMP_A, 0xFF, true, false);
}

TEST_F(I8080_CMPFixture, CMP_A_3) {
    CMP_CanCompareReg(CMP_A, 0xFE, true, false);
}

TEST_F(I8080_CMPFixture, CMP_A_4) {
    CMP_CanCompareReg(CMP_A, 0xAD, true, false);
}

TEST_F(I8080_CMPFixture, CMP_B_1) {
    cpu.B = 0x10;
    CMP_CanCompareReg(CMP_B, 0x10, true, false);
}

TEST_F(I8080_CMPFixture, CMP_B_2) {
    cpu.B = 0x05;
    CMP_CanCompareReg(CMP_B, 0x0A, false, false);
}

TEST_F(I8080_CMPFixture, CMP_B_3) {
    cpu.B = 0x05;
    CMP_CanCompareReg(CMP_B, 0x02, false, false);
}

TEST_F(I8080_CMPFixture, CMP_B_4) {
    cpu.B = 0x05;
    CMP_CanCompareReg(CMP_B, (BYTE)-0x1B, false, false);
}

TEST_F(I8080_CMPFixture, CMP_C_1) {
    cpu.C = 0x10;
    CMP_CanCompareReg(CMP_C, 0x10, true, false);
}

TEST_F(I8080_CMPFixture, CMP_C_2) {
    cpu.C = 0x05;
    CMP_CanCompareReg(CMP_C, 0x0A, false, false);
}

TEST_F(I8080_CMPFixture, CMP_C_3) {
    cpu.C = 0x05;
    CMP_CanCompareReg(CMP_C, 0x02, false, false);
}

TEST_F(I8080_CMPFixture, CMP_C_4) {
    cpu.C = 0x05;
    CMP_CanCompareReg(CMP_C, (BYTE)-0x1B, false, false);
}

TEST_F(I8080_CMPFixture, CMP_D_1) {
    cpu.D = 0x10;
    CMP_CanCompareReg(CMP_D, 0x10, true, false);
}

TEST_F(I8080_CMPFixture, CMP_D_2) {
    cpu.D = 0x05;
    CMP_CanCompareReg(CMP_D, 0x0A, false, false);
}

TEST_F(I8080_CMPFixture, CMP_D_3) {
    cpu.D = 0x05;
    CMP_CanCompareReg(CMP_D, 0x02, false, false);
}

TEST_F(I8080_CMPFixture, CMP_D_4) {
    cpu.D = 0x05;
    CMP_CanCompareReg(CMP_D, (BYTE)-0x1B, false, false);
}

TEST_F(I8080_CMPFixture, CMP_E_1) {
    cpu.E = 0x10;
    CMP_CanCompareReg(CMP_E, 0x10, true, false);
}

TEST_F(I8080_CMPFixture, CMP_E_2) {
    cpu.E = 0x05;
    CMP_CanCompareReg(CMP_E, 0x0A, false, false);
}

TEST_F(I8080_CMPFixture, CMP_E_3) {
    cpu.E = 0x05;
    CMP_CanCompareReg(CMP_E, 0x02, false, false);
}

TEST_F(I8080_CMPFixture, CMP_E_4) {
    cpu.E = 0x05;
    CMP_CanCompareReg(CMP_E, (BYTE)-0x1B, false, false);
}

TEST_F(I8080_CMPFixture, CMP_H_1) {
    cpu.H = 0x10;
    CMP_CanCompareReg(CMP_H, 0x10, true, false);
}

TEST_F(I8080_CMPFixture, CMP_H_2) {
    cpu.H = 0x05;
    CMP_CanCompareReg(CMP_H, 0x0A, false, false);
}

TEST_F(I8080_CMPFixture, CMP_H_3) {
    cpu.H = 0x05;
    CMP_CanCompareReg(CMP_H, 0x02, false, false);
}

TEST_F(I8080_CMPFixture, CMP_H_4) {
    cpu.H = 0x05;
    CMP_CanCompareReg(CMP_H, (BYTE)-0x1B, false, false);
}

TEST_F(I8080_CMPFixture, CMP_L_1) {
    cpu.L = 0x10;
    CMP_CanCompareReg(CMP_L, 0x10, true, false);
}

TEST_F(I8080_CMPFixture, CMP_L_2) {
    cpu.L = 0x05;
    CMP_CanCompareReg(CMP_L, 0x0A, false, false);
}

TEST_F(I8080_CMPFixture, CMP_L_3) {
    cpu.L = 0x05;
    CMP_CanCompareReg(CMP_L, 0x02, false, false);
}

TEST_F(I8080_CMPFixture, CMP_L_4) {
    cpu.L = 0x05;
    CMP_CanCompareReg(CMP_L, (BYTE)-0x1B, false, false);
}

TEST_F(I8080_CMPFixture, CMP_M_1) {
    CMP_CanCompareMemory(0x10, 0x10, true, false);
}

TEST_F(I8080_CMPFixture, CMP_M_2) {
    CMP_CanCompareMemory(0x0A, 0x05, false, false);
}

TEST_F(I8080_CMPFixture, CMP_M_3) {
    CMP_CanCompareMemory(0x02, 0x05, false, false);
}

TEST_F(I8080_CMPFixture, CMP_M_4) {
    CMP_CanCompareMemory((BYTE)-0x1B, 0x05, false, false);
}

TEST_F(I8080_CMPFixture, CPI_1) {
    CPI_CanCompareImmediateValue(0x10, 0x10, true, false);
}

TEST_F(I8080_CMPFixture, CPI_2) {
    CPI_CanCompareImmediateValue(0x0A, 0x05, false, false);
}

TEST_F(I8080_CMPFixture, CPI_3) {
    CPI_CanCompareImmediateValue(0x02, 0x05, false, false);
}

TEST_F(I8080_CMPFixture, CPI_4) {
    CPI_CanCompareImmediateValue((BYTE)-0x1B, 0x05, false, false);
}
