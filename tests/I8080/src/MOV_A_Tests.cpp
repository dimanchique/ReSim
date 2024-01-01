#include "I8080_MOV_Tests.h"

TEST_F(I8080_MOVFixture, ExecuteMOV_AA) {
    NopLikeMov(I8080_OpCodes::MOV_A_A);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_AB) {
    RegToRegMov(I8080_OpCodes::MOV_A_B, cpu.A, cpu.B, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_AC) {
    RegToRegMov(I8080_OpCodes::MOV_A_C, cpu.A, cpu.C, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_AD) {
    RegToRegMov(I8080_OpCodes::MOV_A_D, cpu.A, cpu.D, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_AE) {
    RegToRegMov(I8080_OpCodes::MOV_A_E, cpu.A, cpu.E, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_AH) {
    RegToRegMov(I8080_OpCodes::MOV_A_H, cpu.A, cpu.H, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_AL) {
    RegToRegMov(I8080_OpCodes::MOV_A_L, cpu.A, cpu.L, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_AM) {
    MemToRegMov(I8080_OpCodes::MOV_A_M, cpu.A, 0x1234, 0x23);
}
