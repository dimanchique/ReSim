#include "I8080_MOV_Tests.h"

TEST_F(I8080_MOVFixture, ExecuteMOV_LA) {
    RegToRegMov(I8080_OpCodes::MOV_L_A, cpu.L, cpu.A, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_LB) {
    RegToRegMov(I8080_OpCodes::MOV_L_B, cpu.L, cpu.B, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_LC) {
    RegToRegMov(I8080_OpCodes::MOV_L_C, cpu.L, cpu.C, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_LD) {
    RegToRegMov(I8080_OpCodes::MOV_L_D, cpu.L, cpu.D, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_LE) {
    RegToRegMov(I8080_OpCodes::MOV_L_E, cpu.L, cpu.E, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_LH) {
    RegToRegMov(I8080_OpCodes::MOV_L_H, cpu.L, cpu.H, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_LL) {
    NopLikeMov(I8080_OpCodes::MOV_L_L);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_LM) {
    MemToRegMov(I8080_OpCodes::MOV_L_M, cpu.L, 0x1234, 0x23);
}
