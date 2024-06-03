# ReSim
ReSim (RetroSimulator) was originally designed as a 6502 functional simulator, but when 6502 was finished I realised I would like to implement something else.

> Current development stage: Intel 8080

ReSim is a C++ project designed for retro computing enthusiasts, developers, and learners.
It gives you an opportunity to work with retro MPUs and test your own ASM programs.

## Key Features

### Cycle accurate execution

ReSim is aimed to accurately emulate each instruction of presented MPUs.
Cycles counter increments by each action in instruction i.e read/write, load/store, etc.
> For now, it just says "this set of instructions took X cycles", but my future goal is to implement real cycling feature

### Efficiency under the hood

As far as ReSim is C++ project it has C++ efficiency. I decided to keep project development in a "C with classes" way, i.e. no STL, no lambdas or templates.
This design choice minimizes overhead and makes the emulator efficient and lightweight, ideal for low-level emulation tasks.
> MOS6502 programs runs just a 5 times slower than native. 1 GHz emulating speed on a 5GHz CPU (single thread)

### Tests

I was trying to follow TDD principles and covered each instruction by a set of tests using GTest.
> MOS6502 covered by extra set of ASM tests. I will try to cover each MPU with such tests.

## Limitations

At this moment I don't know how to implement BIOS and hardware IO support.
This feature is really important because there's no way to run something ore complex like Basic or Tetris.
For now ReSim is just an execution environment for running little asm programs.
> You can find MOS6502 CRC32 asm and binaries in tools/asm_tests)

### Special thanks
This project started as a copy of [DavePoo's 6502 emulator](https://github.com/davepoo/6502Emulator), but the only thing left from his project here is an idea.
I designed my own way to describe execution flow, instructions layout and architecture. 
