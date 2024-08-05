  .org      $0000
START_IDX 	.BYTE $0000	    ; start displacement
END_IDX 	.BYTE $00FF   	; end displacement

SRC_ADDR  = $1000    	    ; source address
DST_ADDR  = $2000    	    ; destination address;

CODE      = $3000           ; source code

  .ORG      SRC_ADDR
DATA:
  .TEXT "//////// This is a large data array that must be copied during the execution of this program to test memcpy implementation in 6502 emulator of ReSim project. This array has size of 255 bytes so displacement can be stored in a single byte register ////////"

  .ORG      CODE

INIT:
            LDX START_IDX

MEMCPY:
            LDA SRC_ADDR,X
            STA DST_ADDR,X
            INX
            TXA
            EOR END_IDX
            BEQ EXIT
            JMP MEMCPY

EXIT:
EXIT_CODE   .BYTE $2        ; ReSim 6502 EXIT CODE

  .ORG      $FFFC
  .WORD     INIT

