#include "I8080_MOV_Tests.h"

TEST_F(I8080_MOVFixture, ExecuteMOV_BA) {
    RegToRegMov(I8080_OpCodes::MOV_B_A, cpu.B, cpu.A, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_BB) {
    NopLikeMov(I8080_OpCodes::MOV_B_B);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_BC) {
    RegToRegMov(I8080_OpCodes::MOV_B_C, cpu.B, cpu.C, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_BD) {
    RegToRegMov(I8080_OpCodes::MOV_B_D, cpu.B, cpu.D, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_BE) {
    RegToRegMov(I8080_OpCodes::MOV_B_E, cpu.B, cpu.E, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_BH) {
    RegToRegMov(I8080_OpCodes::MOV_B_H, cpu.B, cpu.H, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_BL) {
    RegToRegMov(I8080_OpCodes::MOV_B_L, cpu.B, cpu.L, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_BM) {
    MemToRegMov(I8080_OpCodes::MOV_B_M, cpu.B, 0x1234, 0x23);
}
