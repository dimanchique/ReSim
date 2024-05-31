#include "I8080_TestingSuite.h"

class I8080_SUBFixture : public I8080_TestFixture {
public:
    void SUB_A_CanZeroAccumulator(const BYTE initialValue, const I8080_Status &expectedStatus) {
        // given:
        cpu.Status = 0;
        cpu.A = initialValue;
        mem[0x0000] = I8080_OpCodes::SUB_A;

        cyclesExpected = 4;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        if (initialValue != 0)
            EXPECT_NE(cpu.A, initialValue);
        EXPECT_EQ(cpu.A, 0);
        CheckStatus(expectedStatus);
        CheckCyclesCount();
    }

    void SUB_Register_CanSubtractRegisterFromAccumulator(const I8080_OpCodes opcode,
                                                         const BYTE initialValue,
                                                         const BYTE expectedValue,
                                                         const I8080_Status &expectedStatus,
                                                         const U32 cycles = 4) {
        // given:
        cpu.Status = 0;
        cpu.A = initialValue;
        mem[0x0000] = opcode;

        cyclesExpected = cycles;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, expectedValue);
        CheckStatus(expectedStatus);
        CheckCyclesCount();
    }

    void
    SUB_CanSubMemoryFromAccumulator(const BYTE memoryValue,
                                    const BYTE initialValue,
                                    const BYTE expectedValue,
                                    const I8080_Status &expectedStatus) {
        cpu.H = 0x12;
        cpu.L = 0x34;
        mem[0x1234] = memoryValue;
        SUB_Register_CanSubtractRegisterFromAccumulator(I8080_OpCodes::SUB_M, initialValue, expectedValue,
                                                        expectedStatus, 7);
    }

    void SBI_CanSubImmediateValueFromAccumulator(const BYTE memoryValue,
                                                 const BYTE initialValue,
                                                 const BYTE expectedValue,
                                                 const I8080_Status &expectedStatus) {
        mem[0x0001] = memoryValue;
        SUB_Register_CanSubtractRegisterFromAccumulator(I8080_OpCodes::SUI, initialValue, expectedValue,
                                                        expectedStatus, 7);
    }
};

TEST_F(I8080_SUBFixture, SUB_A_1) {
    SUB_A_CanZeroAccumulator(0x00, I8080_Status{.C = 0, .NU1 = 1, .P = 1, .AC = 0, .Z = 1, .S = 0});
}

TEST_F(I8080_SUBFixture, SUB_A_2) {
    SUB_A_CanZeroAccumulator(0x04, I8080_Status{.C = 0, .NU1 = 1, .P = 1, .AC = 0, .Z = 1, .S = 0});
}

TEST_F(I8080_SUBFixture, SUB_A_3) {
    SUB_A_CanZeroAccumulator(0x10, I8080_Status{.C = 0, .NU1 = 1, .P = 1, .AC = 0, .Z = 1, .S = 0});
}

TEST_F(I8080_SUBFixture, SUB_A_4) {
    SUB_A_CanZeroAccumulator(0x40, I8080_Status{.C = 0, .NU1 = 1, .P = 1, .AC = 0, .Z = 1, .S = 0});
}

TEST_F(I8080_SUBFixture, SUB_A_5) {
    SUB_A_CanZeroAccumulator(0x48, I8080_Status{.C = 0, .NU1 = 1, .P = 1, .AC = 1, .Z = 1, .S = 0});
}

TEST_F(I8080_SUBFixture, SUB_A_6) {
    SUB_A_CanZeroAccumulator(0x88, I8080_Status{.C = 0, .NU1 = 1, .P = 1, .AC = 1, .Z = 1, .S = 0});
}

TEST_F(I8080_SUBFixture, SUB_B_1) {
    cpu.B = 0x00;
    SUB_Register_CanSubtractRegisterFromAccumulator(I8080_OpCodes::SUB_B, 0b00000000, 0b00000000,
                                                    I8080_Status{.C = 0, .NU1 = 1, .P = 1, .AC = 0, .Z = 1, .S = 0});
}

TEST_F(I8080_SUBFixture, SUB_B_2) {
    cpu.B = 0x9E;
    SUB_Register_CanSubtractRegisterFromAccumulator(I8080_OpCodes::SUB_B, 0xC5, 0x27,
                                                    I8080_Status{.C = 0, .NU1 = 1, .P = 1, .AC = 1, .Z = 0, .S = 0});
}

TEST_F(I8080_SUBFixture, SUB_B_3) {
    cpu.B = 0xF4;
    SUB_Register_CanSubtractRegisterFromAccumulator(I8080_OpCodes::SUB_B, 0x1A, 0x26,
                                                    I8080_Status{.C = 1, .NU1 = 1, .P = 0, .AC = 0, .Z = 0, .S = 1});
}

TEST_F(I8080_SUBFixture, SUB_B_4) {
    cpu.B = 0xDA;
    SUB_Register_CanSubtractRegisterFromAccumulator(I8080_OpCodes::SUB_B, 0xDA, 0x00,
                                                    I8080_Status{.C = 0, .NU1 = 1, .P = 1, .AC = 1, .Z = 1, .S = 0});
}

TEST_F(I8080_SUBFixture, SUB_B_5) {
    cpu.B = 0xB6;
    SUB_Register_CanSubtractRegisterFromAccumulator(I8080_OpCodes::SUB_B, 0xCA, 0x14,
                                                    I8080_Status{.C = 0, .NU1 = 1, .P = 1, .AC = 1, .Z = 0, .S = 0});
}

TEST_F(I8080_SUBFixture, SUB_B_6) {
    cpu.B = 0xFA;
    SUB_Register_CanSubtractRegisterFromAccumulator(I8080_OpCodes::SUB_B, 0xDD, 0xE3,
                                                    I8080_Status{.C = 1, .NU1 = 1, .P = 0, .AC = 1, .Z = 0, .S = 1});
}

TEST_F(I8080_SUBFixture, SUB_C_1) {
    cpu.C = 0xFA;
    SUB_Register_CanSubtractRegisterFromAccumulator(I8080_OpCodes::SUB_C, 0xDD, 0xE3,
                                                    I8080_Status{.C = 1, .NU1 = 1, .P = 0, .AC = 1, .Z = 0, .S = 1});
}

TEST_F(I8080_SUBFixture, SUB_D_1) {
    cpu.D = 0xFA;
    SUB_Register_CanSubtractRegisterFromAccumulator(I8080_OpCodes::SUB_D, 0xDD, 0xE3,
                                                    I8080_Status{.C = 1, .NU1 = 1, .P = 0, .AC = 1, .Z = 0, .S = 1});
}

TEST_F(I8080_SUBFixture, SUB_E_1) {
    cpu.E = 0xFA;
    SUB_Register_CanSubtractRegisterFromAccumulator(I8080_OpCodes::SUB_E, 0xDD, 0xE3,
                                                    I8080_Status{.C = 1, .NU1 = 1, .P = 0, .AC = 1, .Z = 0, .S = 1});
}

TEST_F(I8080_SUBFixture, SUB_H_1) {
    cpu.H = 0xFA;
    SUB_Register_CanSubtractRegisterFromAccumulator(I8080_OpCodes::SUB_H, 0xDD, 0xE3,
                                                    I8080_Status{.C = 1, .NU1 = 1, .P = 0, .AC = 1, .Z = 0, .S = 1});
}

TEST_F(I8080_SUBFixture, SUB_L_1) {
    cpu.L = 0xFA;
    SUB_Register_CanSubtractRegisterFromAccumulator(I8080_OpCodes::SUB_L, 0xDD, 0xE3,
                                                    I8080_Status{.C = 1, .NU1 = 1, .P = 0, .AC = 1, .Z = 0, .S = 1});
}

TEST_F(I8080_SUBFixture, SUB_M_1) {
    SUB_CanSubMemoryFromAccumulator(0xDA, 0xDA, 0x00,
                                    I8080_Status{.C = 0, .NU1 = 1, .P = 1, .AC = 1, .Z = 1, .S = 0});
}

TEST_F(I8080_SUBFixture, SUB_M_2) {
    SUB_CanSubMemoryFromAccumulator(0xB6, 0xCA, 0x14,
                                    I8080_Status{.C = 0, .NU1 = 1, .P = 1, .AC = 1, .Z = 0, .S = 0});
}

TEST_F(I8080_SUBFixture, SUB_M_3) {
    SUB_CanSubMemoryFromAccumulator(0xFA, 0xDD, 0xE3,
                                    I8080_Status{.C = 1, .NU1 = 1, .P = 0, .AC = 1, .Z = 0, .S = 1});
}

TEST_F(I8080_SUBFixture, SBI_1) {
    SBI_CanSubImmediateValueFromAccumulator(0xDA, 0xDA, 0x00,
                                            I8080_Status{.C = 0, .NU1 = 1, .P = 1, .AC = 1, .Z = 1, .S = 0});
}

TEST_F(I8080_SUBFixture, SBI_2) {
    SBI_CanSubImmediateValueFromAccumulator(0xB6, 0xCA, 0x14,
                                            I8080_Status{.C = 0, .NU1 = 1, .P = 1, .AC = 1, .Z = 0, .S = 0});
}

TEST_F(I8080_SUBFixture, SBI_3) {
    SBI_CanSubImmediateValueFromAccumulator(0xFA, 0xDD, 0xE3,
                                            I8080_Status{.C = 1, .NU1 = 1, .P = 0, .AC = 1, .Z = 0, .S = 1});
}
