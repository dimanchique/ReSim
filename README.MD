This is a CPU Emulator project
---
First stage of work is to perform a working emulator of 6502 8-bit CPU with full set of instructions;<br>
Next step is to make it execute a real asm program;<br>
---
This README.MD is WIP document. All progress will be committed. Stay tuned.
---
Emulator features:
* basic functionality: fetch word/byte, read byte/word, write byte/word
* TDD with GTest
---
Current instructions support:
* Clear/Set: CLx/SEx
* Decrement: DEx
* Jump: JMP/JSR/RTS
* Load: LDx
* Push/Pop: PHx/PLx
* Store: STx
* Transfer: Txx