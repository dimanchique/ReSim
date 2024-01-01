#include "I8080_MOV_Tests.h"

TEST_F(I8080_MOVFixture, ExecuteMOV_CA) {
    RegToRegMov(I8080_OpCodes::MOV_C_A, cpu.C, cpu.A, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_CB) {
    RegToRegMov(I8080_OpCodes::MOV_C_B, cpu.C, cpu.B, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_CC) {
    NopLikeMov(I8080_OpCodes::MOV_C_C);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_CD) {
    RegToRegMov(I8080_OpCodes::MOV_C_D, cpu.C, cpu.D, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_CE) {
    RegToRegMov(I8080_OpCodes::MOV_C_E, cpu.C, cpu.E, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_CH) {
    RegToRegMov(I8080_OpCodes::MOV_C_H, cpu.C, cpu.H, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_CL) {
    RegToRegMov(I8080_OpCodes::MOV_C_L, cpu.C, cpu.L, 0x23);
}

TEST_F(I8080_MOVFixture, ExecuteMOV_CM) {
    MemToRegMov(I8080_OpCodes::MOV_C_M, cpu.C, 0x1234, 0x23);
}
