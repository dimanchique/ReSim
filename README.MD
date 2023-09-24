<h2>CPU Emulator project</h2>

>*This README.MD is WIP document. All progress will be committed. Stay tuned.*

<h3>Development stages:</h3>
- [x] Perform a working emulator of 6502 8-bit CPU with full set of instructions
  - [ ] Create assembler Python script to translate asm to instructions
  - [ ] Make it execute a real asm program
- [x] Interrupts handling
- [ ] Simulate hardware mapping
  - [ ] Make it execute BASIC interpreter
  - [ ] Make it work with cc65 compiler

<h3>Emulator features:</h3>
* Basic 6502 CPU functionality: fetch byte/word, read byte/word, write byte/word
* Basic 6502 CPU runtime: instructions fetching and execution
* TDD with GTest

<h3>Instructions support:</h3>
* Arithmetic: ADC/SBC
* Logic:
  * AND/OR
  * Shift Left/Right
  * Roll Left/Right
* Bit test: BIT
* Branch: BEQ/BNE/BMI/BPL/BVC/BVS
* Compare: CMP/CPX/CPY
* Clear/Set: CLx/SEx
* Increment/Decrement: INx/DEx
* Jump: JMP/JSR/RTS/BRK/RTI
* Load: LDx
* Push/Pop: PHx/PLx
* Store: STx
* Transfer: Txx
* No operation: NOP

<h3>Useful links:</h3>
* [6502 wiki page (RU)](https://ru.wikipedia.org/wiki/MOS_Technology_6502)
* [6502 wiki page (EN)](https://en.wikipedia.org/wiki/MOS_Technology_6502)
* [6502 Reference](http://www.6502.org/users/obelisk/)
* [6502 Assembly Language](https://www.masswerk.at/6502/assembler.html)