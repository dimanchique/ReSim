#include "I8080_TestingSuite.h"

class I8080_ADCFixture : public I8080_TestFixture {
public:
    void ADC_A_CanDoubleAccumulator(const BYTE initialValue, const BYTE expectedValue,
                                    const I8080_Status expectedStatus, const BYTE carry) {
        // given:
        cpu.Status = 0;
        cpu.Status.C = carry;
        cpu.A = initialValue;
        mem[0x0000] = I8080_OpCodes::ADC_A;

        cyclesExpected = 4;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, expectedValue);
        EXPECT_EQ(cpu.A, expectedValue);
        CheckStatus(expectedStatus);
        CheckCyclesCount();
    }

    void ADC_Register_CanADCRegisterToAccumulator(const I8080_OpCodes opcode,
                                                  const BYTE initialValue,
                                                  const BYTE carry,
                                                  const BYTE expectedValue,
                                                  const I8080_Status expectedStatus,
                                                  const U32 cycles = 4) {
        // given:
        cpu.Status = 0;
        cpu.Status.C = carry;
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

    void ADC_CanADCMemoryToAccumulator(const BYTE memoryValue,
                                       const BYTE initialValue,
                                       const BYTE carry,
                                       const BYTE expectedValue,
                                       const I8080_Status expectedStatus) {
        cpu.H = 0x12;
        cpu.L = 0x34;
        mem[0x1234] = memoryValue;
        ADC_Register_CanADCRegisterToAccumulator(I8080_OpCodes::ADC_M, initialValue, carry, expectedValue, expectedStatus, 7);
    }

    void ADI_CanAddImmediateValueToAccumulator(const BYTE memoryValue,
                                               const BYTE initialValue,
                                               const BYTE carry,
                                               const BYTE expectedValue,
                                               const I8080_Status expectedStatus) {
        mem[0x0001] = memoryValue;
        ADC_Register_CanADCRegisterToAccumulator(I8080_OpCodes::ACI, initialValue, carry, expectedValue, expectedStatus, 7);
    }
};

TEST_F(I8080_ADCFixture, ADC_A_1) {
    ADC_A_CanDoubleAccumulator(0b00000001, 0b00000010,
                               I8080_Status{.C = 0, .NU1 = 1, .P = 0, .AC = 0, .Z = 0, .S = 0}, 0);
}

TEST_F(I8080_ADCFixture, ADC_A_2) {
    ADC_A_CanDoubleAccumulator(0b10000000, 0b00000001,
                               I8080_Status{.C = 1, .NU1 = 1, .P = 0, .AC = 0, .Z = 0, .S = 0}, 1);
}

TEST_F(I8080_ADCFixture, ADC_A_3) {
    ADC_A_CanDoubleAccumulator(0b00000000, 0b00000000,
                               I8080_Status{.C = 0, .NU1 = 1, .P = 1, .AC = 0, .Z = 1, .S = 0}, 0);
}

TEST_F(I8080_ADCFixture, ADC_B_1) {
    cpu.B = 0b01000010;
    ADC_Register_CanADCRegisterToAccumulator(I8080_OpCodes::ADC_B, 0b00111101, 0, 0b01111111,
                               I8080_Status{.C = 0, .NU1 = 1, .P = 0, .AC = 0, .Z = 0, .S = 0});
}

TEST_F(I8080_ADCFixture, ADC_B_2) {
    cpu.B = 0b01000010;
    ADC_Register_CanADCRegisterToAccumulator(I8080_OpCodes::ADC_B, 0b00111101, 1, 0b10000000,
                               I8080_Status{.C = 0, .NU1 = 1, .P = 0, .AC = 1, .Z = 0, .S = 1});
}

TEST_F(I8080_ADCFixture, ADC_B_3) {
    cpu.B = 0b00000001;
    ADC_Register_CanADCRegisterToAccumulator(I8080_OpCodes::ADC_B, 0b00000001, 0, 0b00000010,
                                             I8080_Status{.C = 0, .NU1 = 1, .P = 0, .AC = 0, .Z = 0, .S = 0});
}

TEST_F(I8080_ADCFixture, ADC_B_4) {
    cpu.B = 0b10000000;
    ADC_Register_CanADCRegisterToAccumulator(I8080_OpCodes::ADC_B, 0b10000000, 1, 0b00000001,
                                             I8080_Status{.C = 1, .NU1 = 1, .P = 0, .AC = 0, .Z = 0, .S = 0});
}

TEST_F(I8080_ADCFixture, ADC_B_5) {
    cpu.B = 0b00000000;
    ADC_Register_CanADCRegisterToAccumulator(I8080_OpCodes::ADC_B, 0b00000000, 0, 0b00000000,
                                             I8080_Status{.C = 0, .NU1 = 1, .P = 1, .AC = 0, .Z = 1, .S = 0});
}

TEST_F(I8080_ADCFixture, ADC_B_6) {
    cpu.B = 0b11110000;
    ADC_Register_CanADCRegisterToAccumulator(I8080_OpCodes::ADC_B, 0b00001111, 1, 0b00000000,
                                             I8080_Status{.C = 1, .NU1 = 1, .P = 1, .AC = 1, .Z = 1, .S = 0});
}

TEST_F(I8080_ADCFixture, ADC_B_7) {
    cpu.B = 0b11111111;
    ADC_Register_CanADCRegisterToAccumulator(I8080_OpCodes::ADC_B, 0b00000000, 0, 0b11111111,
                                             I8080_Status{.C = 0, .NU1 = 1, .P = 1, .AC = 0, .Z = 0, .S = 1});
}

TEST_F(I8080_ADCFixture, ADC_B_8) {
    cpu.B = 0b01010101;
    ADC_Register_CanADCRegisterToAccumulator(I8080_OpCodes::ADC_B, 0b01010101, 0, 0b10101010,
                                             I8080_Status{.C = 0, .NU1 = 1, .P = 1, .AC = 0, .Z = 0, .S = 1});
}

TEST_F(I8080_ADCFixture, ADC_B_9) {
    cpu.B = 0b11111111;
    ADC_Register_CanADCRegisterToAccumulator(I8080_OpCodes::ADC_B, 0b11111111, 1, 0b11111111,
                                             I8080_Status{.C = 1, .NU1 = 1, .P = 1, .AC = 1, .Z = 0, .S = 1});
}

TEST_F(I8080_ADCFixture, ADC_B_10) {
    cpu.B = 0b00000001;
    ADC_Register_CanADCRegisterToAccumulator(I8080_OpCodes::ADC_B, 0b11111110, 0, 0b11111111,
                                             I8080_Status{.C = 0, .NU1 = 1, .P = 1, .AC = 0, .Z = 0, .S = 1});
}

TEST_F(I8080_ADCFixture, ADC_C_1) {
    cpu.C = 0b01000010;
    ADC_Register_CanADCRegisterToAccumulator(I8080_OpCodes::ADC_C, 0b00111101, 0, 0b01111111,
                                             I8080_Status{.C = 0, .NU1 = 1, .P = 0, .AC = 0, .Z = 0, .S = 0});
}

TEST_F(I8080_ADCFixture, ADC_D_1) {
    cpu.D = 0b01000010;
    ADC_Register_CanADCRegisterToAccumulator(I8080_OpCodes::ADC_D, 0b00111101, 0, 0b01111111,
                                             I8080_Status{.C = 0, .NU1 = 1, .P = 0, .AC = 0, .Z = 0, .S = 0});
}

TEST_F(I8080_ADCFixture, ADC_E_1) {
    cpu.E = 0b01000010;
    ADC_Register_CanADCRegisterToAccumulator(I8080_OpCodes::ADC_E, 0b00111101, 0, 0b01111111,
                                             I8080_Status{.C = 0, .NU1 = 1, .P = 0, .AC = 0, .Z = 0, .S = 0});
}

TEST_F(I8080_ADCFixture, ADC_H_1) {
    cpu.H = 0b01000010;
    ADC_Register_CanADCRegisterToAccumulator(I8080_OpCodes::ADC_H, 0b00111101, 0, 0b01111111,
                                             I8080_Status{.C = 0, .NU1 = 1, .P = 0, .AC = 0, .Z = 0, .S = 0});
}

TEST_F(I8080_ADCFixture, ADC_L_1) {
    cpu.L = 0b01000010;
    ADC_Register_CanADCRegisterToAccumulator(I8080_OpCodes::ADC_L, 0b00111101, 0, 0b01111111,
                                             I8080_Status{.C = 0, .NU1 = 1, .P = 0, .AC = 0, .Z = 0, .S = 0});
}

TEST_F(I8080_ADCFixture, ADC_M_1) {
    ADC_CanADCMemoryToAccumulator(0b01000010, 0b00111101, 0, 0b01111111,
                                             I8080_Status{.C = 0, .NU1 = 1, .P = 0, .AC = 0, .Z = 0, .S = 0});
}

TEST_F(I8080_ADCFixture, ADC_M_2) {
    ADC_CanADCMemoryToAccumulator(0b01000010, 0b00111101, 1, 0b10000000,
                                             I8080_Status{.C = 0, .NU1 = 1, .P = 0, .AC = 1, .Z = 0, .S = 1});
}

TEST_F(I8080_ADCFixture, ADC_M_3) {
    ADC_CanADCMemoryToAccumulator(0b00000001, 0b00000001, 0, 0b00000010,
                                             I8080_Status{.C = 0, .NU1 = 1, .P = 0, .AC = 0, .Z = 0, .S = 0});
}

TEST_F(I8080_ADCFixture, ADC_M_4) {
    ADC_CanADCMemoryToAccumulator(0b10000000, 0b10000000, 1, 0b00000001,
                                             I8080_Status{.C = 1, .NU1 = 1, .P = 0, .AC = 0, .Z = 0, .S = 0});
}

TEST_F(I8080_ADCFixture, ADC_M_5) {
    ADC_CanADCMemoryToAccumulator(0b00000000, 0b00000000, 0, 0b00000000,
                                             I8080_Status{.C = 0, .NU1 = 1, .P = 1, .AC = 0, .Z = 1, .S = 0});
}

TEST_F(I8080_ADCFixture, ADI_1) {
    ADI_CanAddImmediateValueToAccumulator(0b01000010, 0b00111101, 0, 0b01111111,
                                          I8080_Status{.C = 0, .NU1 = 1, .P = 0, .AC = 0, .Z = 0, .S = 0});
}

TEST_F(I8080_ADCFixture, ADI_2) {
    ADI_CanAddImmediateValueToAccumulator(0b01000010, 0b00111101, 1, 0b10000000,
                                          I8080_Status{.C = 0, .NU1 = 1, .P = 0, .AC = 1, .Z = 0, .S = 1});
}

TEST_F(I8080_ADCFixture, ADI_3) {
    ADI_CanAddImmediateValueToAccumulator(0b00000001, 0b00000001, 0, 0b00000010,
                                          I8080_Status{.C = 0, .NU1 = 1, .P = 0, .AC = 0, .Z = 0, .S = 0});
}