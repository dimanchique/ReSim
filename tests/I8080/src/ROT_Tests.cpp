#include "I8080_TestingSuite.h"

enum class RotateDirection {
    LEFT,
    RIGHT
};

class I8080_ROTFixture : public I8080_TestFixture {
public:
    void ROT_CanRotate(const I8080_OpCodes opcode, const BYTE value, const RotateDirection direction, const bool throughCarry, const BYTE expectedA, const BYTE expectedCarry) {
        // given:
        cpu.A = value;
        mem[0x0000] = opcode;

        cyclesExpected = 4;

        const BYTE newCarry = direction == RotateDirection::LEFT ?
                        (value >> 7) & 1 :
                        value & 1;

        const BYTE carryBit = throughCarry ?
                cpu.Status.C :
                newCarry;

        const BYTE newA = direction == RotateDirection::LEFT ?
               BYTE(value << 1) | carryBit :
               BYTE(value >> 1) | (carryBit << 7);

        // when:
        cyclesPassed = cpu.Run(mem);

        // then:
        EXPECT_EQ(cpu.A, newA);
        EXPECT_EQ(cpu.Status.C, newCarry);
        EXPECT_EQ(expectedA, newA);
        EXPECT_EQ(expectedCarry, newCarry);
        CheckCyclesCount();
    }
};

TEST_F(I8080_ROTFixture, RLC_CanRotateLeft_1) {
    constexpr BYTE value = 0b11001100;
    ROT_CanRotate(I8080_OpCodes::RLC, value, RotateDirection::LEFT, false, 0b10011001, 1);
}

TEST_F(I8080_ROTFixture, RLC_CanRotateLeft_2) {
    constexpr BYTE value = 0b01101011;
    ROT_CanRotate(I8080_OpCodes::RLC, value, RotateDirection::LEFT, false, 0b11010110, 0);
}

TEST_F(I8080_ROTFixture, RLC_CanRotateLeft_3) {
    constexpr BYTE value = 0b10101101;
    ROT_CanRotate(I8080_OpCodes::RLC, value, RotateDirection::LEFT, false, 0b01011011, 1);
}

TEST_F(I8080_ROTFixture, RLC_CanRotateLeft_4) {
    constexpr BYTE value = 0b00000010;
    ROT_CanRotate(I8080_OpCodes::RLC, value, RotateDirection::LEFT, false, 0b00000100, 0);
}

TEST_F(I8080_ROTFixture, RLC_CanRotateRight_1) {
    constexpr BYTE value = 0b11001100;
    ROT_CanRotate(I8080_OpCodes::RRC, value, RotateDirection::RIGHT, false, 0b01100110, 0);
}

TEST_F(I8080_ROTFixture, RLC_CanRotateRight_2) {
    constexpr BYTE value = 0b01101011;
    ROT_CanRotate(I8080_OpCodes::RRC, value, RotateDirection::RIGHT, false, 0b10110101, 1);
}

TEST_F(I8080_ROTFixture, RLC_CanRotateRight_3) {
    constexpr BYTE value = 0b10101101;
    ROT_CanRotate(I8080_OpCodes::RRC, value, RotateDirection::RIGHT, false, 0b11010110, 1);
}

TEST_F(I8080_ROTFixture, RLC_CanRotateRight_4) {
    constexpr BYTE value = 0b00000010;
    ROT_CanRotate(I8080_OpCodes::RRC, value, RotateDirection::RIGHT, false, 0b00000001, 0);
}

TEST_F(I8080_ROTFixture, RLC_CanRotateLeftThroughCarry_1) {
    constexpr BYTE value = 0b11001100;
    cpu.Status.C = 0;
    ROT_CanRotate(I8080_OpCodes::RAL, value, RotateDirection::LEFT, true, 0b10011000, 1);
}

TEST_F(I8080_ROTFixture, RLC_CanRotateLeftThroughCarry_2) {
    constexpr BYTE value = 0b11001100;
    cpu.Status.C = 1;
    ROT_CanRotate(I8080_OpCodes::RAL, value, RotateDirection::LEFT, true, 0b10011001, 1);
}

TEST_F(I8080_ROTFixture, RLC_CanRotateLeftThroughCarry_3) {
    constexpr BYTE value = 0b10101101;
    cpu.Status.C = 0;
    ROT_CanRotate(I8080_OpCodes::RAL, value, RotateDirection::LEFT, true, 0b01011010, 1);
}

TEST_F(I8080_ROTFixture, RLC_CanRotateLeftThroughCarry_4) {
    constexpr BYTE value = 0b10101101;
    cpu.Status.C = 1;
    ROT_CanRotate(I8080_OpCodes::RAL, value, RotateDirection::LEFT, true, 0b01011011, 1);
}

TEST_F(I8080_ROTFixture, RLC_CanRotateRightThroughCarry_1) {
    constexpr BYTE value = 0b01001100;
    cpu.Status.C = 0;
    ROT_CanRotate(I8080_OpCodes::RAR, value, RotateDirection::RIGHT, true, 0b00100110, 0);
}

TEST_F(I8080_ROTFixture, RLC_CanRotateRightThroughCarry_2) {
    constexpr BYTE value = 0b01001100;
    cpu.Status.C = 1;
    ROT_CanRotate(I8080_OpCodes::RAR, value, RotateDirection::RIGHT, true, 0b10100110, 0);
}

TEST_F(I8080_ROTFixture, RLC_CanRotateRightThroughCarry_3) {
    constexpr BYTE value = 0b00101101;
    cpu.Status.C = 0;
    ROT_CanRotate(I8080_OpCodes::RAR, value, RotateDirection::RIGHT, true, 0b00010110, 1);
}

TEST_F(I8080_ROTFixture, RLC_CanRotateRightThroughCarry_4) {
    constexpr BYTE value = 0b00101101;
    cpu.Status.C = 1;
    ROT_CanRotate(I8080_OpCodes::RAR, value, RotateDirection::RIGHT, true, 0b10010110, 1);
}
