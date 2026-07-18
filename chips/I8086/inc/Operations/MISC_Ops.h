#pragma once

#include "I8086.h"

// Stub impl of HLT. HLT cause end of cpu execution
static void I8086_HLT(BYTE, I8086 &cpu) {}

// TODO: need to implement TEST pin handling
static void I8086_WAIT(BYTE, I8086 &cpu) {}

// Segment register overriding is handled in cpu.Step()
static void I8086_ES(BYTE, I8086 &cpu) {}
static void I8086_CS(BYTE, I8086 &cpu) {}
static void I8086_SS(BYTE, I8086 &cpu) {}
static void I8086_DS(BYTE, I8086 &cpu) {}
