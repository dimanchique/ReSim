## CPU Emulator Project

This README.md is a work in progress document. All progress will be committed. Stay tuned.

### Emulator Features:
* Base 6502 CPU functionality: fetch byte/word, read byte/word, write byte/word
* Base 6502 CPU runtime: instructions fetching and execution
* TDD with GTest framework

### Instructions Support:
- Arithmetic: ADC, SBC
- Logic: AND, OR
- Shift Left/Right
- Roll Left/Right
- Bit test: BIT
- Branch: BEQ, BNE, BMI, BPL, BVC, BVS
- Compare: CMP, CPX, CPY
- Clear/Set: CLx, SEx
- Increment/Decrement: INx, DEx
- Jump: JMP, JSR, RTS, BRK, RTI
- Load: LDx
- Push/Pop: PHx, PLx
- Store: STx
- Transfer: Txx
- No operation: NOP

### Useful Links:
- [6502 Wiki Page (RU)](https://ru.wikipedia.org/wiki/MOS_Technology_6502) (Russian)
- [6502 Wiki Page (EN)](https://en.wikipedia.org/wiki/MOS_Technology_6502) (English)
- [6502 Reference](http://www.6502.org/users/obelisk/)
- [6502 Assembly Language Tutorial](https://www.masswerk.at/6502/assembler.html)
