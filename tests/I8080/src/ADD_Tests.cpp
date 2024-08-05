#include "I8080_TestingSuite.h"

class I8080_ADDFixture : public I8080_TestFixture {
public:
    void ADD_A_CanDoubleAccumulator(const BYTE initialValue, const BYTE expectedValue,
                                    const I8080_Status expectedStatus) {
        // given:
        cpu.Status = 0;
        cpu.A = initialValue;
        mem[0x0000] = ADD_A;
        mem[0x0001] = STOP_OPCODE;

        cyclesExpected = 4;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, expectedValue);
        EXPECT_EQ(cpu.A, expectedValue);
        CheckStatus(expectedStatus);
        CheckCyclesCount();
    }

    void ADD_Register_CanAddRegisterToAccumulator(const I8080_OpCodes opcode,
                                                  const BYTE initialValue,
                                                  const BYTE expectedValue,
                                                  const I8080_Status expectedStatus,
                                                  const U32 cycles = 4) {
        // given:
        cpu.Status = 0;
        cpu.A = initialValue;
        mem[0x0000] = opcode;
        mem[opcode == ADI ? 0x0002 : 0x0001] = STOP_OPCODE;

        cyclesExpected = cycles;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, expectedValue);
        CheckStatus(expectedStatus);
        CheckCyclesCount();
    }

    void
    ADD_CanAddMemoryToAccumulator(const BYTE memoryValue,
                                  const BYTE initialValue,
                                  const BYTE expectedValue,
                                  const I8080_Status expectedStatus) {
        cpu.H = 0x12;
        cpu.L = 0x34;
        mem[0x1234] = memoryValue;
        ADD_Register_CanAddRegisterToAccumulator(ADD_M, initialValue, expectedValue, expectedStatus, 7);
    }

    void ADI_CanAddImmediateValueToAccumulator(const BYTE memoryValue,
                                               const BYTE initialValue,
                                               const BYTE expectedValue,
                                               const I8080_Status expectedStatus) {
        mem[0x0001] = memoryValue;
        ADD_Register_CanAddRegisterToAccumulator(ADI, initialValue, expectedValue, expectedStatus, 7);
    }
};

TEST_F(I8080_ADDFixture, ADD_A_1) {
    ADD_A_CanDoubleAccumulator(0b00000000, 0b00000000,
                               I8080_Status{.C = 0, .NU1 = 1, .P = 1, .AC = 0, .Z = 1, .S = 0});
}

TEST_F(I8080_ADDFixture, ADD_A_2) {
    ADD_A_CanDoubleAccumulator(0b00000100, 0b00001000,
                               I8080_Status{.C = 0, .NU1 = 1, .P = 0, .AC = 0, .Z = 0, .S = 0});
}

TEST_F(I8080_ADDFixture, ADD_A_3) {
    ADD_A_CanDoubleAccumulator(0b00010000, 0b00100000,
                               I8080_Status{.C = 0, .NU1 = 1, .P = 0, .AC = 0, .Z = 0, .S = 0});
}

TEST_F(I8080_ADDFixture, ADD_A_4) {
    ADD_A_CanDoubleAccumulator(0b01000000, 0b10000000,
                               I8080_Status{.C = 0, .NU1 = 1, .P = 0, .AC = 0, .Z = 0, .S = 1});
}

TEST_F(I8080_ADDFixture, ADD_A_5) {
    ADD_A_CanDoubleAccumulator(0b01001000, 0b10010000,
                               I8080_Status{.C = 0, .NU1 = 1, .P = 1, .AC = 1, .Z = 0, .S = 1});
}

TEST_F(I8080_ADDFixture, ADD_A_6) {
    ADD_A_CanDoubleAccumulator(0b10001000, 0b00010000,
                               I8080_Status{.C = 1, .NU1 = 1, .P = 0, .AC = 1, .Z = 0, .S = 0});
}

TEST_F(I8080_ADDFixture, ADD_B_1) {
    cpu.B = 0x00;
    ADD_Register_CanAddRegisterToAccumulator(ADD_B, 0b00000000, 0b00000000,
                                             I8080_Status{.C = 0, .NU1 = 1, .P = 1, .AC = 0, .Z = 1, .S = 0});
}

TEST_F(I8080_ADDFixture, ADD_B_2) {
    cpu.B = 0x2E;
    ADD_Register_CanAddRegisterToAccumulator(ADD_B, 0x6C, 0x9A,
                                             I8080_Status{.C = 0, .NU1 = 1, .P = 1, .AC = 1, .Z = 0, .S = 1});
}

TEST_F(I8080_ADDFixture, ADD_B_3) {
    cpu.B = 0x2E;
    ADD_Register_CanAddRegisterToAccumulator(ADD_B, 0x74, 0xA2,
                                             I8080_Status{.C = 0, .NU1 = 1, .P = 0, .AC = 1, .Z = 0, .S = 1});
}

TEST_F(I8080_ADDFixture, ADD_B_4) {
    cpu.B = 0b01000000;
    ADD_Register_CanAddRegisterToAccumulator(ADD_B, 0b01000000, 0b10000000,
                                             I8080_Status{.C = 0, .NU1 = 1, .P = 0, .AC = 0, .Z = 0, .S = 1});
}

TEST_F(I8080_ADDFixture, ADD_B_5) {
    cpu.B = 0b01001000;
    ADD_Register_CanAddRegisterToAccumulator(ADD_B, 0b01001000, 0b10010000,
                                             I8080_Status{.C = 0, .NU1 = 1, .P = 1, .AC = 1, .Z = 0, .S = 1});
}

TEST_F(I8080_ADDFixture, ADD_B_6) {
    cpu.B = 0b10001000;
    ADD_Register_CanAddRegisterToAccumulator(ADD_B, 0b10001000, 0b00010000,
                                             I8080_Status{.C = 1, .NU1 = 1, .P = 0, .AC = 1, .Z = 0, .S = 0});
}

TEST_F(I8080_ADDFixture, ADD_C_1) {
    cpu.C = 0b00011010;
    ADD_Register_CanAddRegisterToAccumulator(ADD_C, 0b11110100, 0b00001110,
                                             I8080_Status{.C = 1, .NU1 = 1, .P = 0, .AC = 0, .Z = 0, .S = 0});
}

TEST_F(I8080_ADDFixture, ADD_D_1) {
    cpu.D = 0b00011010;
    ADD_Register_CanAddRegisterToAccumulator(ADD_D, 0b11110100, 0b00001110,
                                             I8080_Status{.C = 1, .NU1 = 1, .P = 0, .AC = 0, .Z = 0, .S = 0});
}

TEST_F(I8080_ADDFixture, ADD_E_1) {
    cpu.E = 0b00011010;
    ADD_Register_CanAddRegisterToAccumulator(ADD_E, 0b11110100, 0b00001110,
                                             I8080_Status{.C = 1, .NU1 = 1, .P = 0, .AC = 0, .Z = 0, .S = 0});
}

TEST_F(I8080_ADDFixture, ADD_H_1) {
    cpu.H = 0b00011010;
    ADD_Register_CanAddRegisterToAccumulator(ADD_H, 0b11110100, 0b00001110,
                                             I8080_Status{.C = 1, .NU1 = 1, .P = 0, .AC = 0, .Z = 0, .S = 0});
}

TEST_F(I8080_ADDFixture, ADD_L_1) {
    cpu.L = 0b00011010;
    ADD_Register_CanAddRegisterToAccumulator(ADD_L, 0b11110100, 0b00001110,
                                             I8080_Status{.C = 1, .NU1 = 1, .P = 0, .AC = 0, .Z = 0, .S = 0});
}

TEST_F(I8080_ADDFixture, ADD_M_1) {
    ADD_CanAddMemoryToAccumulator(0b00011010, 0b11110100, 0b00001110,
                                  I8080_Status{.C = 1, .NU1 = 1, .P = 0, .AC = 0, .Z = 0, .S = 0});
}

TEST_F(I8080_ADDFixture, ADD_M_2) {
    ADD_CanAddMemoryToAccumulator(0b11000101, 0b10011110, 0b01100011,
                                  I8080_Status{.C = 1, .NU1 = 1, .P = 1, .AC = 1, .Z = 0, .S = 0});
}

TEST_F(I8080_ADDFixture, ADD_M_3) {
    ADD_CanAddMemoryToAccumulator(0b00001100, 0b11110001, 0b11111101,
                                  I8080_Status{.C = 0, .NU1 = 1, .P = 0, .AC = 0, .Z = 0, .S = 1});
}

TEST_F(I8080_ADDFixture, ADI_1) {
    ADI_CanAddImmediateValueToAccumulator(0b00011010, 0b11110100, 0b00001110,
                                          I8080_Status{.C = 1, .NU1 = 1, .P = 0, .AC = 0, .Z = 0, .S = 0});
}

TEST_F(I8080_ADDFixture, ADI_2) {
    ADI_CanAddImmediateValueToAccumulator(0b11000101, 0b10011110, 0b01100011,
                                          I8080_Status{.C = 1, .NU1 = 1, .P = 1, .AC = 1, .Z = 0, .S = 0});
}

TEST_F(I8080_ADDFixture, ADI_3) {
    ADI_CanAddImmediateValueToAccumulator(0b00001100, 0b11110001, 0b11111101,
                                          I8080_Status{.C = 0, .NU1 = 1, .P = 0, .AC = 0, .Z = 0, .S = 1});
}
