#include "I8080_TestingSuite.h"

class I8080_SBBFixture : public I8080_TestFixture {
public:
    void SBB_A_CanSBBAccumulator(const BYTE initialValue, const BYTE expectedValue,
                                    const I8080_Status expectedStatus, const BYTE carry) {
        // given:
        cpu.Status = 0;
        cpu.Status.C = carry;
        cpu.A = initialValue;
        mem[0x0000] = SBB_A;
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

    void SBB_Register_CanSBBRegisterToAccumulator(const I8080_OpCodes opcode,
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
        mem[opcode == SBI ? 0x0002 : 0x0001] = STOP_OPCODE;

        cyclesExpected = cycles;

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, expectedValue);
        CheckStatus(expectedStatus);
        CheckCyclesCount();
    }

    void SBB_CanSBBMemoryFromAccumulator(const BYTE memoryValue,
                                       const BYTE initialValue,
                                       const BYTE carry,
                                       const BYTE expectedValue,
                                       const I8080_Status expectedStatus) {
        cpu.H = 0x12;
        cpu.L = 0x34;
        mem[0x1234] = memoryValue;
        SBB_Register_CanSBBRegisterToAccumulator(SBB_M, initialValue, carry, expectedValue, expectedStatus, 7);
    }

    void SBI_CanSBBImmediateValueFromAccumulator(const BYTE memoryValue,
                                               const BYTE initialValue,
                                               const BYTE carry,
                                               const BYTE expectedValue,
                                               const I8080_Status expectedStatus) {
        mem[0x0001] = memoryValue;
        SBB_Register_CanSBBRegisterToAccumulator(SBI, initialValue, carry, expectedValue, expectedStatus, 7);
    }
};

TEST_F(I8080_SBBFixture, SBB_A_1) {
    SBB_A_CanSBBAccumulator(0b00000001, 0b00000000,
                               I8080_Status{.C = 0, .P = 1, .AC = 0, .Z = 1, .S = 0}, 0);
}

TEST_F(I8080_SBBFixture, SBB_A_2) {
    SBB_A_CanSBBAccumulator(0b00000001, 0b00000001,
                            I8080_Status{.C = 0, .P = 0, .AC = 0, .Z = 0, .S = 0}, 1);
}

TEST_F(I8080_SBBFixture, SBB_A_3) {
    SBB_A_CanSBBAccumulator(0b10000000, 0b00000001,
                               I8080_Status{.C = 0, .P = 0, .AC = 0, .Z = 0, .S = 0}, 1);
}

TEST_F(I8080_SBBFixture, SBB_A_4) {
    SBB_A_CanSBBAccumulator(0b00000000, 0b00000000,
                               I8080_Status{.C = 0, .P = 1, .AC = 0, .Z = 1, .S = 0}, 0);
}

TEST_F(I8080_SBBFixture, SBB_B_1) {
    cpu.B = 0b00000010;
    SBB_Register_CanSBBRegisterToAccumulator(SBB_B, 0b00000100, 1, 0b00000001,
                               I8080_Status{.C = 0, .P = 0, .AC = 1, .Z = 0, .S = 0});
}

TEST_F(I8080_SBBFixture, SBB_B_2) {
    cpu.B = 0b00000010;
    SBB_Register_CanSBBRegisterToAccumulator(SBB_B, 0b00000100, 0, 0b00000010,
                               I8080_Status{.C = 0, .P = 0, .AC = 1, .Z = 0, .S = 0});
}

TEST_F(I8080_SBBFixture, SBB_B_3) {
    cpu.B = 0b01000010;
    SBB_Register_CanSBBRegisterToAccumulator(SBB_B, 0b00111101, 1, 0b11111010,
                               I8080_Status{.C = 1, .P = 1, .AC = 1, .Z = 0, .S = 1});
}

TEST_F(I8080_SBBFixture, SBB_B_4) {
    cpu.B = 0b01000010;
    SBB_Register_CanSBBRegisterToAccumulator(SBB_B, 0b00111101, 0, 0b11111011,
                                             I8080_Status{.C = 0, .P = 0, .AC = 1, .Z = 0, .S = 1});
}

TEST_F(I8080_SBBFixture, SBB_M_1) {
    SBB_CanSBBMemoryFromAccumulator(0b00000010, 0b00000100, 1, 0b00000001,
                               I8080_Status{.C = 0, .P = 0, .AC = 1, .Z = 0, .S = 0});
}

TEST_F(I8080_SBBFixture, SBB_M_2) {
    SBB_CanSBBMemoryFromAccumulator(0b00000010, 0b00000100, 0, 0b00000010,
                               I8080_Status{.C = 0, .P = 0, .AC = 1, .Z = 0, .S = 0});
}

TEST_F(I8080_SBBFixture, SBB_M_3) {
    SBB_CanSBBMemoryFromAccumulator(0b01000010, 0b00111101, 1, 0b11111010,
                               I8080_Status{.C = 1, .P = 1, .AC = 1, .Z = 0, .S = 1});
}

TEST_F(I8080_SBBFixture, SBB_M_4) {
    SBB_CanSBBMemoryFromAccumulator(0b01000010, 0b00111101, 0, 0b11111011,
                                             I8080_Status{.C = 0, .P = 0, .AC = 1, .Z = 0, .S = 1});
}

TEST_F(I8080_SBBFixture, SBI_1) {
    SBI_CanSBBImmediateValueFromAccumulator(0b00000010, 0b00000100, 1, 0b00000001,
                               I8080_Status{.C = 0, .P = 0, .AC = 1, .Z = 0, .S = 0});
}

TEST_F(I8080_SBBFixture, SBI_2) {
    SBI_CanSBBImmediateValueFromAccumulator(0b00000010, 0b00000100, 0, 0b00000010,
                               I8080_Status{.C = 0, .P = 0, .AC = 1, .Z = 0, .S = 0});
}

TEST_F(I8080_SBBFixture, SBI_3) {
    SBI_CanSBBImmediateValueFromAccumulator(0b01000010, 0b00111101, 1, 0b11111010,
                               I8080_Status{.C = 1, .P = 1, .AC = 1, .Z = 0, .S = 1});
}

TEST_F(I8080_SBBFixture, SBI_4) {
    SBI_CanSBBImmediateValueFromAccumulator(0b01000010, 0b00111101, 0, 0b11111011,
                                             I8080_Status{.C = 0, .P = 0, .AC = 1, .Z = 0, .S = 1});
}
