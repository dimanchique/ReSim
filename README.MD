<h2>CPU Emulator project</h2>

**This README.MD is WIP document. All progress will be committed. Stay tuned.**

Development stages:
- Perform a working emulator of 6502 8-bit CPU with full set of instructions
  - Create assembler script
  - Take it execute a real asm program
- Interrupts handling
- Simulate hardware mapping
  - Make it execute BASIC interpreter
---
Emulator features:
* Basic 6502 CPU functionality: fetch word/byte, read byte/word, write byte/word
* Basic 6502 CPU runtime: instructions fetching and executing 
* TDD with GTest

Current instructions support:
* Clear/Set: CLx/SEx
* Decrement: DEx
* Jump: JMP/JSR/RTS
* Load: LDx
* Push/Pop: PHx/PLx
* Store: STx
* Transfer: Txx

Useful links:<br>
* [6502 wiki page (RU)](https://ru.wikipedia.org/wiki/MOS_Technology_6502)
* [6502 wiki page (EN)](https://en.wikipedia.org/wiki/MOS_Technology_6502)
* [6502 Reference](http://www.6502.org/users/obelisk/)